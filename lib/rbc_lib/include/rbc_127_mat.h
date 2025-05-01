/**
 * \file rbc_127_mat.h
 * \brief Interface for matrices over Fq^m
 */

#ifndef RBC_127_MAT_H
#define RBC_127_MAT_H

#include "rbc_127.h"
#include "rbc_127_elt.h"
#include "rbc_127_vec.h"
#include "seedexpander.h"
#include "seedexpander_shake.h"

void rbc_127_mat_init(rbc_127_mat* m, uint32_t rows, uint32_t columns);
void rbc_127_mat_clear(rbc_127_mat m);
void rbc_127_mat_set_zero(rbc_127_mat m, uint32_t rows, uint32_t columns);
void rbc_127_mat_set(rbc_127_mat o, const rbc_127_mat m, uint32_t rows, uint32_t columns);
void rbc_127_mat_set_random(random_source* ctx, rbc_127_mat o, uint32_t rows, uint32_t columns);
void rbc_127_mat_set_random_tmp(seedexpander_shake_t* ctx, rbc_127_mat o, uint32_t rows, uint32_t columns);
void rbc_127_mat_add(rbc_127_mat o, const rbc_127_mat m1, const rbc_127_mat m2, uint32_t rows, uint32_t columns);
void rbc_127_mat_mul(rbc_127_mat o, const rbc_127_mat m1, const rbc_127_mat m2, uint32_t rows1, uint32_t columns1_rows2, uint32_t columns2);
void rbc_127_mat_vec_mul(rbc_127_vec o, const rbc_127_mat m, const rbc_127_vec v, uint32_t rows, uint32_t columns);
void rbc_127_vec_mat_mul(rbc_127_vec o, const rbc_127_mat m, const rbc_127_vec v, uint32_t rows, uint32_t columns);
void rbc_127_mat_to_string(uint8_t* str, const rbc_127_mat m, uint32_t rows, uint32_t columns);
void rbc_127_mat_from_string(rbc_127_mat m, uint32_t rows, uint32_t columns, const uint8_t* str);
void rbc_127_mat_print(const rbc_127_mat m, uint32_t rows, uint32_t columns);
#endif

