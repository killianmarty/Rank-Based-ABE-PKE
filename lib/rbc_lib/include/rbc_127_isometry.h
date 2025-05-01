/**
 * \file rbc_127_isometry.h
 * \brief Interface isometries over Fq^m
 */

#ifndef RBC_127_ISOMETRY_H
#define RBC_127_ISOMETRY_H

#include "rbc_127.h"
#include "rbc_127_elt.h"
#include "rbc_127_vec.h"
#include "rbc_127_mat_fq.h"
#include "seedexpander.h"

void rbc_127_isometry_init(rbc_127_isometry* o, uint32_t n);
void rbc_127_isometry_clear(rbc_127_isometry* o);
void rbc_127_isometry_set_zero(rbc_127_isometry *iso, uint32_t n);
void rbc_127_isometry_set(rbc_127_isometry *o, const rbc_127_mat_fq P, const rbc_127_mat_fq Q, uint32_t n);
void rbc_127_isometry_set_random(random_source* ctx, rbc_127_isometry *o, uint32_t n);
void rbc_127_isometry_set_random_from_xof(rbc_127_isometry *o,
                                      uint32_t n,
                                      void (*xof)(uint8_t *, size_t, const uint8_t *, size_t),
                                      const uint8_t *xof_input,
                                      uint32_t xof_size);
void rbc_127_isometry_apply(rbc_127_vec o, const rbc_127_vec v, uint32_t n, const rbc_127_isometry *iso);
void rbc_127_isometry_compose(rbc_127_isometry *o, const rbc_127_isometry *iso1, const rbc_127_isometry *iso2);
#endif

