/**
 * \file rbc_89_mat.h
 * \brief Interface for matrices over Fq^m
 */

#ifndef RBC_89_MAT_H
#define RBC_89_MAT_H

#include "rbc_89.h"
#include "rbc_89_elt.h"
#include "rbc_89_vec.h"
#include "seedexpander.h"
#include "seedexpander_shake.h"

void rbc_89_mat_init(rbc_89_mat* m, uint32_t rows, uint32_t columns);
void rbc_89_mat_clear(rbc_89_mat m);
void rbc_89_mat_set_zero(rbc_89_mat m, uint32_t rows, uint32_t columns);
void rbc_89_mat_set(rbc_89_mat o, const rbc_89_mat m, uint32_t rows, uint32_t columns);
void rbc_89_mat_set_random(random_source* ctx, rbc_89_mat o, uint32_t rows, uint32_t columns);
void rbc_89_mat_set_random_tmp(seedexpander_shake_t* ctx, rbc_89_mat o, uint32_t rows, uint32_t columns);
void rbc_89_mat_add(rbc_89_mat o, const rbc_89_mat m1, const rbc_89_mat m2, uint32_t rows, uint32_t columns);
void rbc_89_mat_mul(rbc_89_mat o, const rbc_89_mat m1, const rbc_89_mat m2, uint32_t rows1, uint32_t columns1_rows2, uint32_t columns2);
void rbc_89_mat_vec_mul(rbc_89_vec o, const rbc_89_mat m, const rbc_89_vec v, uint32_t rows, uint32_t columns);
void rbc_89_vec_mat_mul(rbc_89_vec o, const rbc_89_mat m, const rbc_89_vec v, uint32_t rows, uint32_t columns);
void rbc_89_mat_to_string(uint8_t* str, const rbc_89_mat m, uint32_t rows, uint32_t columns);
void rbc_89_mat_from_string(rbc_89_mat m, uint32_t rows, uint32_t columns, const uint8_t* str);
void rbc_89_mat_print(const rbc_89_mat m, uint32_t rows, uint32_t columns);
#endif

