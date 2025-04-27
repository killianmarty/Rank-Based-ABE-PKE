/**
 * \file lrpc.h
 * \brief Fonctions to decode the error support using LRPC codes
 *
 */

#ifndef RBC_127_LRPC_H
#define RBC_127_LRPC_H

#include "rbc_127_vspace.h"
#include "rbc_127_qre.h"

unsigned int rbc_127_lrpc_RSR(rbc_127_vspace E, const uint32_t E_expected_dim, const rbc_127_vspace F, const uint32_t F_dim, const rbc_127_vec ec, const uint32_t ec_size);

#endif

