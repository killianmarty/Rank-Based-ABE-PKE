/**
 * \file rbc_151_mat.h
 * \brief Interface for matrices over Fq^m
 */

#ifndef RBC_151_MAT_H
#define RBC_151_MAT_H

#include "rbc_151.h"
#include "rbc_151_elt.h"
#include "rbc_151_vec.h"
#include "seedexpander.h"
#include "seedexpander_shake.h"

void rbc_151_mat_init(rbc_151_mat* m, uint32_t rows, uint32_t columns);
void rbc_151_mat_clear(rbc_151_mat m);
void rbc_151_mat_set_zero(rbc_151_mat m, uint32_t rows, uint32_t columns);
void rbc_151_mat_set(rbc_151_mat o, const rbc_151_mat m, uint32_t rows, uint32_t columns);
void rbc_151_mat_set_random(random_source* ctx, rbc_151_mat o, uint32_t rows, uint32_t columns);
void rbc_151_mat_set_random_tmp(seedexpander_shake_t* ctx, rbc_151_mat o, uint32_t rows, uint32_t columns);
void rbc_151_mat_add(rbc_151_mat o, const rbc_151_mat m1, const rbc_151_mat m2, uint32_t rows, uint32_t columns);
void rbc_151_mat_mul(rbc_151_mat o, const rbc_151_mat m1, const rbc_151_mat m2, uint32_t rows1, uint32_t columns1_rows2, uint32_t columns2);
void rbc_151_mat_vec_mul(rbc_151_vec o, const rbc_151_mat m, const rbc_151_vec v, uint32_t rows, uint32_t columns);
void rbc_151_vec_mat_mul(rbc_151_vec o, const rbc_151_mat m, const rbc_151_vec v, uint32_t rows, uint32_t columns);
void rbc_151_mat_to_string(uint8_t* str, const rbc_151_mat m, uint32_t rows, uint32_t columns);
void rbc_151_mat_from_string(rbc_151_mat m, uint32_t rows, uint32_t columns, const uint8_t* str);
void rbc_151_mat_print(const rbc_151_mat m, uint32_t rows, uint32_t columns);
#endif

