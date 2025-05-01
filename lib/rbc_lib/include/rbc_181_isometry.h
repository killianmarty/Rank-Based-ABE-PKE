/**
 * \file rbc_181_isometry.h
 * \brief Interface isometries over Fq^m
 */

#ifndef RBC_181_ISOMETRY_H
#define RBC_181_ISOMETRY_H

#include "rbc_181.h"
#include "rbc_181_elt.h"
#include "rbc_181_vec.h"
#include "rbc_181_mat_fq.h"
#include "seedexpander.h"

void rbc_181_isometry_init(rbc_181_isometry* o, uint32_t n);
void rbc_181_isometry_clear(rbc_181_isometry* o);
void rbc_181_isometry_set_zero(rbc_181_isometry *iso, uint32_t n);
void rbc_181_isometry_set(rbc_181_isometry *o, const rbc_181_mat_fq P, const rbc_181_mat_fq Q, uint32_t n);
void rbc_181_isometry_set_random(random_source* ctx, rbc_181_isometry *o, uint32_t n);
void rbc_181_isometry_set_random_from_xof(rbc_181_isometry *o,
                                      uint32_t n,
                                      void (*xof)(uint8_t *, size_t, const uint8_t *, size_t),
                                      const uint8_t *xof_input,
                                      uint32_t xof_size);
void rbc_181_isometry_apply(rbc_181_vec o, const rbc_181_vec v, uint32_t n, const rbc_181_isometry *iso);
void rbc_181_isometry_compose(rbc_181_isometry *o, const rbc_181_isometry *iso1, const rbc_181_isometry *iso2);
#endif

