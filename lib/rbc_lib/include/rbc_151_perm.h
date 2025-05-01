/**
 * \file rbc_151_perm.h
 * \brief Interface for permutation matrices over Fq
 */

#ifndef RBC_151_PERM_H
#define RBC_151_PERM_H

#include "rbc_151.h"
#include "rbc_151_elt.h"
#include "rbc_151_vec.h"
#include "rbc_151_mat_fq.h"
#include "seedexpander.h"

void rbc_151_perm_init(rbc_151_perm* perm, uint32_t size);
void rbc_151_perm_clear(rbc_151_perm m);
void rbc_151_perm_set_zero(rbc_151_perm o, uint32_t size);
void rbc_151_perm_set(rbc_151_perm o, const rbc_151_perm perm, uint32_t size);
void rbc_151_perm_set_random(random_source* ctx, rbc_151_perm perm, uint32_t size);
void rbc_151_perm_set_random_from_xof(rbc_151_perm perm, uint32_t size, void (*xof)(uint8_t *, size_t, const uint8_t *, size_t), const uint8_t *xof_input, uint32_t xof_size);
void rbc_151_perm_apply(rbc_151_mat_fq o, const rbc_151_mat_fq m, const rbc_151_perm perm, uint32_t size);
#endif

