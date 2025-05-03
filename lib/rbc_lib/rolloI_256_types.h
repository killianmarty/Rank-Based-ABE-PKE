/** 
 * \file rolloI_256_types.h
 * \brief File defining publicKey, secretKey and cipherText types for ROLLO-I
 */

#ifndef ROLLOI_256_TYPES_H
#define ROLLOI_256_TYPES_H

#include "rbc_181_qre.h"
#include "rbc_181_vspace.h"

typedef struct rolloI_256_secretKey {
	rbc_181_vspace F;
	rbc_181_qre x;
	rbc_181_qre y;
} rolloI_256_secretKey;

typedef struct rolloI_256_publicKey {
	rbc_181_qre h;
} rolloI_256_publicKey;

typedef struct rolloI_256_ciphertext{
	rbc_181_qre syndrom;
} rolloI_256_ciphertext;

#endif
