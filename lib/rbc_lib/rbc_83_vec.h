/**
 * \file rbc_83_vec.h
 * \brief Interface for vectors of finite field elements
 */

#ifndef RBC_83_VEC_H
#define RBC_83_VEC_H

#include "rbc_83.h"
#include "rbc_83_elt.h"
#include "random_source.h"
#include "seedexpander_shake.h"

void rbc_83_vec_init(rbc_83_vec* v, uint32_t size);

void rbc_83_vec_clear(rbc_83_vec v);

void rbc_83_vec_set_zero(rbc_83_vec v, uint32_t size);

void rbc_83_vec_set(rbc_83_vec o, const rbc_83_vec v, uint32_t size);

void rbc_83_vec_set_random(random_source* ctx, rbc_83_vec o, uint32_t size);

void rbc_83_vec_set_random_tmp(seedexpander_shake_t* ctx, rbc_83_vec o, uint32_t size);

void rbc_83_vec_set_random_from_xof(rbc_83_vec o,
                                 uint32_t size,
                                 void (*xof)(uint8_t *, size_t, const uint8_t *, size_t),
                                 const uint8_t *xof_input,
                                 uint32_t xof_size);

void rbc_83_vec_set_random_fixed_rank(random_source* ctx, rbc_83_vec o, uint32_t size, int32_t rank);

void rbc_83_vec_set_random_full_rank(random_source*, rbc_83_vec o, uint32_t size);

void rbc_83_vec_set_random_full_rank_with_one(random_source* ctx, rbc_83_vec o, uint32_t size);

void rbc_83_vec_set_random_full_rank_with_one_tmp(seedexpander_shake_t* ctx, rbc_83_vec o, uint32_t size);

void rbc_83_vec_set_random_from_support(random_source* ctx, rbc_83_vec o, uint32_t size, const rbc_83_vec support, uint32_t support_size, uint8_t copy_flag);
void rbc_83_vec_set_random_from_support_tmp(seedexpander_shake_t* ctx, rbc_83_vec o, uint32_t size, const rbc_83_vec support, uint32_t support_size, uint8_t copy_flag);
void rbc_83_vec_set_random_pair_from_support(random_source* ctx, rbc_83_vec o1, rbc_83_vec o2, uint32_t size, const rbc_83_vec support, uint32_t support_size, uint8_t copy_flag);

uint32_t rbc_83_vec_gauss(rbc_83_vec v, uint32_t size, uint8_t reduced_flag, rbc_83_vec *other_matrices, uint32_t nMatrices);

uint32_t rbc_83_vec_get_rank(const rbc_83_vec v, uint32_t size);

uint32_t rbc_83_vec_echelonize(rbc_83_vec o, uint32_t size);

void rbc_83_vec_add(rbc_83_vec o, const rbc_83_vec v1, const rbc_83_vec v2, uint32_t size);

void rbc_83_vec_inner_product(rbc_83_elt o, const rbc_83_vec v1, const rbc_83_vec v2, uint32_t size);

void rbc_83_vec_scalar_mul(rbc_83_vec o, const rbc_83_vec v, const rbc_83_elt e, uint32_t size);

void rbc_83_vec_to_string(uint8_t* str, const rbc_83_vec v, uint32_t size);

void rbc_83_vec_from_string(rbc_83_vec v, uint32_t size, const uint8_t* str);

void rbc_83_vec_from_bytes(rbc_83_vec o, uint32_t size, uint8_t *random);

void rbc_83_vec_from_bytes_without_mask(rbc_83_vec o, uint32_t size, const uint8_t *random);

void rbc_83_vec_to_bytes( uint8_t *o, const rbc_83_vec v, uint32_t size);

void rbc_83_vec_print(const rbc_83_vec v, uint32_t size);

#endif

