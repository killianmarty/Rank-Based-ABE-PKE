/**
 * \file rbc_89_vec.h
 * \brief Interface for finite field elements
 */

#ifndef RBC_89_ELT_H
#define RBC_89_ELT_H

#include "rbc_89.h"
#include "random_source.h"

void rbc_89_field_init(void);
void rbc_89_elt_set_zero(rbc_89_elt o);

void rbc_89_elt_set_one(rbc_89_elt o);

void rbc_89_elt_set(rbc_89_elt o, const rbc_89_elt e);

void rbc_89_elt_set_mask1(rbc_89_elt o, const rbc_89_elt e1, const rbc_89_elt e2, uint32_t mask);

void rbc_89_elt_set_mask2(rbc_89_elt o1, rbc_89_elt o2, const rbc_89_elt e, uint32_t mask);

void rbc_89_elt_set_from_uint64(rbc_89_elt o, const uint64_t* e);

void rbc_89_elt_set_random(random_source* ctx, rbc_89_elt o);
uint8_t rbc_89_elt_is_zero(const rbc_89_elt e);

uint8_t rbc_89_elt_is_equal_to(const rbc_89_elt e1, const rbc_89_elt e2);

uint8_t rbc_89_elt_is_greater_than(const rbc_89_elt e1, const rbc_89_elt e2);

int32_t rbc_89_elt_get_degree(const rbc_89_elt e);

uint8_t rbc_89_elt_get_coefficient(const rbc_89_elt e, uint32_t index);

void rbc_89_elt_set_coefficient_vartime(rbc_89_elt o, uint32_t index, uint8_t bit);

void rbc_89_elt_add(rbc_89_elt o, const rbc_89_elt e1, const rbc_89_elt e2);

void rbc_89_elt_mul(rbc_89_elt o, const rbc_89_elt e1, const rbc_89_elt e2);

void rbc_89_elt_inv(rbc_89_elt o, const rbc_89_elt e);

void rbc_89_elt_sqr(rbc_89_elt o, const rbc_89_elt e);

void rbc_89_elt_nth_root(rbc_89_elt o, const rbc_89_elt e, uint32_t n);

void rbc_89_elt_reduce(rbc_89_elt o, const rbc_89_elt_ur e);

void rbc_89_elt_print(const rbc_89_elt e);

void rbc_89_elt_ur_set(rbc_89_elt_ur o, const rbc_89_elt_ur e);

void rbc_89_elt_ur_set_zero(rbc_89_elt_ur o);

void rbc_89_elt_ur_set_from_uint64(rbc_89_elt_ur o, const uint64_t* e);

void rbc_89_elt_ur_mul(rbc_89_elt_ur o, const rbc_89_elt e1, const rbc_89_elt e2);

void rbc_89_elt_ur_sqr(rbc_89_elt_ur o, const rbc_89_elt e);

void rbc_89_elt_to_string(uint8_t* str, const rbc_89_elt e);

void rbc_89_elt_from_string(rbc_89_elt e, const uint8_t* str);

void rbc_89_elt_ur_print(const rbc_89_elt_ur e);

#endif

