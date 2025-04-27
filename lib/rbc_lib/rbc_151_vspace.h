/**
 * \file rbc_151_vspace.h
 * \brief Interface for subspaces of Fq^m
 */

#ifndef RBC_151_VSPACE_H
#define RBC_151_VSPACE_H

#include "rbc_151.h"
#include "random_source.h"
#include "seedexpander_shake.h"

void rbc_151_vspace_init(rbc_151_vspace* vs, uint32_t size);

void rbc_151_vspace_clear(rbc_151_vspace vs);

void rbc_151_vspace_set(rbc_151_vspace o, const rbc_151_vspace vs, uint32_t size);

void rbc_151_vspace_set_zero(rbc_151_vspace o, uint32_t size);

void rbc_151_vspace_set_random_full_rank(random_source* ctx, rbc_151_vspace o, uint32_t size);

void rbc_151_vspace_set_random_full_rank_with_one(random_source* ctx, rbc_151_vspace o, uint32_t size);

void rbc_151_vspace_set_random_full_rank_with_one_tmp(seedexpander_shake_t* ctx, rbc_151_vspace o, uint32_t size);

void rbc_151_vspace_direct_sum(rbc_151_vspace o, const rbc_151_vspace vs1, const rbc_151_vspace vs2, uint32_t vs1_size, uint32_t vs2_size);

uint32_t rbc_151_vspace_intersection(rbc_151_vspace o, const rbc_151_vspace vs1, const rbc_151_vspace vs2, uint32_t vs1_size, uint32_t vs2_size);

void rbc_151_vspace_product(rbc_151_vspace o, const rbc_151_vspace vs1, const rbc_151_vspace vs2, uint32_t vs1_size, uint32_t vs2_size);

void rbc_151_vspace_print(const rbc_151_vspace vs, uint32_t size);

#endif

