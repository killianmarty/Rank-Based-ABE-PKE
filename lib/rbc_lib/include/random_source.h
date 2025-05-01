
#ifndef RANDOM_SOURCE_H
#define RANDOM_SOURCE_H

#include "randombytes.h"
#include "seedexpander.h"

#define RANDOM_SOURCE_PRNG    0
#define RANDOM_SOURCE_SEEDEXP 1

typedef struct {
  AES_XOF_struct *ctx;
  int type;
} random_source;

void random_source_init(random_source *o, int type);
void random_source_seed(random_source *o, unsigned char *seed);
void random_source_get_bytes(random_source *e, unsigned char *buffer, size_t len);
void random_source_clear(random_source *o);

#endif

