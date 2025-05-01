/**
 * \file rbc_151_vec.h
 * \brief Interface for finite field elements
 */

#ifndef RBC_151_ELT_H
#define RBC_151_ELT_H

#include "rbc_151.h"
#include "random_source.h"

void rbc_151_field_init(void);
void rbc_151_elt_set_zero(rbc_151_elt o);

void rbc_151_elt_set_one(rbc_151_elt o);

void rbc_151_elt_set(rbc_151_elt o, const rbc_151_elt e);

void rbc_151_elt_set_mask1(rbc_151_elt o, const rbc_151_elt e1, const rbc_151_elt e2, uint32_t mask);

void rbc_151_elt_set_mask2(rbc_151_elt o1, rbc_151_elt o2, const rbc_151_elt e, uint32_t mask);

void rbc_151_elt_set_from_uint64(rbc_151_elt o, const uint64_t* e);

void rbc_151_elt_set_random(random_source* ctx, rbc_151_elt o);
uint8_t rbc_151_elt_is_zero(const rbc_151_elt e);

uint8_t rbc_151_elt_is_equal_to(const rbc_151_elt e1, const rbc_151_elt e2);

uint8_t rbc_151_elt_is_greater_than(const rbc_151_elt e1, const rbc_151_elt e2);

int32_t rbc_151_elt_get_degree(const rbc_151_elt e);

uint8_t rbc_151_elt_get_coefficient(const rbc_151_elt e, uint32_t index);

void rbc_151_elt_set_coefficient_vartime(rbc_151_elt o, uint32_t index, uint8_t bit);

void rbc_151_elt_add(rbc_151_elt o, const rbc_151_elt e1, const rbc_151_elt e2);

void rbc_151_elt_mul(rbc_151_elt o, const rbc_151_elt e1, const rbc_151_elt e2);

void rbc_151_elt_inv(rbc_151_elt o, const rbc_151_elt e);

void rbc_151_elt_sqr(rbc_151_elt o, const rbc_151_elt e);

void rbc_151_elt_nth_root(rbc_151_elt o, const rbc_151_elt e, uint32_t n);

void rbc_151_elt_reduce(rbc_151_elt o, const rbc_151_elt_ur e);

void rbc_151_elt_print(const rbc_151_elt e);

void rbc_151_elt_ur_set(rbc_151_elt_ur o, const rbc_151_elt_ur e);

void rbc_151_elt_ur_set_zero(rbc_151_elt_ur o);

void rbc_151_elt_ur_set_from_uint64(rbc_151_elt_ur o, const uint64_t* e);

void rbc_151_elt_ur_mul(rbc_151_elt_ur o, const rbc_151_elt e1, const rbc_151_elt e2);

void rbc_151_elt_ur_sqr(rbc_151_elt_ur o, const rbc_151_elt e);

void rbc_151_elt_to_string(uint8_t* str, const rbc_151_elt e);

void rbc_151_elt_from_string(rbc_151_elt e, const uint8_t* str);

void rbc_151_elt_ur_print(const rbc_151_elt_ur e);

#endif

