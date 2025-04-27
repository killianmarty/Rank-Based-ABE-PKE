#ifndef DECRYPT__H
#define DECRYPT__H

#include "utils.h"

void decaps(uint8_t *shared_secret, rbc_181_qre cipher, PrivateKey *priv);

#endif