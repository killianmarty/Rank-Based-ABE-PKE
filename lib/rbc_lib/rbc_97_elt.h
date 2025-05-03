/**
 * \file rbc_97_vec.h
 * \brief Interface for finite field elements
 */

#ifndef RBC_97_ELT_H
#define RBC_97_ELT_H

#include "rbc_97.h"
#include "random_source.h"

void rbc_97_field_init(void);
void rbc_97_elt_set_zero(rbc_97_elt o);

void rbc_97_elt_set_one(rbc_97_elt o);

void rbc_97_elt_set(rbc_97_elt o, const rbc_97_elt e);

void rbc_97_elt_set_mask1(rbc_97_elt o, const rbc_97_elt e1, const rbc_97_elt e2, uint32_t mask);

void rbc_97_elt_set_mask2(rbc_97_elt o1, rbc_97_elt o2, const rbc_97_elt e, uint32_t mask);

void rbc_97_elt_set_from_uint64(rbc_97_elt o, const uint64_t* e);

void rbc_97_elt_set_random(random_source* ctx, rbc_97_elt o);
uint8_t rbc_97_elt_is_zero(const rbc_97_elt e);

uint8_t rbc_97_elt_is_equal_to(const rbc_97_elt e1, const rbc_97_elt e2);

uint8_t rbc_97_elt_is_greater_than(const rbc_97_elt e1, const rbc_97_elt e2);

int32_t rbc_97_elt_get_degree(const rbc_97_elt e);

uint8_t rbc_97_elt_get_coefficient(const rbc_97_elt e, uint32_t index);

void rbc_97_elt_set_coefficient_vartime(rbc_97_elt o, uint32_t index, uint8_t bit);

void rbc_97_elt_add(rbc_97_elt o, const rbc_97_elt e1, const rbc_97_elt e2);

void rbc_97_elt_mul(rbc_97_elt o, const rbc_97_elt e1, const rbc_97_elt e2);

void rbc_97_elt_inv(rbc_97_elt o, const rbc_97_elt e);

void rbc_97_elt_sqr(rbc_97_elt o, const rbc_97_elt e);

void rbc_97_elt_nth_root(rbc_97_elt o, const rbc_97_elt e, uint32_t n);

void rbc_97_elt_reduce(rbc_97_elt o, const rbc_97_elt_ur e);

void rbc_97_elt_print(const rbc_97_elt e);

void rbc_97_elt_ur_set(rbc_97_elt_ur o, const rbc_97_elt_ur e);

void rbc_97_elt_ur_set_zero(rbc_97_elt_ur o);

void rbc_97_elt_ur_set_from_uint64(rbc_97_elt_ur o, const uint64_t* e);

void rbc_97_elt_ur_mul(rbc_97_elt_ur o, const rbc_97_elt e1, const rbc_97_elt e2);

void rbc_97_elt_ur_sqr(rbc_97_elt_ur o, const rbc_97_elt e);

void rbc_97_elt_to_string(uint8_t* str, const rbc_97_elt e);

void rbc_97_elt_from_string(rbc_97_elt e, const uint8_t* str);

void rbc_97_elt_ur_print(const rbc_97_elt_ur e);

#endif

