/**
 * \file rbc_67_qre.h
 * \brief Interface for quotient ring elements 
 * */

#ifndef RBC_67_QRE_H
#define RBC_67_QRE_H

#include "rbc_67.h"
#include "random_source.h"

void rbc_67_qre_init_modulus(uint32_t degree);

void rbc_67_qre_clear_modulus(void);

rbc_67_poly_sparse rbc_67_qre_get_modulus(uint32_t degree);

void rbc_67_qre_init(rbc_67_qre* p);

void rbc_67_qre_clear(rbc_67_qre p);

void rbc_67_qre_set_zero(rbc_67_qre o);

void rbc_67_qre_set_random(random_source* ctx, rbc_67_qre o);

void rbc_67_qre_set_random_from_xof(rbc_67_qre o,
                                 void (*xof)(uint8_t *, size_t, const uint8_t *, size_t),
                                 const uint8_t *xof_input,
                                 uint32_t xof_size);

void rbc_67_qre_set_random_full_rank(random_source* ctx, rbc_67_qre o);

void rbc_67_qre_set_random_full_rank_with_one(random_source* ctx, rbc_67_qre o);

void rbc_67_qre_set_random_from_support(random_source* ctx, rbc_67_qre o, const rbc_67_vspace support, uint32_t support_size, uint8_t copy_flag);

void rbc_67_qre_set_random_pair_from_support(random_source* ctx, rbc_67_qre o1, rbc_67_qre o2, const rbc_67_vspace support, uint32_t support_size, uint8_t copy_flag);

uint8_t rbc_67_qre_is_equal_to(const rbc_67_qre p1, const rbc_67_qre p2);

void rbc_67_qre_add(rbc_67_qre o, const rbc_67_qre p1, const rbc_67_qre p2);

void rbc_67_qre_mul(rbc_67_qre o, const rbc_67_qre p1, const rbc_67_qre p2);

void rbc_67_qre_inv(rbc_67_qre o, const rbc_67_qre p);

void rbc_67_qre_to_string(uint8_t* str, const rbc_67_qre p);

void rbc_67_qre_from_string(rbc_67_qre o, const uint8_t* str);

void rbc_67_qre_print(const rbc_67_qre p);

void rbc_67_qre_set_monomial(rbc_67_qre o, uint32_t degree);

void rbc_67_qre_rot(rbc_67_qre o, rbc_67_qre e, uint32_t rot);

#endif

