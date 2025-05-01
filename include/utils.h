#ifndef UTILS__H
#define UTILS__H

#include "../lib/rbc_lib/rbc.h"
#include <openssl/sha.h>
#include "bloomfilter.h"

typedef struct {
    rbc_181_vspace F;
    rbc_181_qre x;
    rbc_181_qre y;
} PrivateKey;

typedef struct {
    rbc_181_qre h;
} PublicKey;

typedef struct {
    rbc_181_qre cipher;
    BloomFilter bf_keys;
    uint8_t salts[NUM_HASH_FUNCTIONS][SALT_SIZE];
} Message;

#define M 181
#define N 179
#define D 9
#define R 9
#define R_BYTES 204
#define SECRET_KEY_BYTES 64

#define SERIALIZED_QRE_SIZE (M*(N+1) / 8) + 1
#define SERIALIZED_VSPACE_SIZE (M * D / 8)+1 //TODO: sure about D everywhere ?
#define SERIALIZED_PRIVATE_KEY_SIZE (2*SERIALIZED_QRE_SIZE + SERIALIZED_VSPACE_SIZE)
#define SERIALIZED_PUBLIC_KEY_SIZE SERIALIZED_QRE_SIZE

void H(uint8_t *payload, int payload_size, rbc_181_qre output);

uint8_t * serialize_private_key(PrivateKey *key);

PrivateKey * deserialize_private_key(uint8_t *input);

uint8_t * serialize_public_key(PublicKey *key);

PublicKey * deserialize_public_key(uint8_t *input);

uint8_t * serialize_message(Message *msg);

Message * deserialize_message(uint8_t *input);

#endif