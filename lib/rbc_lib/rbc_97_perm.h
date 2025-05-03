/**
 * \file rbc_97_perm.h
 * \brief Interface for permutation matrices over Fq
 */

#ifndef RBC_97_PERM_H
#define RBC_97_PERM_H

#include "rbc_97.h"
#include "rbc_97_elt.h"
#include "rbc_97_vec.h"
#include "rbc_97_mat_fq.h"
#include "seedexpander.h"

void rbc_97_perm_init(rbc_97_perm* perm, uint32_t size);
void rbc_97_perm_clear(rbc_97_perm m);
void rbc_97_perm_set_zero(rbc_97_perm o, uint32_t size);
void rbc_97_perm_set(rbc_97_perm o, const rbc_97_perm perm, uint32_t size);
void rbc_97_perm_set_random(random_source* ctx, rbc_97_perm perm, uint32_t size);
void rbc_97_perm_set_random_from_xof(rbc_97_perm perm, uint32_t size, void (*xof)(uint8_t *, size_t, const uint8_t *, size_t), const uint8_t *xof_input, uint32_t xof_size);
void rbc_97_perm_apply(rbc_97_mat_fq o, const rbc_97_mat_fq m, const rbc_97_perm perm, uint32_t size);
#endif

