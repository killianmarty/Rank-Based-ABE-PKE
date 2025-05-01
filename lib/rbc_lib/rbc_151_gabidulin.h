/**
 * \file gabidulin.h
 * \brief Functions to encode and decode CipherTextMetaDatas using Gabidulin codes
 *
 * The decoding algorithm provided is based on q_polynomials reconstruction, see \cite gabidulin:welch and \cite gabidulin:generalized for details.
 *
 */

#ifndef RBC_151_GABIDULIN_H
#define RBC_151_GABIDULIN_H

#include "rbc_151_vec.h"
#include "rbc_151_qre.h"


/**
  * \typedef rbc_151_gabidulin
  * \brief Structure of a gabidulin code
  */
typedef struct rbc_151_gabidulin {
  rbc_151_poly g; /**< Generator vector defining the code */
  uint32_t k; /**< Size of vectors representing CipherTextMetaDatas */
  uint32_t n; /**< Size of vectors representing codewords */
} rbc_151_gabidulin;


void rbc_151_gabidulin_init(rbc_151_gabidulin* code, const rbc_151_poly g, uint32_t k, uint32_t n);

void rbc_151_gabidulin_encode(rbc_151_qre c, const rbc_151_gabidulin gc, const rbc_151_vec m);
void rbc_151_gabidulin_decode(rbc_151_vec m, const rbc_151_gabidulin gc, const rbc_151_qre y);

#endif

