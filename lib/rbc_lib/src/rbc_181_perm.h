/**
 * \file rbc_181_perm.h
 * \brief Interface for permutation matrices over Fq
 */

#ifndef RBC_181_PERM_H
#define RBC_181_PERM_H

#include "rbc_181.h"
#include "rbc_181_elt.h"
#include "rbc_181_vec.h"
#include "rbc_181_mat_fq.h"
#include "seedexpander.h"

void rbc_181_perm_init(rbc_181_perm* perm, uint32_t size);
void rbc_181_perm_clear(rbc_181_perm m);
void rbc_181_perm_set_zero(rbc_181_perm o, uint32_t size);
void rbc_181_perm_set(rbc_181_perm o, const rbc_181_perm perm, uint32_t size);
void rbc_181_perm_set_random(random_source* ctx, rbc_181_perm perm, uint32_t size);
void rbc_181_perm_set_random_from_xof(rbc_181_perm perm, uint32_t size, void (*xof)(uint8_t *, size_t, const uint8_t *, size_t), const uint8_t *xof_input, uint32_t xof_size);
void rbc_181_perm_apply(rbc_181_mat_fq o, const rbc_181_mat_fq m, const rbc_181_perm perm, uint32_t size);
#endif

