/**
 * \file rbc_89_qre.h
 * \brief Interface for quotient ring elements 
 * */

#ifndef RBC_89_QRE_H
#define RBC_89_QRE_H

#include "rbc_89.h"
#include "random_source.h"

void rbc_89_qre_init_modulus(uint32_t degree);

void rbc_89_qre_clear_modulus(void);

rbc_89_poly_sparse rbc_89_qre_get_modulus(uint32_t degree);

void rbc_89_qre_init(rbc_89_qre* p);

void rbc_89_qre_clear(rbc_89_qre p);

void rbc_89_qre_set_zero(rbc_89_qre o);

void rbc_89_qre_set_random(random_source* ctx, rbc_89_qre o);

void rbc_89_qre_set_random_from_xof(rbc_89_qre o,
                                 void (*xof)(uint8_t *, size_t, const uint8_t *, size_t),
                                 const uint8_t *xof_input,
                                 uint32_t xof_size);

void rbc_89_qre_set_random_full_rank(random_source* ctx, rbc_89_qre o);

void rbc_89_qre_set_random_full_rank_with_one(random_source* ctx, rbc_89_qre o);

void rbc_89_qre_set_random_from_support(random_source* ctx, rbc_89_qre o, const rbc_89_vspace support, uint32_t support_size, uint8_t copy_flag);

void rbc_89_qre_set_random_pair_from_support(random_source* ctx, rbc_89_qre o1, rbc_89_qre o2, const rbc_89_vspace support, uint32_t support_size, uint8_t copy_flag);

uint8_t rbc_89_qre_is_equal_to(const rbc_89_qre p1, const rbc_89_qre p2);

void rbc_89_qre_add(rbc_89_qre o, const rbc_89_qre p1, const rbc_89_qre p2);

void rbc_89_qre_mul(rbc_89_qre o, const rbc_89_qre p1, const rbc_89_qre p2);

void rbc_89_qre_inv(rbc_89_qre o, const rbc_89_qre p);

void rbc_89_qre_to_string(uint8_t* str, const rbc_89_qre p);

void rbc_89_qre_from_string(rbc_89_qre o, const uint8_t* str);

void rbc_89_qre_print(const rbc_89_qre p);

void rbc_89_qre_set_monomial(rbc_89_qre o, uint32_t degree);

void rbc_89_qre_rot(rbc_89_qre o, rbc_89_qre e, uint32_t rot);

#endif

