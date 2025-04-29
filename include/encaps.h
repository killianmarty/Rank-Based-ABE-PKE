#ifndef ENCAPS__H
#define ENCAPS__H

#include "utils.h"
#include "attribute.h"
#include "bloomfilter.h"

void encaps(PublicKey *pub, Attribute *attributes, int nbAttributes, uint8_t *shared_secret, Message *msg);

#endif