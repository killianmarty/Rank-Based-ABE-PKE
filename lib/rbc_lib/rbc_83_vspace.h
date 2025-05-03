/**
 * \file rbc_83_vspace.h
 * \brief Interface for subspaces of Fq^m
 */

#ifndef RBC_83_VSPACE_H
#define RBC_83_VSPACE_H

#include "rbc_83.h"
#include "random_source.h"
#include "seedexpander_shake.h"

void rbc_83_vspace_init(rbc_83_vspace* vs, uint32_t size);

void rbc_83_vspace_clear(rbc_83_vspace vs);

void rbc_83_vspace_set(rbc_83_vspace o, const rbc_83_vspace vs, uint32_t size);

void rbc_83_vspace_set_zero(rbc_83_vspace o, uint32_t size);

void rbc_83_vspace_set_random_full_rank(random_source* ctx, rbc_83_vspace o, uint32_t size);

void rbc_83_vspace_set_random_full_rank_with_one(random_source* ctx, rbc_83_vspace o, uint32_t size);

void rbc_83_vspace_set_random_full_rank_with_one_tmp(seedexpander_shake_t* ctx, rbc_83_vspace o, uint32_t size);

void rbc_83_vspace_direct_sum(rbc_83_vspace o, const rbc_83_vspace vs1, const rbc_83_vspace vs2, uint32_t vs1_size, uint32_t vs2_size);

uint32_t rbc_83_vspace_intersection(rbc_83_vspace o, const rbc_83_vspace vs1, const rbc_83_vspace vs2, uint32_t vs1_size, uint32_t vs2_size);

void rbc_83_vspace_product(rbc_83_vspace o, const rbc_83_vspace vs1, const rbc_83_vspace vs2, uint32_t vs1_size, uint32_t vs2_size);

void rbc_83_vspace_print(const rbc_83_vspace vs, uint32_t size);

#endif

