/**
 * \file api.h
 * \brief NIST KEM API used by the RQC_192_KEM IND-CCA2 scheme
 */


#ifndef RQC_192_KEM_H
#define RQC_192_KEM_H

int rqc_192_keygen(uint8_t* pk, uint8_t* sk);
int rqc_192_encaps(uint8_t* ct, uint8_t* ss, const uint8_t* pk);
int rqc_192_decaps(uint8_t* ss, const uint8_t* ct, const uint8_t* sk);

#endif

