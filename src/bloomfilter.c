#include "bloomfilter.h"

int bloom_filter_init(BloomFilter *bf, int size, int num_hash_functions, int hash_len) {
    if (!bf || size <= 0 || num_hash_functions <= 0 || hash_len <= 0) return -1;
    bf->size = size;
    bf->num_hash_functions = num_hash_functions;
    bf->hash_len = hash_len;
    int bytes = (size + 7) / 8;
    bf->bit_array = calloc(bytes, sizeof(uint8_t));
    if (!bf->bit_array) return -1;
    return 0;
}

int bloom_filter_add(BloomFilter *bf, char *str, char *salts[]) {
    if (!bf || !str || !salts) return -1;

    size_t str_len = strlen(str);
    for (int i = 0; i < bf->num_hash_functions; ++i) {
        char *salt = salts[i];
        size_t salt_len = strlen(salt);

        unsigned char *buf = malloc(salt_len + str_len);
        memcpy(buf, salt, salt_len);
        memcpy(buf + salt_len, str, str_len);

        unsigned char hash[SHA256_DIGEST_LENGTH];
        SHA256(buf, salt_len + str_len, hash);
        free(buf);

        uint32_t hv = ((uint32_t)hash[0] << 24) |
                      ((uint32_t)hash[1] << 16) |
                      ((uint32_t)hash[2] << 8)  |
                      ((uint32_t)hash[3]);

        uint32_t bit_idx = hv % bf->size;
        uint32_t byte_idx = bit_idx / 8;
        uint8_t  bit_mask = 1 << (bit_idx % 8);

        bf->bit_array[byte_idx] |= bit_mask;
    }

    return 0;
}

int bloom_filter_check(BloomFilter *bf, char *str, char *salts[]) {
    if (!bf || !str || !salts) return 0;

    size_t str_len = strlen(str);
    for (int i = 0; i < bf->num_hash_functions; ++i) {
        char *salt = salts[i];
        size_t salt_len = strlen(salt);

        unsigned char *buf = malloc(salt_len + str_len);
        memcpy(buf, salt, salt_len);
        memcpy(buf + salt_len, str, str_len);

        unsigned char hash[SHA256_DIGEST_LENGTH];
        SHA256(buf, salt_len + str_len, hash);
        free(buf);

        uint32_t hv = ((uint32_t)hash[0] << 24) |
                      ((uint32_t)hash[1] << 16) |
                      ((uint32_t)hash[2] << 8)  |
                      ((uint32_t)hash[3]);

        uint32_t bit_idx = hv % bf->size;
        uint32_t byte_idx = bit_idx / 8;
        uint8_t  bit_mask = 1 << (bit_idx % 8);

        if (!(bf->bit_array[byte_idx] & bit_mask)) {
            return 0;
        }
    }
    return 1;
}