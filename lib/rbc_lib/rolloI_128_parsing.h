/** 
 * \file parsing.h
 * \brief Functions to parse secret key, public key and ciphertext of the ROLLO scheme
 */

#ifndef PARSING_H
#define PARSING_H

#include "rolloI_128_types.h"

void rolloI_128_secret_key_to_string(uint8_t* skString, const uint8_t* seed);
void rolloI_128_secret_key_from_string(rolloI_128_secretKey* sk, const uint8_t* skString);


void rolloI_128_public_key_to_string(uint8_t* pkString, rolloI_128_publicKey* pk);
void rolloI_128_public_key_from_string(rolloI_128_publicKey* pk, const uint8_t* pkString);


void rolloI_128_rolloI_128_ciphertext_to_string(uint8_t* ctString, rolloI_128_ciphertext* ct);
void rolloI_128_rolloI_128_ciphertext_from_string(rolloI_128_ciphertext* ct, const uint8_t* ctString);

#endif
