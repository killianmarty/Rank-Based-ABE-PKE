/** 
 * \file parsing.h
 * \brief Functions to parse secret key, public key and ciphertext of the RQC scheme
 */

#ifndef RQC_256_PARSING_H
#define RQC_256_PARSING_H

#include "rbc_181_qre.h"


void rqc_256_secret_key_to_string(uint8_t* sk, const uint8_t* seed, const uint8_t* pk);
void rqc_256_secret_key_from_string(rbc_181_qre x, rbc_181_qre y, uint8_t* pk, const uint8_t* sk);

void rqc_256_public_key_to_string(uint8_t* pk, const rbc_181_qre s, const uint8_t* seed);
void rqc_256_public_key_from_string(rbc_181_qre g, rbc_181_qre h, rbc_181_qre s, const uint8_t* pk);

void rqc_256_kem_ciphertext_to_string(uint8_t* ct, const rbc_181_qre u, const rbc_181_qre v, const uint8_t* d);
void rqc_256_kem_ciphertext_from_string(rbc_181_qre u, rbc_181_qre v, uint8_t* d, const uint8_t* ct);

#endif

