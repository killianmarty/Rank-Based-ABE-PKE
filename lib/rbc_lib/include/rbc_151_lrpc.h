/**
 * \file lrpc.h
 * \brief Fonctions to decode the error support using LRPC codes
 *
 */

#ifndef RBC_151_LRPC_H
#define RBC_151_LRPC_H

#include "rbc_151_vspace.h"
#include "rbc_151_qre.h"

unsigned int rbc_151_lrpc_RSR(rbc_151_vspace E, const uint32_t E_expected_dim, const rbc_151_vspace F, const uint32_t F_dim, const rbc_151_vec ec, const uint32_t ec_size);

#endif

