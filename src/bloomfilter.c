#include "bloomfilter.h"

int bloom_filter_init(BloomFilter *bf, int size, int num_hash_functions, int hash_len, uint8_t **salts, int salt_len) {
    if (!bf || size <= 0 || num_hash_functions <= 0 || hash_len <= 0) return -1;
    bf->size = size;
    bf->num_hash_functions = num_hash_functions;
    bf->hash_len = hash_len;
    bf->salt_len = salt_len;
    bf->salts = salts;
    
    bf->bit_array = calloc(size, sizeof(uint8_t));
    if (!bf->bit_array) return -1;
    return 0;
}

int bloom_filter_add(BloomFilter *bf, char *str) {
    if (!bf || !str) return -1;

    size_t str_len = strlen(str);
    for (int i = 0; i < bf->num_hash_functions; ++i) {

        unsigned char *buf = malloc(bf->salt_len + str_len);
        memcpy(buf, bf->salts[i], bf->salt_len);
        memcpy(buf + bf->salt_len, str, str_len);

        unsigned char hash[SHA256_DIGEST_LENGTH];
        SHA256(buf, bf->salt_len + str_len, hash);
        free(buf);

        uint32_t hv = ((uint32_t)hash[0] << 24) |
                      ((uint32_t)hash[1] << 16) |
                      ((uint32_t)hash[2] << 8)  |
                      ((uint32_t)hash[3]);

        uint32_t bit_idx = hv % bf->size * 8;
        uint32_t byte_idx = bit_idx / 8;
        uint8_t  bit_mask = 1 << (bit_idx % 8);

        bf->bit_array[byte_idx] |= bit_mask;
    }

    return 0;
}

int bloom_filter_check(BloomFilter *bf, char *str) {
    if (!bf || !str) return 0;

    size_t str_len = strlen(str);
    for (int i = 0; i < bf->num_hash_functions; ++i) {

        unsigned char *buf = malloc(bf->salt_len + str_len);
        memcpy(buf, bf->salts[i], bf->salt_len);
        memcpy(buf + bf->salt_len, str, str_len);

        unsigned char hash[SHA256_DIGEST_LENGTH];
        SHA256(buf, bf->salt_len + str_len, hash);
        free(buf);

        uint32_t hv = ((uint32_t)hash[0] << 24) |
                      ((uint32_t)hash[1] << 16) |
                      ((uint32_t)hash[2] << 8)  |
                      ((uint32_t)hash[3]);

        uint32_t bit_idx = hv % bf->size * 8;
        uint32_t byte_idx = bit_idx / 8;
        uint8_t  bit_mask = 1 << (bit_idx % 8);

        if (!(bf->bit_array[byte_idx] & bit_mask)) {
            return 0;
        }
    }
    return 1;
}