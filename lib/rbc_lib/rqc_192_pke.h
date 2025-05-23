/** 
 * \file rqc.h
 * \brief Functions of the RQC_192_PKE IND-CPA scheme
 */

#ifndef RQC_192_PKE_H
#define RQC_192_PKE_H

#include "rbc_151_vec.h"
#include "rbc_151_qre.h"


void rqc_192_pke_keygen(uint8_t* pk, uint8_t* sk);
void rqc_192_pke_encrypt(rbc_151_qre u, rbc_151_qre v, const rbc_151_vec m, uint8_t* theta, const uint8_t* pk);
void rqc_192_pke_decrypt(rbc_151_vec m, const rbc_151_qre u, const rbc_151_qre v, const uint8_t* sk);

#endif

