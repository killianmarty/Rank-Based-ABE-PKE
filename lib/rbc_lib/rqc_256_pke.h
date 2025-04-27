/** 
 * \file rqc.h
 * \brief Functions of the RQC_256_PKE IND-CPA scheme
 */

#ifndef RQC_256_PKE_H
#define RQC_256_PKE_H

#include "rbc_181_vec.h"
#include "rbc_181_qre.h"


void rqc_256_pke_keygen(uint8_t* pk, uint8_t* sk);
void rqc_256_pke_encrypt(rbc_181_qre u, rbc_181_qre v, const rbc_181_vec m, uint8_t* theta, const uint8_t* pk);
void rqc_256_pke_decrypt(rbc_181_vec m, const rbc_181_qre u, const rbc_181_qre v, const uint8_t* sk);

#endif

