/**
 * \file rbc_97_vspace.h
 * \brief Interface for subspaces of Fq^m
 */

#ifndef RBC_97_VSPACE_H
#define RBC_97_VSPACE_H

#include "rbc_97.h"
#include "random_source.h"
#include "seedexpander_shake.h"

void rbc_97_vspace_init(rbc_97_vspace* vs, uint32_t size);

void rbc_97_vspace_clear(rbc_97_vspace vs);

void rbc_97_vspace_set(rbc_97_vspace o, const rbc_97_vspace vs, uint32_t size);

void rbc_97_vspace_set_zero(rbc_97_vspace o, uint32_t size);

void rbc_97_vspace_set_random_full_rank(random_source* ctx, rbc_97_vspace o, uint32_t size);

void rbc_97_vspace_set_random_full_rank_with_one(random_source* ctx, rbc_97_vspace o, uint32_t size);

void rbc_97_vspace_set_random_full_rank_with_one_tmp(seedexpander_shake_t* ctx, rbc_97_vspace o, uint32_t size);

void rbc_97_vspace_direct_sum(rbc_97_vspace o, const rbc_97_vspace vs1, const rbc_97_vspace vs2, uint32_t vs1_size, uint32_t vs2_size);

uint32_t rbc_97_vspace_intersection(rbc_97_vspace o, const rbc_97_vspace vs1, const rbc_97_vspace vs2, uint32_t vs1_size, uint32_t vs2_size);

void rbc_97_vspace_product(rbc_97_vspace o, const rbc_97_vspace vs1, const rbc_97_vspace vs2, uint32_t vs1_size, uint32_t vs2_size);

void rbc_97_vspace_print(const rbc_97_vspace vs, uint32_t size);

#endif

