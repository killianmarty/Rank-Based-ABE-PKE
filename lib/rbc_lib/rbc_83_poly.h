/**
 * \file rbc_83_poly.h
 * \brief Interface for polynomials over a finite field
 */

#ifndef RBC_83_POLY_H
#define RBC_83_POLY_H

#include "rbc_83.h"
#include "rbc_83_vspace.h"
#include "random_source.h"

void rbc_83_poly_init(rbc_83_poly* p, int32_t degree);

void rbc_83_poly_clear(rbc_83_poly p);

void rbc_83_poly_sparse_init(rbc_83_poly_sparse* p, uint32_t coeff_nb, uint32_t *coeffs);

void rbc_83_poly_sparse_clear(rbc_83_poly_sparse p);

void rbc_83_poly_set_zero(rbc_83_poly o, int32_t degree);

void rbc_83_poly_set(rbc_83_poly o, const rbc_83_poly p);

void rbc_83_poly_set_random(random_source* ctx, rbc_83_poly o, int32_t degree);

void rbc_83_poly_set_random_from_xof(rbc_83_poly o,
                                  int32_t degree,
                                  void (*xof)(uint8_t *, size_t, const uint8_t *, size_t),
                                  const uint8_t *xof_input,
                                  uint32_t xof_size);

void rbc_83_poly_set_random_full_rank(random_source* ctx, rbc_83_poly o, int32_t degree);

void rbc_83_poly_set_random_full_rank_with_one(random_source* ctx, rbc_83_poly o, int32_t degree);

void rbc_83_poly_set_random_from_support(random_source* ctx, rbc_83_poly o, int32_t degree, const rbc_83_vspace support, uint32_t support_size, uint8_t copy_flag);

void rbc_83_poly_set_random_pair_from_support(random_source* ctx, rbc_83_poly o1, rbc_83_poly o2, int32_t degree, const rbc_83_vspace support, uint32_t support_size, uint8_t copy_flag);

uint8_t rbc_83_poly_is_equal_to(const rbc_83_poly p1, const rbc_83_poly p2);

void rbc_83_poly_add(rbc_83_poly o, const rbc_83_poly p1, const rbc_83_poly p2);

void rbc_83_poly_mul(rbc_83_poly o, const rbc_83_poly p1, const rbc_83_poly p2);
void rbc_83_poly_mul2(rbc_83_poly o, const rbc_83_poly p1, const rbc_83_poly p2, int32_t p1_degree, int32_t p2_degree);

void rbc_83_poly_mulmod_sparse(rbc_83_poly o, const rbc_83_poly p1, const rbc_83_poly p2, const rbc_83_poly_sparse modulus);

void rbc_83_poly_inv(rbc_83_poly o, const rbc_83_poly p, const rbc_83_poly modulus);

void rbc_83_poly_to_string(uint8_t* str, const rbc_83_poly p);

void rbc_83_poly_from_string(rbc_83_poly p, const uint8_t* str);

void rbc_83_poly_print(const rbc_83_poly p);

void rbc_83_poly_sparse_print(const rbc_83_poly_sparse p);

void rbc_83_poly_set_monomial(rbc_83_poly o, uint32_t degree);

#endif

