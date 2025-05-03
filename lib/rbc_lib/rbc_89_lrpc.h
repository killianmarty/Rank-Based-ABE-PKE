/**
 * \file lrpc.h
 * \brief Fonctions to decode the error support using LRPC codes
 *
 */

#ifndef RBC_89_LRPC_H
#define RBC_89_LRPC_H

#include "rbc_89_vspace.h"
#include "rbc_89_qre.h"

unsigned int rbc_89_lrpc_RSR(rbc_89_vspace E, const uint32_t E_expected_dim, const rbc_89_vspace F, const uint32_t F_dim, const rbc_89_vec ec, const uint32_t ec_size);

#endif

