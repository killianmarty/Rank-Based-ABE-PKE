#ifndef ENCAPS__H
#define ENCAPS__H

#include "utils.h"
#include "attribute.h"
#include "bloomfilter.h"

int encrypt(PublicKey *pub, AttributeList * attributes, uint8_t *plaintext, int plaintextSize, CipherText *ciphertext);

#endif