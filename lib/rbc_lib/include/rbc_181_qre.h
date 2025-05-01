/**
 * \file rbc_181_qre.h
 * \brief Interface for quotient ring elements 
 * */

#ifndef RBC_181_QRE_H
#define RBC_181_QRE_H

#include "rbc_181.h"
#include "random_source.h"

void rbc_181_qre_init_modulus(uint32_t degree);

void rbc_181_qre_clear_modulus(void);

rbc_181_poly_sparse rbc_181_qre_get_modulus(uint32_t degree);

void rbc_181_qre_init(rbc_181_qre* p);

void rbc_181_qre_clear(rbc_181_qre p);

void rbc_181_qre_set_zero(rbc_181_qre o);

void rbc_181_qre_set_random(random_source* ctx, rbc_181_qre o);

void rbc_181_qre_set_random_from_xof(rbc_181_qre o,
                                 void (*xof)(uint8_t *, size_t, const uint8_t *, size_t),
                                 const uint8_t *xof_input,
                                 uint32_t xof_size);

void rbc_181_qre_set_random_full_rank(random_source* ctx, rbc_181_qre o);

void rbc_181_qre_set_random_full_rank_with_one(random_source* ctx, rbc_181_qre o);

void rbc_181_qre_set_random_from_support(random_source* ctx, rbc_181_qre o, const rbc_181_vspace support, uint32_t support_size, uint8_t copy_flag);

void rbc_181_qre_set_random_pair_from_support(random_source* ctx, rbc_181_qre o1, rbc_181_qre o2, const rbc_181_vspace support, uint32_t support_size, uint8_t copy_flag);

uint8_t rbc_181_qre_is_equal_to(const rbc_181_qre p1, const rbc_181_qre p2);

void rbc_181_qre_add(rbc_181_qre o, const rbc_181_qre p1, const rbc_181_qre p2);

void rbc_181_qre_mul(rbc_181_qre o, const rbc_181_qre p1, const rbc_181_qre p2);

void rbc_181_qre_inv(rbc_181_qre o, const rbc_181_qre p);

void rbc_181_qre_to_string(uint8_t* str, const rbc_181_qre p);

void rbc_181_qre_from_string(rbc_181_qre o, const uint8_t* str);

void rbc_181_qre_print(const rbc_181_qre p);

void rbc_181_qre_set_monomial(rbc_181_qre o, uint32_t degree);

void rbc_181_qre_rot(rbc_181_qre o, rbc_181_qre e, uint32_t rot);

#endif

