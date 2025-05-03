/** 
 * \file rolloI_192_types.h
 * \brief File defining publicKey, secretKey and cipherText types for ROLLO-I
 */

#ifndef ROLLOI_192_TYPES_H
#define ROLLOI_192_TYPES_H

#include "rbc_151_qre.h"
#include "rbc_151_vspace.h"

typedef struct rolloI_192_secretKey {
	rbc_151_vspace F;
	rbc_151_qre x;
	rbc_151_qre y;
} rolloI_192_secretKey;

typedef struct rolloI_192_publicKey {
	rbc_151_qre h;
} rolloI_192_publicKey;

typedef struct rolloI_192_ciphertext{
	rbc_151_qre syndrom;
} rolloI_192_ciphertext;

#endif
