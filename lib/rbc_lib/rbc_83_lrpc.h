/**
 * \file lrpc.h
 * \brief Fonctions to decode the error support using LRPC codes
 *
 */

#ifndef RBC_83_LRPC_H
#define RBC_83_LRPC_H

#include "rbc_83_vspace.h"
#include "rbc_83_qre.h"

unsigned int rbc_83_lrpc_RSR(rbc_83_vspace E, const uint32_t E_expected_dim, const rbc_83_vspace F, const uint32_t F_dim, const rbc_83_vec ec, const uint32_t ec_size);

#endif

