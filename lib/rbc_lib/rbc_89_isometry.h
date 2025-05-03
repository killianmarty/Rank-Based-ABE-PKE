/**
 * \file rbc_89_isometry.h
 * \brief Interface isometries over Fq^m
 */

#ifndef RBC_89_ISOMETRY_H
#define RBC_89_ISOMETRY_H

#include "rbc_89.h"
#include "rbc_89_elt.h"
#include "rbc_89_vec.h"
#include "rbc_89_mat_fq.h"
#include "seedexpander.h"

void rbc_89_isometry_init(rbc_89_isometry* o, uint32_t n);
void rbc_89_isometry_clear(rbc_89_isometry* o);
void rbc_89_isometry_set_zero(rbc_89_isometry *iso, uint32_t n);
void rbc_89_isometry_set(rbc_89_isometry *o, const rbc_89_mat_fq P, const rbc_89_mat_fq Q, uint32_t n);
void rbc_89_isometry_set_random(random_source* ctx, rbc_89_isometry *o, uint32_t n);
void rbc_89_isometry_set_random_from_xof(rbc_89_isometry *o,
                                      uint32_t n,
                                      void (*xof)(uint8_t *, size_t, const uint8_t *, size_t),
                                      const uint8_t *xof_input,
                                      uint32_t xof_size);
void rbc_89_isometry_apply(rbc_89_vec o, const rbc_89_vec v, uint32_t n, const rbc_89_isometry *iso);
void rbc_89_isometry_compose(rbc_89_isometry *o, const rbc_89_isometry *iso1, const rbc_89_isometry *iso2);
#endif

