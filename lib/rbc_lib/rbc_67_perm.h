/**
 * \file rbc_67_perm.h
 * \brief Interface for permutation matrices over Fq
 */

#ifndef RBC_67_PERM_H
#define RBC_67_PERM_H

#include "rbc_67.h"
#include "rbc_67_elt.h"
#include "rbc_67_vec.h"
#include "rbc_67_mat_fq.h"
#include "seedexpander.h"

void rbc_67_perm_init(rbc_67_perm* perm, uint32_t size);
void rbc_67_perm_clear(rbc_67_perm m);
void rbc_67_perm_set_zero(rbc_67_perm o, uint32_t size);
void rbc_67_perm_set(rbc_67_perm o, const rbc_67_perm perm, uint32_t size);
void rbc_67_perm_set_random(random_source* ctx, rbc_67_perm perm, uint32_t size);
void rbc_67_perm_set_random_from_xof(rbc_67_perm perm, uint32_t size, void (*xof)(uint8_t *, size_t, const uint8_t *, size_t), const uint8_t *xof_input, uint32_t xof_size);
void rbc_67_perm_apply(rbc_67_mat_fq o, const rbc_67_mat_fq m, const rbc_67_perm perm, uint32_t size);
#endif

