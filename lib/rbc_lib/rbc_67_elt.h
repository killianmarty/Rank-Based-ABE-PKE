/**
 * \file rbc_67_vec.h
 * \brief Interface for finite field elements
 */

#ifndef RBC_67_ELT_H
#define RBC_67_ELT_H

#include "rbc_67.h"
#include "random_source.h"

void rbc_67_field_init(void);
void rbc_67_elt_set_zero(rbc_67_elt o);

void rbc_67_elt_set_one(rbc_67_elt o);

void rbc_67_elt_set(rbc_67_elt o, const rbc_67_elt e);

void rbc_67_elt_set_mask1(rbc_67_elt o, const rbc_67_elt e1, const rbc_67_elt e2, uint32_t mask);

void rbc_67_elt_set_mask2(rbc_67_elt o1, rbc_67_elt o2, const rbc_67_elt e, uint32_t mask);

void rbc_67_elt_set_from_uint64(rbc_67_elt o, const uint64_t* e);

void rbc_67_elt_set_random(random_source* ctx, rbc_67_elt o);
uint8_t rbc_67_elt_is_zero(const rbc_67_elt e);

uint8_t rbc_67_elt_is_equal_to(const rbc_67_elt e1, const rbc_67_elt e2);

uint8_t rbc_67_elt_is_greater_than(const rbc_67_elt e1, const rbc_67_elt e2);

int32_t rbc_67_elt_get_degree(const rbc_67_elt e);

uint8_t rbc_67_elt_get_coefficient(const rbc_67_elt e, uint32_t index);

void rbc_67_elt_set_coefficient_vartime(rbc_67_elt o, uint32_t index, uint8_t bit);

void rbc_67_elt_add(rbc_67_elt o, const rbc_67_elt e1, const rbc_67_elt e2);

void rbc_67_elt_mul(rbc_67_elt o, const rbc_67_elt e1, const rbc_67_elt e2);

void rbc_67_elt_inv(rbc_67_elt o, const rbc_67_elt e);

void rbc_67_elt_sqr(rbc_67_elt o, const rbc_67_elt e);

void rbc_67_elt_nth_root(rbc_67_elt o, const rbc_67_elt e, uint32_t n);

void rbc_67_elt_reduce(rbc_67_elt o, const rbc_67_elt_ur e);

void rbc_67_elt_print(const rbc_67_elt e);

void rbc_67_elt_ur_set(rbc_67_elt_ur o, const rbc_67_elt_ur e);

void rbc_67_elt_ur_set_zero(rbc_67_elt_ur o);

void rbc_67_elt_ur_set_from_uint64(rbc_67_elt_ur o, const uint64_t* e);

void rbc_67_elt_ur_mul(rbc_67_elt_ur o, const rbc_67_elt e1, const rbc_67_elt e2);

void rbc_67_elt_ur_sqr(rbc_67_elt_ur o, const rbc_67_elt e);

void rbc_67_elt_to_string(uint8_t* str, const rbc_67_elt e);

void rbc_67_elt_from_string(rbc_67_elt e, const uint8_t* str);

void rbc_67_elt_ur_print(const rbc_67_elt_ur e);

#endif

