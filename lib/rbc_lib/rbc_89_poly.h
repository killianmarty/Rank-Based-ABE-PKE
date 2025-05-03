/**
 * \file rbc_89_poly.h
 * \brief Interface for polynomials over a finite field
 */

#ifndef RBC_89_POLY_H
#define RBC_89_POLY_H

#include "rbc_89.h"
#include "rbc_89_vspace.h"
#include "random_source.h"

void rbc_89_poly_init(rbc_89_poly* p, int32_t degree);

void rbc_89_poly_clear(rbc_89_poly p);

void rbc_89_poly_sparse_init(rbc_89_poly_sparse* p, uint32_t coeff_nb, uint32_t *coeffs);

void rbc_89_poly_sparse_clear(rbc_89_poly_sparse p);

void rbc_89_poly_set_zero(rbc_89_poly o, int32_t degree);

void rbc_89_poly_set(rbc_89_poly o, const rbc_89_poly p);

void rbc_89_poly_set_random(random_source* ctx, rbc_89_poly o, int32_t degree);

void rbc_89_poly_set_random_from_xof(rbc_89_poly o,
                                  int32_t degree,
                                  void (*xof)(uint8_t *, size_t, const uint8_t *, size_t),
                                  const uint8_t *xof_input,
                                  uint32_t xof_size);

void rbc_89_poly_set_random_full_rank(random_source* ctx, rbc_89_poly o, int32_t degree);

void rbc_89_poly_set_random_full_rank_with_one(random_source* ctx, rbc_89_poly o, int32_t degree);

void rbc_89_poly_set_random_from_support(random_source* ctx, rbc_89_poly o, int32_t degree, const rbc_89_vspace support, uint32_t support_size, uint8_t copy_flag);

void rbc_89_poly_set_random_pair_from_support(random_source* ctx, rbc_89_poly o1, rbc_89_poly o2, int32_t degree, const rbc_89_vspace support, uint32_t support_size, uint8_t copy_flag);

uint8_t rbc_89_poly_is_equal_to(const rbc_89_poly p1, const rbc_89_poly p2);

void rbc_89_poly_add(rbc_89_poly o, const rbc_89_poly p1, const rbc_89_poly p2);

void rbc_89_poly_mul(rbc_89_poly o, const rbc_89_poly p1, const rbc_89_poly p2);
void rbc_89_poly_mul2(rbc_89_poly o, const rbc_89_poly p1, const rbc_89_poly p2, int32_t p1_degree, int32_t p2_degree);

void rbc_89_poly_mulmod_sparse(rbc_89_poly o, const rbc_89_poly p1, const rbc_89_poly p2, const rbc_89_poly_sparse modulus);

void rbc_89_poly_inv(rbc_89_poly o, const rbc_89_poly p, const rbc_89_poly modulus);

void rbc_89_poly_to_string(uint8_t* str, const rbc_89_poly p);

void rbc_89_poly_from_string(rbc_89_poly p, const uint8_t* str);

void rbc_89_poly_print(const rbc_89_poly p);

void rbc_89_poly_sparse_print(const rbc_89_poly_sparse p);

void rbc_89_poly_set_monomial(rbc_89_poly o, uint32_t degree);

#endif

