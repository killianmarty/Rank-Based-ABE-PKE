/**
 * \file lrpc.h
 * \brief Fonctions to decode the error support using LRPC codes
 *
 */

#ifndef RBC_181_LRPC_H
#define RBC_181_LRPC_H

#include "rbc_181_vspace.h"
#include "rbc_181_qre.h"

unsigned int rbc_181_lrpc_RSR(rbc_181_vspace E, const uint32_t E_expected_dim, const rbc_181_vspace F, const uint32_t F_dim, const rbc_181_vec ec, const uint32_t ec_size);

#endif

