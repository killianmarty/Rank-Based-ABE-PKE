#include "bloomfilter.h"

int bloom_filter_init(BloomFilter *bf, int size, int num_hash_functions, int hash_len) {
    if (bf == NULL) {
        return -1;
    }
    bf->bit_array = (uint8_t *)calloc(size / 8, sizeof(uint8_t));
    bf->size = size;
    bf->num_hash_functions = num_hash_functions;
    bf->hash_len = hash_len;
    return 0;
}

int bloom_filter_add(BloomFilter *bf, char *str, char *salts[]) {
    if (bf == NULL || str == NULL) {
        return -1;
    }

    for (int i = 0; i < bf->num_hash_functions; i++) {
        char hash_256[SHA256_DIGEST_LENGTH];
        char hash[bf->hash_len/8];

        char salted_str[strlen(str) + strlen(salts[i]) + 1];
        strcpy(salted_str, str);
        strcat(salted_str, salts[i]);
        SHA256(salted_str, strlen(salted_str), hash_256);

        for (int j = bf->hash_len; j < SHA256_DIGEST_LENGTH; j++) {
            hash[j % (bf->hash_len)] ^= hash_256[j % SHA256_DIGEST_LENGTH];
        }

        uint32_t key = 0;
        for (int j = bf->hash_len/8 - 1; j >= 0; j--) {
            key = (key << 8) | hash[j];
        }

        key = key % bf->size;
        bf->bit_array[key / 8] |= (1 << (key % 8));
    }
    return 0;
}


int bloom_filter_check(BloomFilter *bf, char *str, char *salts[]) {
    if (bf == NULL || str == NULL) {
        return -1;
    }
    for (int i = 0; i < bf->num_hash_functions; i++) {
        char hash_256[SHA256_DIGEST_LENGTH];
        char hash[bf->hash_len/8];

        char salted_str[strlen(str) + strlen(salts[i]) + 1];
        strcpy(salted_str, str);
        strcat(salted_str, salts[i]);
        SHA256(salted_str, strlen(salted_str), hash_256);

        for (int j = bf->hash_len; j < SHA256_DIGEST_LENGTH; j++) {
            hash[j % (bf->hash_len)] ^= hash_256[j % SHA256_DIGEST_LENGTH];
        }

        uint32_t key = 0;
        for (int j = bf->hash_len/8 - 1; j >= 0; j--) {
            key = (key << 8) | hash[j];
        }

        key = key % bf->size;
        
        if ((bf->bit_array[key / 8] & (1 << (key % 8))) == 0) {
            return 0;
        }
    }
    return 1;
}