/** 
 * \file parsing.h
 * \brief Functions to parse secret key, public key and ciphertext of the ROLLO scheme
 */

#ifndef PARSING_H
#define PARSING_H

#include "rolloI_256_types.h"

void rolloI_256_secret_key_to_string(uint8_t* skString, const uint8_t* seed);
void rolloI_256_secret_key_from_string(rolloI_256_secretKey* sk, const uint8_t* skString);


void rolloI_256_public_key_to_string(uint8_t* pkString, rolloI_256_publicKey* pk);
void rolloI_256_public_key_from_string(rolloI_256_publicKey* pk, const uint8_t* pkString);


void rolloI_256_rolloI_256_ciphertext_to_string(uint8_t* ctString, rolloI_256_ciphertext* ct);
void rolloI_256_rolloI_256_ciphertext_from_string(rolloI_256_ciphertext* ct, const uint8_t* ctString);

#endif
