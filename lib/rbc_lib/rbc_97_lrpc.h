/**
 * \file lrpc.h
 * \brief Fonctions to decode the error support using LRPC codes
 *
 */

#ifndef RBC_97_LRPC_H
#define RBC_97_LRPC_H

#include "rbc_97_vspace.h"
#include "rbc_97_qre.h"

unsigned int rbc_97_lrpc_RSR(rbc_97_vspace E, const uint32_t E_expected_dim, const rbc_97_vspace F, const uint32_t F_dim, const rbc_97_vec ec, const uint32_t ec_size);

#endif

