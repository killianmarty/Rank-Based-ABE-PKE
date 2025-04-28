#ifndef BLOOMFILTER_H
#define BLOOMFILTER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "utils.h"


// Default parameters
#define BLOOM_FILTER_SIZE (8192*4) // Size of Bloom Filter in bits
#define NUM_HASH_FUNCTIONS (21) // Number of hash functions
#define HASH_LEN (16) // Length of hash in bytes

// Bloom Filter structure
typedef struct {
    int size;
    int num_hash_functions;
    int hash_len;
    uint8_t *bit_array;
} BloomFilter;

int bloom_filter_init(BloomFilter *bf, int size, int num_hash_functions, int hash_len);
int bloom_filter_add(BloomFilter *bf, char *str, char *salts[]);
int bloom_filter_check(BloomFilter *bf, char *str, char *salts[]);

#endif