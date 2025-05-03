/**
 * \file rbc_83_mat_fq.h
 * \brief Interface for matrices over Fq
 */

#ifndef RBC_83_MAT_FQ_H
#define RBC_83_MAT_FQ_H

#include "rbc_83.h"
#include "rbc_83_elt.h"
#include "rbc_83_vec.h"
#include "rbc_83_perm.h"
#include "seedexpander.h"

void rbc_83_mat_fq_init(rbc_83_mat_fq* m, uint32_t rows, uint32_t columns);
void rbc_83_mat_fq_clear(rbc_83_mat_fq m);
void rbc_83_mat_fq_set_zero(rbc_83_mat_fq m, uint32_t rows, uint32_t columns);
void rbc_83_mat_fq_set_identity(rbc_83_mat_fq m, uint32_t rows, uint32_t columns);
void rbc_83_mat_fq_set(rbc_83_mat_fq o, const rbc_83_mat_fq m, uint32_t rows, uint32_t columns);
void rbc_83_mat_fq_set_random(random_source* ctx, rbc_83_mat_fq o, uint32_t rows, uint32_t columns);
void rbc_83_mat_fq_set_transpose(rbc_83_mat_fq o, const rbc_83_mat_fq m, uint32_t rows, uint32_t columns);
void rbc_83_mat_fq_set_inverse(rbc_83_mat_fq o, const rbc_83_mat_fq m, uint32_t size);
void rbc_83_mat_fq_mul(rbc_83_mat_fq o, const rbc_83_mat_fq m1, const rbc_83_mat_fq m2, uint32_t rows1, uint32_t columns1_rows2, uint32_t columns2);
void rbc_83_mat_fq_tr_mul(rbc_83_mat_fq o, const rbc_83_mat_fq m1, const rbc_83_mat_fq m2, uint32_t rows1, uint32_t columns, uint32_t rows2);
void rbc_83_tr_mat_fq_mul(rbc_83_mat_fq o, const rbc_83_mat_fq m1, const rbc_83_mat_fq m2, uint32_t rows, uint32_t columns1, uint32_t columns2);
void rbc_83_mat_fq_minmax(rbc_83_mat_fq c1, uint64_t* x, rbc_83_mat_fq c2, uint64_t* y, uint32_t size);
void rbc_83_mat_fq_gen(random_source* ctx, rbc_83_perm perm, rbc_83_mat_fq t, uint32_t size);
void rbc_83_mat_fq_gen_from_xof(rbc_83_perm perm,
                             rbc_83_mat_fq t,
                             uint32_t size, void (*xof)(uint8_t *, size_t, const uint8_t *, size_t),
                             const uint8_t *xof_input,
                             uint32_t xof_size);
void rbc_83_mat_fq_vec_mul(rbc_83_vec o, const rbc_83_mat_fq m, const rbc_83_vec v, uint32_t rows, uint32_t columns);
void rbc_83_vec_mat_fq_mul(rbc_83_vec o, const rbc_83_mat_fq m, const rbc_83_vec v, uint32_t rows, uint32_t columns);
void rbc_83_tr_mat_fq_vec_mul(rbc_83_vec o, const rbc_83_mat_fq m, const rbc_83_vec v, uint32_t size);
void rbc_83_vec_mat_fq_tr_mul(rbc_83_vec o, const rbc_83_vec v, const rbc_83_mat_fq m, uint32_t size);
void rbc_83_mat_fq_to_string(uint8_t* str, const rbc_83_mat_fq m, uint32_t rows, uint32_t columns);
void rbc_83_mat_fq_from_string(rbc_83_mat_fq m, uint32_t rows, uint32_t columns, const uint8_t* str);
void rbc_83_mat_fq_print(const rbc_83_mat_fq m, uint32_t rows, uint32_t columns);
void rbc_83_vec_mat_fq_compress(rbc_83_vec basis, rbc_83_vec lcomb, const rbc_83_vec v, uint32_t size, uint32_t w);
void rbc_83_vec_mat_fq_decompress(rbc_83_vec v, const rbc_83_vec basis, const rbc_83_vec lcomb, uint32_t size, uint32_t w);
#endif

