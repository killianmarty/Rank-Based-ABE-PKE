/** 
 * \file rqc.h
 * \brief Functions of the RQC_128_PKE IND-CPA scheme
 */

#ifndef RQC_128_PKE_H
#define RQC_128_PKE_H

#include "rbc_127_vec.h"
#include "rbc_127_qre.h"


void rqc_128_pke_keygen(uint8_t* pk, uint8_t* sk);
void rqc_128_pke_encrypt(rbc_127_qre u, rbc_127_qre v, const rbc_127_vec m, uint8_t* theta, const uint8_t* pk);
void rqc_128_pke_decrypt(rbc_127_vec m, const rbc_127_qre u, const rbc_127_qre v, const uint8_t* sk);

#endif

