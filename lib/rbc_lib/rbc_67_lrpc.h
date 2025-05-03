/**
 * \file lrpc.h
 * \brief Fonctions to decode the error support using LRPC codes
 *
 */

#ifndef RBC_67_LRPC_H
#define RBC_67_LRPC_H

#include "rbc_67_vspace.h"
#include "rbc_67_qre.h"

unsigned int rbc_67_lrpc_RSR(rbc_67_vspace E, const uint32_t E_expected_dim, const rbc_67_vspace F, const uint32_t F_dim, const rbc_67_vec ec, const uint32_t ec_size);

#endif

