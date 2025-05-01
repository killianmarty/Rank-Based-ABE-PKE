/**
 * \file gabidulin.h
 * \brief Functions to encode and decode messages using Gabidulin codes
 *
 * The decoding algorithm provided is based on q_polynomials reconstruction, see \cite gabidulin:welch and \cite gabidulin:generalized for details.
 *
 */

#ifndef RBC_181_GABIDULIN_H
#define RBC_181_GABIDULIN_H

#include "rbc_181_vec.h"
#include "rbc_181_qre.h"


/**
  * \typedef rbc_181_gabidulin
  * \brief Structure of a gabidulin code
  */
typedef struct rbc_181_gabidulin {
  rbc_181_poly g; /**< Generator vector defining the code */
  uint32_t k; /**< Size of vectors representing messages */
  uint32_t n; /**< Size of vectors representing codewords */
} rbc_181_gabidulin;


void rbc_181_gabidulin_init(rbc_181_gabidulin* code, const rbc_181_poly g, uint32_t k, uint32_t n);

void rbc_181_gabidulin_encode(rbc_181_qre c, const rbc_181_gabidulin gc, const rbc_181_vec m);
void rbc_181_gabidulin_decode(rbc_181_vec m, const rbc_181_gabidulin gc, const rbc_181_qre y);

#endif

