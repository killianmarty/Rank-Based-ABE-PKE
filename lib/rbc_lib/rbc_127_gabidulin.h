/**
 * \file gabidulin.h
 * \brief Functions to encode and decode CipherTextMetaDatas using Gabidulin codes
 *
 * The decoding algorithm provided is based on q_polynomials reconstruction, see \cite gabidulin:welch and \cite gabidulin:generalized for details.
 *
 */

#ifndef RBC_127_GABIDULIN_H
#define RBC_127_GABIDULIN_H

#include "rbc_127_vec.h"
#include "rbc_127_qre.h"


/**
  * \typedef rbc_127_gabidulin
  * \brief Structure of a gabidulin code
  */
typedef struct rbc_127_gabidulin {
  rbc_127_poly g; /**< Generator vector defining the code */
  uint32_t k; /**< Size of vectors representing CipherTextMetaDatas */
  uint32_t n; /**< Size of vectors representing codewords */
} rbc_127_gabidulin;


void rbc_127_gabidulin_init(rbc_127_gabidulin* code, const rbc_127_poly g, uint32_t k, uint32_t n);

void rbc_127_gabidulin_encode(rbc_127_qre c, const rbc_127_gabidulin gc, const rbc_127_vec m);
void rbc_127_gabidulin_decode(rbc_127_vec m, const rbc_127_gabidulin gc, const rbc_127_qre y);

#endif

