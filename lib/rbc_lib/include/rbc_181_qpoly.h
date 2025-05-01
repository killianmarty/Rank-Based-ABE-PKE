/** 
 * \file rbc_181_qpoly.h
 * \brief Functions to manipulate q-polynomials. 
 *
 * The rbc_181_qpolys are polynomials over a field of the form \f$ P(x) = \sum_{i=0}^{n} p_i \times x^{q^i} \f$ with \f$ q \f$ a rational prime.
 * See \cite ore:qpolynomials for a description of their main properties.
 *
 */

#ifndef RBC_181_QPOLY_H
#define RBC_181_QPOLY_H

#include "rbc_181_elt.h"
#include "rbc_181_poly.h"

/**
  * \typedef rbc_181_qpoly
  * \brief Structure of a q-polynomial
  */
typedef struct {
  rbc_181_vec values; /**< Coefficients of the q-polynomial */
  int32_t max_degree; /**< Maximum q-degree that the q-polynomial may have. This value never changes */
  int32_t degree; /**< Q-degree of the q-polynomial. This value is updated whenever necessary */
} rbc_181_qpoly_struct;
typedef rbc_181_qpoly_struct* rbc_181_qpoly;

void rbc_181_qpoly_init(rbc_181_qpoly* p, int32_t max_degree);

void rbc_181_qpoly_clear(rbc_181_qpoly o);

void rbc_181_qpoly_update_degree(rbc_181_qpoly p, int32_t position);

int8_t rbc_181_qpoly_set(rbc_181_qpoly o, const rbc_181_qpoly p);

int8_t rbc_181_qpoly_set_mask(rbc_181_qpoly o, const rbc_181_qpoly p1, const rbc_181_qpoly p2, uint32_t mask);

int8_t rbc_181_qpoly_set_zero(rbc_181_qpoly o);

int8_t rbc_181_qpoly_set_one(rbc_181_qpoly o);

int8_t rbc_181_qpoly_set_interpolate_vect_and_zero(rbc_181_qpoly o1, rbc_181_qpoly o2, const rbc_181_poly p1, const rbc_181_poly p2, int32_t size);

int8_t rbc_181_qpoly_annihilator(rbc_181_qpoly p, const rbc_181_vec v, int32_t size);

int8_t rbc_181_qpoly_is_zero(const rbc_181_qpoly p);

void rbc_181_qpoly_evaluate(rbc_181_elt o, const rbc_181_qpoly p, const rbc_181_elt e);

int8_t rbc_181_qpoly_scalar_mul(rbc_181_qpoly o, const rbc_181_qpoly p, const rbc_181_elt e);

int8_t rbc_181_qpoly_qexp(rbc_181_qpoly o, const rbc_181_qpoly p);

int8_t rbc_181_qpoly_add(rbc_181_qpoly o, const rbc_181_qpoly p1, const rbc_181_qpoly p2);

int8_t rbc_181_qpoly_mul(rbc_181_qpoly o, const rbc_181_qpoly p1, const rbc_181_qpoly p2);

int8_t rbc_181_qpoly_mul2(rbc_181_qpoly o, const rbc_181_qpoly p1, const rbc_181_qpoly p2, uint32_t p1_degree, uint32_t p2_degree);

int8_t rbc_181_qpoly_left_div(rbc_181_qpoly q, rbc_181_qpoly r, const rbc_181_qpoly a, const rbc_181_qpoly b);

int8_t rbc_181_qpoly_left_div2(rbc_181_qpoly q, rbc_181_qpoly r, const rbc_181_qpoly a, const rbc_181_qpoly b, uint32_t capacity, uint32_t k);

void rbc_181_qpoly_print(const rbc_181_qpoly p);

#endif

