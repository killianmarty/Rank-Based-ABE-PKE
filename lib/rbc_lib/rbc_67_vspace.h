/**
 * \file rbc_67_vspace.h
 * \brief Interface for subspaces of Fq^m
 */

#ifndef RBC_67_VSPACE_H
#define RBC_67_VSPACE_H

#include "rbc_67.h"
#include "random_source.h"
#include "seedexpander_shake.h"

void rbc_67_vspace_init(rbc_67_vspace* vs, uint32_t size);

void rbc_67_vspace_clear(rbc_67_vspace vs);

void rbc_67_vspace_set(rbc_67_vspace o, const rbc_67_vspace vs, uint32_t size);

void rbc_67_vspace_set_zero(rbc_67_vspace o, uint32_t size);

void rbc_67_vspace_set_random_full_rank(random_source* ctx, rbc_67_vspace o, uint32_t size);

void rbc_67_vspace_set_random_full_rank_with_one(random_source* ctx, rbc_67_vspace o, uint32_t size);

void rbc_67_vspace_set_random_full_rank_with_one_tmp(seedexpander_shake_t* ctx, rbc_67_vspace o, uint32_t size);

void rbc_67_vspace_direct_sum(rbc_67_vspace o, const rbc_67_vspace vs1, const rbc_67_vspace vs2, uint32_t vs1_size, uint32_t vs2_size);

uint32_t rbc_67_vspace_intersection(rbc_67_vspace o, const rbc_67_vspace vs1, const rbc_67_vspace vs2, uint32_t vs1_size, uint32_t vs2_size);

void rbc_67_vspace_product(rbc_67_vspace o, const rbc_67_vspace vs1, const rbc_67_vspace vs2, uint32_t vs1_size, uint32_t vs2_size);

void rbc_67_vspace_print(const rbc_67_vspace vs, uint32_t size);

#endif

