/**
 * \file rbc_181_mat_fq.h
 * \brief Interface for matrices over Fq
 */

#ifndef RBC_181_MAT_FQ_H
#define RBC_181_MAT_FQ_H

#include "rbc_181.h"
#include "rbc_181_elt.h"
#include "rbc_181_vec.h"
#include "rbc_181_perm.h"
#include "seedexpander.h"

void rbc_181_mat_fq_init(rbc_181_mat_fq* m, uint32_t rows, uint32_t columns);
void rbc_181_mat_fq_clear(rbc_181_mat_fq m);
void rbc_181_mat_fq_set_zero(rbc_181_mat_fq m, uint32_t rows, uint32_t columns);
void rbc_181_mat_fq_set_identity(rbc_181_mat_fq m, uint32_t rows, uint32_t columns);
void rbc_181_mat_fq_set(rbc_181_mat_fq o, const rbc_181_mat_fq m, uint32_t rows, uint32_t columns);
void rbc_181_mat_fq_set_random(random_source* ctx, rbc_181_mat_fq o, uint32_t rows, uint32_t columns);
void rbc_181_mat_fq_set_transpose(rbc_181_mat_fq o, const rbc_181_mat_fq m, uint32_t rows, uint32_t columns);
void rbc_181_mat_fq_set_inverse(rbc_181_mat_fq o, const rbc_181_mat_fq m, uint32_t size);
void rbc_181_mat_fq_mul(rbc_181_mat_fq o, const rbc_181_mat_fq m1, const rbc_181_mat_fq m2, uint32_t rows1, uint32_t columns1_rows2, uint32_t columns2);
void rbc_181_mat_fq_tr_mul(rbc_181_mat_fq o, const rbc_181_mat_fq m1, const rbc_181_mat_fq m2, uint32_t rows1, uint32_t columns, uint32_t rows2);
void rbc_181_tr_mat_fq_mul(rbc_181_mat_fq o, const rbc_181_mat_fq m1, const rbc_181_mat_fq m2, uint32_t rows, uint32_t columns1, uint32_t columns2);
void rbc_181_mat_fq_minmax(rbc_181_mat_fq c1, uint64_t* x, rbc_181_mat_fq c2, uint64_t* y, uint32_t size);
void rbc_181_mat_fq_gen(random_source* ctx, rbc_181_perm perm, rbc_181_mat_fq t, uint32_t size);
void rbc_181_mat_fq_gen_from_xof(rbc_181_perm perm,
                             rbc_181_mat_fq t,
                             uint32_t size, void (*xof)(uint8_t *, size_t, const uint8_t *, size_t),
                             const uint8_t *xof_input,
                             uint32_t xof_size);
void rbc_181_mat_fq_vec_mul(rbc_181_vec o, const rbc_181_mat_fq m, const rbc_181_vec v, uint32_t rows, uint32_t columns);
void rbc_181_vec_mat_fq_mul(rbc_181_vec o, const rbc_181_mat_fq m, const rbc_181_vec v, uint32_t rows, uint32_t columns);
void rbc_181_tr_mat_fq_vec_mul(rbc_181_vec o, const rbc_181_mat_fq m, const rbc_181_vec v, uint32_t size);
void rbc_181_vec_mat_fq_tr_mul(rbc_181_vec o, const rbc_181_vec v, const rbc_181_mat_fq m, uint32_t size);
void rbc_181_mat_fq_to_string(uint8_t* str, const rbc_181_mat_fq m, uint32_t rows, uint32_t columns);
void rbc_181_mat_fq_from_string(rbc_181_mat_fq m, uint32_t rows, uint32_t columns, const uint8_t* str);
void rbc_181_mat_fq_print(const rbc_181_mat_fq m, uint32_t rows, uint32_t columns);
void rbc_181_vec_mat_fq_compress(rbc_181_vec basis, rbc_181_vec lcomb, const rbc_181_vec v, uint32_t size, uint32_t w);
void rbc_181_vec_mat_fq_decompress(rbc_181_vec v, const rbc_181_vec basis, const rbc_181_vec lcomb, uint32_t size, uint32_t w);
#endif

