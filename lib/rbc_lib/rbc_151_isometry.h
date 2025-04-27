/**
 * \file rbc_151_isometry.h
 * \brief Interface isometries over Fq^m
 */

#ifndef RBC_151_ISOMETRY_H
#define RBC_151_ISOMETRY_H

#include "rbc_151.h"
#include "rbc_151_elt.h"
#include "rbc_151_vec.h"
#include "rbc_151_mat_fq.h"
#include "seedexpander.h"

void rbc_151_isometry_init(rbc_151_isometry* o, uint32_t n);
void rbc_151_isometry_clear(rbc_151_isometry* o);
void rbc_151_isometry_set_zero(rbc_151_isometry *iso, uint32_t n);
void rbc_151_isometry_set(rbc_151_isometry *o, const rbc_151_mat_fq P, const rbc_151_mat_fq Q, uint32_t n);
void rbc_151_isometry_set_random(random_source* ctx, rbc_151_isometry *o, uint32_t n);
void rbc_151_isometry_set_random_from_xof(rbc_151_isometry *o,
                                      uint32_t n,
                                      void (*xof)(uint8_t *, size_t, const uint8_t *, size_t),
                                      const uint8_t *xof_input,
                                      uint32_t xof_size);
void rbc_151_isometry_apply(rbc_151_vec o, const rbc_151_vec v, uint32_t n, const rbc_151_isometry *iso);
void rbc_151_isometry_compose(rbc_151_isometry *o, const rbc_151_isometry *iso1, const rbc_151_isometry *iso2);
#endif

