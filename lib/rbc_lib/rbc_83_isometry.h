/**
 * \file rbc_83_isometry.h
 * \brief Interface isometries over Fq^m
 */

#ifndef RBC_83_ISOMETRY_H
#define RBC_83_ISOMETRY_H

#include "rbc_83.h"
#include "rbc_83_elt.h"
#include "rbc_83_vec.h"
#include "rbc_83_mat_fq.h"
#include "seedexpander.h"

void rbc_83_isometry_init(rbc_83_isometry* o, uint32_t n);
void rbc_83_isometry_clear(rbc_83_isometry* o);
void rbc_83_isometry_set_zero(rbc_83_isometry *iso, uint32_t n);
void rbc_83_isometry_set(rbc_83_isometry *o, const rbc_83_mat_fq P, const rbc_83_mat_fq Q, uint32_t n);
void rbc_83_isometry_set_random(random_source* ctx, rbc_83_isometry *o, uint32_t n);
void rbc_83_isometry_set_random_from_xof(rbc_83_isometry *o,
                                      uint32_t n,
                                      void (*xof)(uint8_t *, size_t, const uint8_t *, size_t),
                                      const uint8_t *xof_input,
                                      uint32_t xof_size);
void rbc_83_isometry_apply(rbc_83_vec o, const rbc_83_vec v, uint32_t n, const rbc_83_isometry *iso);
void rbc_83_isometry_compose(rbc_83_isometry *o, const rbc_83_isometry *iso1, const rbc_83_isometry *iso2);
#endif

