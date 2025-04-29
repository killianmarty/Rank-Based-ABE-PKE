#ifndef DECRYPT__H
#define DECRYPT__H

#include "utils.h"
#include "attribute.h"

void decaps(PrivateKey *priv, Message *msg, Attribute *attributes, int nbAttributes, uint8_t *shared_secret);

#endif