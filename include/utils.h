#ifndef UTILS__H
#define UTILS__H

#include "../lib/rbc_lib/rbc.h"
#include <openssl/sha.h>

typedef struct {
    rbc_181_vspace F;
    rbc_181_qre x;
    rbc_181_qre y;
} PrivateKey;

typedef struct {
    rbc_181_qre h;
} PublicKey;


#define N 113
#define D 9
#define R 9
#define R_BYTES 204
#define SECRET_KEY_BYTES 64

void H(uint8_t *payload, int payload_size, rbc_181_vspace E, int rank, rbc_181_qre output);

#endif