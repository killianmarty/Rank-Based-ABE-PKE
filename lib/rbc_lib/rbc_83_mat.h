/**
 * \file rbc_83_mat.h
 * \brief Interface for matrices over Fq^m
 */

#ifndef RBC_83_MAT_H
#define RBC_83_MAT_H

#include "rbc_83.h"
#include "rbc_83_elt.h"
#include "rbc_83_vec.h"
#include "seedexpander.h"
#include "seedexpander_shake.h"

void rbc_83_mat_init(rbc_83_mat* m, uint32_t rows, uint32_t columns);
void rbc_83_mat_clear(rbc_83_mat m);
void rbc_83_mat_set_zero(rbc_83_mat m, uint32_t rows, uint32_t columns);
void rbc_83_mat_set(rbc_83_mat o, const rbc_83_mat m, uint32_t rows, uint32_t columns);
void rbc_83_mat_set_random(random_source* ctx, rbc_83_mat o, uint32_t rows, uint32_t columns);
void rbc_83_mat_set_random_tmp(seedexpander_shake_t* ctx, rbc_83_mat o, uint32_t rows, uint32_t columns);
void rbc_83_mat_add(rbc_83_mat o, const rbc_83_mat m1, const rbc_83_mat m2, uint32_t rows, uint32_t columns);
void rbc_83_mat_mul(rbc_83_mat o, const rbc_83_mat m1, const rbc_83_mat m2, uint32_t rows1, uint32_t columns1_rows2, uint32_t columns2);
void rbc_83_mat_vec_mul(rbc_83_vec o, const rbc_83_mat m, const rbc_83_vec v, uint32_t rows, uint32_t columns);
void rbc_83_vec_mat_mul(rbc_83_vec o, const rbc_83_mat m, const rbc_83_vec v, uint32_t rows, uint32_t columns);
void rbc_83_mat_to_string(uint8_t* str, const rbc_83_mat m, uint32_t rows, uint32_t columns);
void rbc_83_mat_from_string(rbc_83_mat m, uint32_t rows, uint32_t columns, const uint8_t* str);
void rbc_83_mat_print(const rbc_83_mat m, uint32_t rows, uint32_t columns);
#endif

