/** 
 * \file parsing.h
 * \brief Functions to parse secret key, public key and ciphertext of the RQC scheme
 */

#ifndef RQC_192_PARSING_H
#define RQC_192_PARSING_H

#include "rbc_151_qre.h"


void rqc_192_secret_key_to_string(uint8_t* sk, const uint8_t* seed, const uint8_t* pk);
void rqc_192_secret_key_from_string(rbc_151_qre x, rbc_151_qre y, uint8_t* pk, const uint8_t* sk);

void rqc_192_public_key_to_string(uint8_t* pk, const rbc_151_qre s, const uint8_t* seed);
void rqc_192_public_key_from_string(rbc_151_qre g, rbc_151_qre h, rbc_151_qre s, const uint8_t* pk);

void rqc_192_kem_ciphertext_to_string(uint8_t* ct, const rbc_151_qre u, const rbc_151_qre v, const uint8_t* d);
void rqc_192_kem_ciphertext_from_string(rbc_151_qre u, rbc_151_qre v, uint8_t* d, const uint8_t* ct);

#endif

