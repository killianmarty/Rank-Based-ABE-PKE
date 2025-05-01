#ifndef ENCAPS__H
#define ENCAPS__H

#include "utils.h"
#include "attribute.h"
#include "bloomfilter.h"

int encrypt(PublicKey *pub, Attribute *attributes, int nbAttributes, uint8_t *plaintext, int plaintextSize, CipherText *msg);

#endif