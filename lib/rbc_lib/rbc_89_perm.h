/**
 * \file rbc_89_perm.h
 * \brief Interface for permutation matrices over Fq
 */

#ifndef RBC_89_PERM_H
#define RBC_89_PERM_H

#include "rbc_89.h"
#include "rbc_89_elt.h"
#include "rbc_89_vec.h"
#include "rbc_89_mat_fq.h"
#include "seedexpander.h"

void rbc_89_perm_init(rbc_89_perm* perm, uint32_t size);
void rbc_89_perm_clear(rbc_89_perm m);
void rbc_89_perm_set_zero(rbc_89_perm o, uint32_t size);
void rbc_89_perm_set(rbc_89_perm o, const rbc_89_perm perm, uint32_t size);
void rbc_89_perm_set_random(random_source* ctx, rbc_89_perm perm, uint32_t size);
void rbc_89_perm_set_random_from_xof(rbc_89_perm perm, uint32_t size, void (*xof)(uint8_t *, size_t, const uint8_t *, size_t), const uint8_t *xof_input, uint32_t xof_size);
void rbc_89_perm_apply(rbc_89_mat_fq o, const rbc_89_mat_fq m, const rbc_89_perm perm, uint32_t size);
#endif

