/**
 * \file rbc_83_qre.h
 * \brief Interface for quotient ring elements 
 * */

#ifndef RBC_83_QRE_H
#define RBC_83_QRE_H

#include "rbc_83.h"
#include "random_source.h"

void rbc_83_qre_init_modulus(uint32_t degree);

void rbc_83_qre_clear_modulus(void);

rbc_83_poly_sparse rbc_83_qre_get_modulus(uint32_t degree);

void rbc_83_qre_init(rbc_83_qre* p);

void rbc_83_qre_clear(rbc_83_qre p);

void rbc_83_qre_set_zero(rbc_83_qre o);

void rbc_83_qre_set_random(random_source* ctx, rbc_83_qre o);

void rbc_83_qre_set_random_from_xof(rbc_83_qre o,
                                 void (*xof)(uint8_t *, size_t, const uint8_t *, size_t),
                                 const uint8_t *xof_input,
                                 uint32_t xof_size);

void rbc_83_qre_set_random_full_rank(random_source* ctx, rbc_83_qre o);

void rbc_83_qre_set_random_full_rank_with_one(random_source* ctx, rbc_83_qre o);

void rbc_83_qre_set_random_from_support(random_source* ctx, rbc_83_qre o, const rbc_83_vspace support, uint32_t support_size, uint8_t copy_flag);

void rbc_83_qre_set_random_pair_from_support(random_source* ctx, rbc_83_qre o1, rbc_83_qre o2, const rbc_83_vspace support, uint32_t support_size, uint8_t copy_flag);

uint8_t rbc_83_qre_is_equal_to(const rbc_83_qre p1, const rbc_83_qre p2);

void rbc_83_qre_add(rbc_83_qre o, const rbc_83_qre p1, const rbc_83_qre p2);

void rbc_83_qre_mul(rbc_83_qre o, const rbc_83_qre p1, const rbc_83_qre p2);

void rbc_83_qre_inv(rbc_83_qre o, const rbc_83_qre p);

void rbc_83_qre_to_string(uint8_t* str, const rbc_83_qre p);

void rbc_83_qre_from_string(rbc_83_qre o, const uint8_t* str);

void rbc_83_qre_print(const rbc_83_qre p);

void rbc_83_qre_set_monomial(rbc_83_qre o, uint32_t degree);

void rbc_83_qre_rot(rbc_83_qre o, rbc_83_qre e, uint32_t rot);

#endif

