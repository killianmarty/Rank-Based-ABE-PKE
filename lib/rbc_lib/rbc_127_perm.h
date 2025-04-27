/**
 * \file rbc_127_perm.h
 * \brief Interface for permutation matrices over Fq
 */

#ifndef RBC_127_PERM_H
#define RBC_127_PERM_H

#include "rbc_127.h"
#include "rbc_127_elt.h"
#include "rbc_127_vec.h"
#include "rbc_127_mat_fq.h"
#include "seedexpander.h"

void rbc_127_perm_init(rbc_127_perm* perm, uint32_t size);
void rbc_127_perm_clear(rbc_127_perm m);
void rbc_127_perm_set_zero(rbc_127_perm o, uint32_t size);
void rbc_127_perm_set(rbc_127_perm o, const rbc_127_perm perm, uint32_t size);
void rbc_127_perm_set_random(random_source* ctx, rbc_127_perm perm, uint32_t size);
void rbc_127_perm_set_random_from_xof(rbc_127_perm perm, uint32_t size, void (*xof)(uint8_t *, size_t, const uint8_t *, size_t), const uint8_t *xof_input, uint32_t xof_size);
void rbc_127_perm_apply(rbc_127_mat_fq o, const rbc_127_mat_fq m, const rbc_127_perm perm, uint32_t size);
#endif

