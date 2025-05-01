#ifndef DECRYPT__H
#define DECRYPT__H

#include "utils.h"
#include "attribute.h"

int decrypt(PrivateKey *priv, Attribute *attributes, int nbAttributes, CipherText *ciphertext,  uint8_t *plaintext);

#endif