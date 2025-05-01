/**
 * \file rbc_181_vec.h
 * \brief Interface for finite field elements
 */

#ifndef RBC_181_ELT_H
#define RBC_181_ELT_H

#include "rbc_181.h"
#include "random_source.h"

void rbc_181_field_init(void);
void rbc_181_elt_set_zero(rbc_181_elt o);

void rbc_181_elt_set_one(rbc_181_elt o);

void rbc_181_elt_set(rbc_181_elt o, const rbc_181_elt e);

void rbc_181_elt_set_mask1(rbc_181_elt o, const rbc_181_elt e1, const rbc_181_elt e2, uint32_t mask);

void rbc_181_elt_set_mask2(rbc_181_elt o1, rbc_181_elt o2, const rbc_181_elt e, uint32_t mask);

void rbc_181_elt_set_from_uint64(rbc_181_elt o, const uint64_t* e);

void rbc_181_elt_set_random(random_source* ctx, rbc_181_elt o);
uint8_t rbc_181_elt_is_zero(const rbc_181_elt e);

uint8_t rbc_181_elt_is_equal_to(const rbc_181_elt e1, const rbc_181_elt e2);

uint8_t rbc_181_elt_is_greater_than(const rbc_181_elt e1, const rbc_181_elt e2);

int32_t rbc_181_elt_get_degree(const rbc_181_elt e);

uint8_t rbc_181_elt_get_coefficient(const rbc_181_elt e, uint32_t index);

void rbc_181_elt_set_coefficient_vartime(rbc_181_elt o, uint32_t index, uint8_t bit);

void rbc_181_elt_add(rbc_181_elt o, const rbc_181_elt e1, const rbc_181_elt e2);

void rbc_181_elt_mul(rbc_181_elt o, const rbc_181_elt e1, const rbc_181_elt e2);

void rbc_181_elt_inv(rbc_181_elt o, const rbc_181_elt e);

void rbc_181_elt_sqr(rbc_181_elt o, const rbc_181_elt e);

void rbc_181_elt_nth_root(rbc_181_elt o, const rbc_181_elt e, uint32_t n);

void rbc_181_elt_reduce(rbc_181_elt o, const rbc_181_elt_ur e);

void rbc_181_elt_print(const rbc_181_elt e);

void rbc_181_elt_ur_set(rbc_181_elt_ur o, const rbc_181_elt_ur e);

void rbc_181_elt_ur_set_zero(rbc_181_elt_ur o);

void rbc_181_elt_ur_set_from_uint64(rbc_181_elt_ur o, const uint64_t* e);

void rbc_181_elt_ur_mul(rbc_181_elt_ur o, const rbc_181_elt e1, const rbc_181_elt e2);

void rbc_181_elt_ur_sqr(rbc_181_elt_ur o, const rbc_181_elt e);

void rbc_181_elt_to_string(uint8_t* str, const rbc_181_elt e);

void rbc_181_elt_from_string(rbc_181_elt e, const uint8_t* str);

void rbc_181_elt_ur_print(const rbc_181_elt_ur e);

#endif

