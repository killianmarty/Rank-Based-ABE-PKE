/**
 * \file rbc_181_mat.h
 * \brief Interface for matrices over Fq^m
 */

#ifndef RBC_181_MAT_H
#define RBC_181_MAT_H

#include "rbc_181.h"
#include "rbc_181_elt.h"
#include "rbc_181_vec.h"
#include "seedexpander.h"
#include "seedexpander_shake.h"

void rbc_181_mat_init(rbc_181_mat* m, uint32_t rows, uint32_t columns);
void rbc_181_mat_clear(rbc_181_mat m);
void rbc_181_mat_set_zero(rbc_181_mat m, uint32_t rows, uint32_t columns);
void rbc_181_mat_set(rbc_181_mat o, const rbc_181_mat m, uint32_t rows, uint32_t columns);
void rbc_181_mat_set_random(random_source* ctx, rbc_181_mat o, uint32_t rows, uint32_t columns);
void rbc_181_mat_set_random_tmp(seedexpander_shake_t* ctx, rbc_181_mat o, uint32_t rows, uint32_t columns);
void rbc_181_mat_add(rbc_181_mat o, const rbc_181_mat m1, const rbc_181_mat m2, uint32_t rows, uint32_t columns);
void rbc_181_mat_mul(rbc_181_mat o, const rbc_181_mat m1, const rbc_181_mat m2, uint32_t rows1, uint32_t columns1_rows2, uint32_t columns2);
void rbc_181_mat_vec_mul(rbc_181_vec o, const rbc_181_mat m, const rbc_181_vec v, uint32_t rows, uint32_t columns);
void rbc_181_vec_mat_mul(rbc_181_vec o, const rbc_181_mat m, const rbc_181_vec v, uint32_t rows, uint32_t columns);
void rbc_181_mat_to_string(uint8_t* str, const rbc_181_mat m, uint32_t rows, uint32_t columns);
void rbc_181_mat_from_string(rbc_181_mat m, uint32_t rows, uint32_t columns, const uint8_t* str);
void rbc_181_mat_print(const rbc_181_mat m, uint32_t rows, uint32_t columns);
#endif

