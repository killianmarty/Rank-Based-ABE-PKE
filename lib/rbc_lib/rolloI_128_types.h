/** 
 * \file rolloI_128_types.h
 * \brief File defining publicKey, secretKey and cipherText types for ROLLO-I
 */

#ifndef ROLLOI_128_TYPES_H
#define ROLLOI_128_TYPES_H

#include "rbc_67_qre.h"
#include "rbc_67_vspace.h"

typedef struct rolloI_128_secretKey {
	rbc_67_vspace F;
	rbc_67_qre x;
	rbc_67_qre y;
} rolloI_128_secretKey;

typedef struct rolloI_128_publicKey {
	rbc_67_qre h;
} rolloI_128_publicKey;

typedef struct rolloI_128_ciphertext{
	rbc_67_qre syndrom;
} rolloI_128_ciphertext;

#endif
