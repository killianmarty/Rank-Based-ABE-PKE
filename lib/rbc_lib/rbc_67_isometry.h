/**
 * \file rbc_67_isometry.h
 * \brief Interface isometries over Fq^m
 */

#ifndef RBC_67_ISOMETRY_H
#define RBC_67_ISOMETRY_H

#include "rbc_67.h"
#include "rbc_67_elt.h"
#include "rbc_67_vec.h"
#include "rbc_67_mat_fq.h"
#include "seedexpander.h"

void rbc_67_isometry_init(rbc_67_isometry* o, uint32_t n);
void rbc_67_isometry_clear(rbc_67_isometry* o);
void rbc_67_isometry_set_zero(rbc_67_isometry *iso, uint32_t n);
void rbc_67_isometry_set(rbc_67_isometry *o, const rbc_67_mat_fq P, const rbc_67_mat_fq Q, uint32_t n);
void rbc_67_isometry_set_random(random_source* ctx, rbc_67_isometry *o, uint32_t n);
void rbc_67_isometry_set_random_from_xof(rbc_67_isometry *o,
                                      uint32_t n,
                                      void (*xof)(uint8_t *, size_t, const uint8_t *, size_t),
                                      const uint8_t *xof_input,
                                      uint32_t xof_size);
void rbc_67_isometry_apply(rbc_67_vec o, const rbc_67_vec v, uint32_t n, const rbc_67_isometry *iso);
void rbc_67_isometry_compose(rbc_67_isometry *o, const rbc_67_isometry *iso1, const rbc_67_isometry *iso2);
#endif

