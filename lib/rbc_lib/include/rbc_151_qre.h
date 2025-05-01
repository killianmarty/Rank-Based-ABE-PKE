/**
 * \file rbc_151_qre.h
 * \brief Interface for quotient ring elements 
 * */

#ifndef RBC_151_QRE_H
#define RBC_151_QRE_H

#include "rbc_151.h"
#include "random_source.h"

void rbc_151_qre_init_modulus(uint32_t degree);

void rbc_151_qre_clear_modulus(void);

rbc_151_poly_sparse rbc_151_qre_get_modulus(uint32_t degree);

void rbc_151_qre_init(rbc_151_qre* p);

void rbc_151_qre_clear(rbc_151_qre p);

void rbc_151_qre_set_zero(rbc_151_qre o);

void rbc_151_qre_set_random(random_source* ctx, rbc_151_qre o);

void rbc_151_qre_set_random_from_xof(rbc_151_qre o,
                                 void (*xof)(uint8_t *, size_t, const uint8_t *, size_t),
                                 const uint8_t *xof_input,
                                 uint32_t xof_size);

void rbc_151_qre_set_random_full_rank(random_source* ctx, rbc_151_qre o);

void rbc_151_qre_set_random_full_rank_with_one(random_source* ctx, rbc_151_qre o);

void rbc_151_qre_set_random_from_support(random_source* ctx, rbc_151_qre o, const rbc_151_vspace support, uint32_t support_size, uint8_t copy_flag);

void rbc_151_qre_set_random_pair_from_support(random_source* ctx, rbc_151_qre o1, rbc_151_qre o2, const rbc_151_vspace support, uint32_t support_size, uint8_t copy_flag);

uint8_t rbc_151_qre_is_equal_to(const rbc_151_qre p1, const rbc_151_qre p2);

void rbc_151_qre_add(rbc_151_qre o, const rbc_151_qre p1, const rbc_151_qre p2);

void rbc_151_qre_mul(rbc_151_qre o, const rbc_151_qre p1, const rbc_151_qre p2);

void rbc_151_qre_inv(rbc_151_qre o, const rbc_151_qre p);

void rbc_151_qre_to_string(uint8_t* str, const rbc_151_qre p);

void rbc_151_qre_from_string(rbc_151_qre o, const uint8_t* str);

void rbc_151_qre_print(const rbc_151_qre p);

void rbc_151_qre_set_monomial(rbc_151_qre o, uint32_t degree);

void rbc_151_qre_rot(rbc_151_qre o, rbc_151_qre e, uint32_t rot);

#endif

