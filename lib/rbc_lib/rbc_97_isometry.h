/**
 * \file rbc_97_isometry.h
 * \brief Interface isometries over Fq^m
 */

#ifndef RBC_97_ISOMETRY_H
#define RBC_97_ISOMETRY_H

#include "rbc_97.h"
#include "rbc_97_elt.h"
#include "rbc_97_vec.h"
#include "rbc_97_mat_fq.h"
#include "seedexpander.h"

void rbc_97_isometry_init(rbc_97_isometry* o, uint32_t n);
void rbc_97_isometry_clear(rbc_97_isometry* o);
void rbc_97_isometry_set_zero(rbc_97_isometry *iso, uint32_t n);
void rbc_97_isometry_set(rbc_97_isometry *o, const rbc_97_mat_fq P, const rbc_97_mat_fq Q, uint32_t n);
void rbc_97_isometry_set_random(random_source* ctx, rbc_97_isometry *o, uint32_t n);
void rbc_97_isometry_set_random_from_xof(rbc_97_isometry *o,
                                      uint32_t n,
                                      void (*xof)(uint8_t *, size_t, const uint8_t *, size_t),
                                      const uint8_t *xof_input,
                                      uint32_t xof_size);
void rbc_97_isometry_apply(rbc_97_vec o, const rbc_97_vec v, uint32_t n, const rbc_97_isometry *iso);
void rbc_97_isometry_compose(rbc_97_isometry *o, const rbc_97_isometry *iso1, const rbc_97_isometry *iso2);
#endif

