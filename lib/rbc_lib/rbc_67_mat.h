/**
 * \file rbc_67_mat.h
 * \brief Interface for matrices over Fq^m
 */

#ifndef RBC_67_MAT_H
#define RBC_67_MAT_H

#include "rbc_67.h"
#include "rbc_67_elt.h"
#include "rbc_67_vec.h"
#include "seedexpander.h"
#include "seedexpander_shake.h"

void rbc_67_mat_init(rbc_67_mat* m, uint32_t rows, uint32_t columns);
void rbc_67_mat_clear(rbc_67_mat m);
void rbc_67_mat_set_zero(rbc_67_mat m, uint32_t rows, uint32_t columns);
void rbc_67_mat_set(rbc_67_mat o, const rbc_67_mat m, uint32_t rows, uint32_t columns);
void rbc_67_mat_set_random(random_source* ctx, rbc_67_mat o, uint32_t rows, uint32_t columns);
void rbc_67_mat_set_random_tmp(seedexpander_shake_t* ctx, rbc_67_mat o, uint32_t rows, uint32_t columns);
void rbc_67_mat_add(rbc_67_mat o, const rbc_67_mat m1, const rbc_67_mat m2, uint32_t rows, uint32_t columns);
void rbc_67_mat_mul(rbc_67_mat o, const rbc_67_mat m1, const rbc_67_mat m2, uint32_t rows1, uint32_t columns1_rows2, uint32_t columns2);
void rbc_67_mat_vec_mul(rbc_67_vec o, const rbc_67_mat m, const rbc_67_vec v, uint32_t rows, uint32_t columns);
void rbc_67_vec_mat_mul(rbc_67_vec o, const rbc_67_mat m, const rbc_67_vec v, uint32_t rows, uint32_t columns);
void rbc_67_mat_to_string(uint8_t* str, const rbc_67_mat m, uint32_t rows, uint32_t columns);
void rbc_67_mat_from_string(rbc_67_mat m, uint32_t rows, uint32_t columns, const uint8_t* str);
void rbc_67_mat_print(const rbc_67_mat m, uint32_t rows, uint32_t columns);
#endif

