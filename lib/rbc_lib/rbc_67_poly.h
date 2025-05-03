/**
 * \file rbc_67_poly.h
 * \brief Interface for polynomials over a finite field
 */

#ifndef RBC_67_POLY_H
#define RBC_67_POLY_H

#include "rbc_67.h"
#include "rbc_67_vspace.h"
#include "random_source.h"

void rbc_67_poly_init(rbc_67_poly* p, int32_t degree);

void rbc_67_poly_clear(rbc_67_poly p);

void rbc_67_poly_sparse_init(rbc_67_poly_sparse* p, uint32_t coeff_nb, uint32_t *coeffs);

void rbc_67_poly_sparse_clear(rbc_67_poly_sparse p);

void rbc_67_poly_set_zero(rbc_67_poly o, int32_t degree);

void rbc_67_poly_set(rbc_67_poly o, const rbc_67_poly p);

void rbc_67_poly_set_random(random_source* ctx, rbc_67_poly o, int32_t degree);

void rbc_67_poly_set_random_from_xof(rbc_67_poly o,
                                  int32_t degree,
                                  void (*xof)(uint8_t *, size_t, const uint8_t *, size_t),
                                  const uint8_t *xof_input,
                                  uint32_t xof_size);

void rbc_67_poly_set_random_full_rank(random_source* ctx, rbc_67_poly o, int32_t degree);

void rbc_67_poly_set_random_full_rank_with_one(random_source* ctx, rbc_67_poly o, int32_t degree);

void rbc_67_poly_set_random_from_support(random_source* ctx, rbc_67_poly o, int32_t degree, const rbc_67_vspace support, uint32_t support_size, uint8_t copy_flag);

void rbc_67_poly_set_random_pair_from_support(random_source* ctx, rbc_67_poly o1, rbc_67_poly o2, int32_t degree, const rbc_67_vspace support, uint32_t support_size, uint8_t copy_flag);

uint8_t rbc_67_poly_is_equal_to(const rbc_67_poly p1, const rbc_67_poly p2);

void rbc_67_poly_add(rbc_67_poly o, const rbc_67_poly p1, const rbc_67_poly p2);

void rbc_67_poly_mul(rbc_67_poly o, const rbc_67_poly p1, const rbc_67_poly p2);
void rbc_67_poly_mul2(rbc_67_poly o, const rbc_67_poly p1, const rbc_67_poly p2, int32_t p1_degree, int32_t p2_degree);

void rbc_67_poly_mulmod_sparse(rbc_67_poly o, const rbc_67_poly p1, const rbc_67_poly p2, const rbc_67_poly_sparse modulus);

void rbc_67_poly_inv(rbc_67_poly o, const rbc_67_poly p, const rbc_67_poly modulus);

void rbc_67_poly_to_string(uint8_t* str, const rbc_67_poly p);

void rbc_67_poly_from_string(rbc_67_poly p, const uint8_t* str);

void rbc_67_poly_print(const rbc_67_poly p);

void rbc_67_poly_sparse_print(const rbc_67_poly_sparse p);

void rbc_67_poly_set_monomial(rbc_67_poly o, uint32_t degree);

#endif

