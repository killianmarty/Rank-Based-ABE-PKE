/**
 * \file rbc_83_perm.h
 * \brief Interface for permutation matrices over Fq
 */

#ifndef RBC_83_PERM_H
#define RBC_83_PERM_H

#include "rbc_83.h"
#include "rbc_83_elt.h"
#include "rbc_83_vec.h"
#include "rbc_83_mat_fq.h"
#include "seedexpander.h"

void rbc_83_perm_init(rbc_83_perm* perm, uint32_t size);
void rbc_83_perm_clear(rbc_83_perm m);
void rbc_83_perm_set_zero(rbc_83_perm o, uint32_t size);
void rbc_83_perm_set(rbc_83_perm o, const rbc_83_perm perm, uint32_t size);
void rbc_83_perm_set_random(random_source* ctx, rbc_83_perm perm, uint32_t size);
void rbc_83_perm_set_random_from_xof(rbc_83_perm perm, uint32_t size, void (*xof)(uint8_t *, size_t, const uint8_t *, size_t), const uint8_t *xof_input, uint32_t xof_size);
void rbc_83_perm_apply(rbc_83_mat_fq o, const rbc_83_mat_fq m, const rbc_83_perm perm, uint32_t size);
#endif

