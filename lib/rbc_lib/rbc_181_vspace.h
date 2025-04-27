/**
 * \file rbc_181_vspace.h
 * \brief Interface for subspaces of Fq^m
 */

#ifndef RBC_181_VSPACE_H
#define RBC_181_VSPACE_H

#include "rbc_181.h"
#include "random_source.h"
#include "seedexpander_shake.h"

void rbc_181_vspace_init(rbc_181_vspace* vs, uint32_t size);

void rbc_181_vspace_clear(rbc_181_vspace vs);

void rbc_181_vspace_set(rbc_181_vspace o, const rbc_181_vspace vs, uint32_t size);

void rbc_181_vspace_set_zero(rbc_181_vspace o, uint32_t size);

void rbc_181_vspace_set_random_full_rank(random_source* ctx, rbc_181_vspace o, uint32_t size);

void rbc_181_vspace_set_random_full_rank_with_one(random_source* ctx, rbc_181_vspace o, uint32_t size);

void rbc_181_vspace_set_random_full_rank_with_one_tmp(seedexpander_shake_t* ctx, rbc_181_vspace o, uint32_t size);

void rbc_181_vspace_direct_sum(rbc_181_vspace o, const rbc_181_vspace vs1, const rbc_181_vspace vs2, uint32_t vs1_size, uint32_t vs2_size);

uint32_t rbc_181_vspace_intersection(rbc_181_vspace o, const rbc_181_vspace vs1, const rbc_181_vspace vs2, uint32_t vs1_size, uint32_t vs2_size);

void rbc_181_vspace_product(rbc_181_vspace o, const rbc_181_vspace vs1, const rbc_181_vspace vs2, uint32_t vs1_size, uint32_t vs2_size);

void rbc_181_vspace_print(const rbc_181_vspace vs, uint32_t size);

#endif

