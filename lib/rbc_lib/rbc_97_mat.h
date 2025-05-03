/**
 * \file rbc_97_mat.h
 * \brief Interface for matrices over Fq^m
 */

#ifndef RBC_97_MAT_H
#define RBC_97_MAT_H

#include "rbc_97.h"
#include "rbc_97_elt.h"
#include "rbc_97_vec.h"
#include "seedexpander.h"
#include "seedexpander_shake.h"

void rbc_97_mat_init(rbc_97_mat* m, uint32_t rows, uint32_t columns);
void rbc_97_mat_clear(rbc_97_mat m);
void rbc_97_mat_set_zero(rbc_97_mat m, uint32_t rows, uint32_t columns);
void rbc_97_mat_set(rbc_97_mat o, const rbc_97_mat m, uint32_t rows, uint32_t columns);
void rbc_97_mat_set_random(random_source* ctx, rbc_97_mat o, uint32_t rows, uint32_t columns);
void rbc_97_mat_set_random_tmp(seedexpander_shake_t* ctx, rbc_97_mat o, uint32_t rows, uint32_t columns);
void rbc_97_mat_add(rbc_97_mat o, const rbc_97_mat m1, const rbc_97_mat m2, uint32_t rows, uint32_t columns);
void rbc_97_mat_mul(rbc_97_mat o, const rbc_97_mat m1, const rbc_97_mat m2, uint32_t rows1, uint32_t columns1_rows2, uint32_t columns2);
void rbc_97_mat_vec_mul(rbc_97_vec o, const rbc_97_mat m, const rbc_97_vec v, uint32_t rows, uint32_t columns);
void rbc_97_vec_mat_mul(rbc_97_vec o, const rbc_97_mat m, const rbc_97_vec v, uint32_t rows, uint32_t columns);
void rbc_97_mat_to_string(uint8_t* str, const rbc_97_mat m, uint32_t rows, uint32_t columns);
void rbc_97_mat_from_string(rbc_97_mat m, uint32_t rows, uint32_t columns, const uint8_t* str);
void rbc_97_mat_print(const rbc_97_mat m, uint32_t rows, uint32_t columns);
#endif

