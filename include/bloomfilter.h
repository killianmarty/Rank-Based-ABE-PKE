#ifndef BLOOMFILTER_H
#define BLOOMFILTER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <openssl/sha.h>


// Default parameters
#define BLOOM_FILTER_SIZE (4096) // Size of Bloom Filter in bytes
#define NUM_HASH_FUNCTIONS (21) // Number of hash functions
#define HASH_LEN (16) // Length of hash in bytes
#define SALT_SIZE 10

// Bloom Filter structure
typedef struct {
    int size;
    int num_hash_functions;
    int hash_len;
    int salt_len;
    uint8_t **salts;
    uint8_t *bit_array;
} BloomFilter;

int bloom_filter_init(BloomFilter *bf, int size, int num_hash_functions, int hash_len, uint8_t **salts, int salt_len);
int bloom_filter_add(BloomFilter *bf, char *str);
int bloom_filter_check(BloomFilter *bf, char *str);

#endif