/**
 * \file rbc_181_qre.c
 * \brief Implementation of rbc_181_qre.h
 */

#include "rbc_181_elt.h"
#include "rbc_181_qre.h"
#include "rbc_181_poly.h"

static uint32_t RBC_181_QRE_DEG;
static int rbc_181_init_qre_modulus = 0;
static rbc_181_poly_sparse rbc_181_qre_modulus;
static rbc_181_poly rbc_181_qre_modulus_inv;




/**
 * \fn void rbc_181_qre_init_modulus(uint32_t degree) {
 * \brief This function init the quotient ring modulus corresponding to PARAM_N.
 *
 * \param[in] degree Degree of the modulus
 */
void rbc_181_qre_init_modulus(uint32_t degree) {
  if(rbc_181_init_qre_modulus == 0) {
    RBC_181_QRE_DEG = degree - 1;
    rbc_181_qre_modulus = rbc_181_qre_get_modulus(degree);
    rbc_181_poly_init(&rbc_181_qre_modulus_inv, RBC_181_QRE_DEG + 1);
    rbc_181_poly_set_zero(rbc_181_qre_modulus_inv, RBC_181_QRE_DEG + 1);
    for(uint32_t i = 0 ; i < rbc_181_qre_modulus->coeffs_nb ; i++) {
      rbc_181_elt_set_one(rbc_181_qre_modulus_inv->v[rbc_181_qre_modulus->coeffs[i]]);
    }
  }

  rbc_181_init_qre_modulus++;
}




/**
 * \fn void rbc_181_qre_clear_modulus(void) {
 * \brief This function clears the quotient ring modulus in use.
 */
void rbc_181_qre_clear_modulus(void) {
  rbc_181_init_qre_modulus--;

  if(rbc_181_init_qre_modulus == 0) {
    rbc_181_poly_sparse_clear(rbc_181_qre_modulus);
    rbc_181_poly_clear(rbc_181_qre_modulus_inv);
  }
}

/**
 * \fn rbc_181_poly_sparse rbc_181_qre_get_modulus(uint32_t degree) {
 * \brief This function return the sparse polynomial used as the quotient ring modulus for PARAM_N.
 *
 * \param[in] degree Degree of the modulus
 */
rbc_181_poly_sparse rbc_181_qre_get_modulus(uint32_t degree) {
  rbc_181_poly_sparse modulus = NULL;
  uint32_t* values;
  if(degree == 113) {
    values = (uint32_t*) malloc(3 * sizeof(uint32_t));
    values[0] = 0;
    values[1] = 9;
    values[2] = 113;
    rbc_181_poly_sparse_init(&modulus, 3, values);
    free(values);
  }
  else if(degree == 149) {
    values = (uint32_t*) malloc(5 * sizeof(uint32_t));
    values[0] = 0;
    values[1] = 7;
    values[2] = 9;
    values[3] = 10;
    values[4] = 149;
    rbc_181_poly_sparse_init(&modulus, 5, values);
    free(values);
  }
  else if(degree == 179) {
    values = (uint32_t*) malloc(5 * sizeof(uint32_t));
    values[0] = 0;
    values[1] = 1;
    values[2] = 2;
    values[3] = 4;
    values[4] = 179;
    rbc_181_poly_sparse_init(&modulus, 5, values);
    free(values);
  }
  else if(degree == 83) {
    values = (uint32_t*) malloc(5 * sizeof(uint32_t));
    values[0] = 0;
    values[1] = 2;
    values[2] = 4;
    values[3] = 7;
    values[4] = 83;
    rbc_181_poly_sparse_init(&modulus, 5, values);
    free(values);
  }

 return modulus;
}




/**
 * \fn void rbc_181_qre_init(rbc_181_qre* p)
 * \brief This function allocates the memory for a rbc_181_qre element.
 *
 * \param[out] p Pointer to the allocated rbc_181_qre
 */
void rbc_181_qre_init(rbc_181_qre* p) {
  rbc_181_poly_init(p, RBC_181_QRE_DEG);
}




/**
 * \fn void rbc_181_qre_clear(rbc_181_qre p)
 * \brief This function clears the memory allocated for a rbc_181_qre element.
 *
 * \param[in] p rbc_181_qre
 */
void rbc_181_qre_clear(rbc_181_qre p) {
  rbc_181_poly_clear(p);
}




/**
 * \fn void rbc_181_qre_set_zero(rbc_181_qre o)
 * \brief This functions sets a rbc_181_qre to zero.
 *
 * \param[in] o rbc_181_qre
 */
void rbc_181_qre_set_zero(rbc_181_qre o) {
  rbc_181_poly_set_zero(o, RBC_181_QRE_DEG);
}




/**
 * \fn void rbc_181_qre_set_random(random_source* ctx, rbc_181_qre o)
 * \brief This function sets a rbc_181_qre with random values using NIST seed expander.
 *
 * \param[out] ctx random source
 * \param[out] o rbc_181_qre
 */
void rbc_181_qre_set_random(random_source* ctx, rbc_181_qre o) {
  rbc_181_poly_set_random(ctx, o, RBC_181_QRE_DEG);
}




/**
 * \fn rbc_181_qre_set_random_from_xof(rbc_181_qre o, void (*xof)(uint8_t *, size_t, const uint8_t *, size_t), const uint8_t *xof_input, uint32_t xof_size)
 * \brief This function sets a rbc_181_qre with random values using XOF.
 *
 * \param[out] o rbc_181_qre
 * \param[in] xof XOF procedure
 * \param[in] xof_input XOF input byte array
 * \param[in] xof_size XOF input byte array length of xof_input
 */
void rbc_181_qre_set_random_from_xof(rbc_181_qre o,
                                 void (*xof)(uint8_t *, size_t, const uint8_t *, size_t),
                                 const uint8_t *xof_input,
                                 uint32_t xof_size) {
  rbc_181_poly_set_random_from_xof(o, RBC_181_QRE_DEG, xof, xof_input, xof_size);
}




/**
 * \fn void rbc_181_qre_set_random_full_rank(random_source* ctx, rbc_181_qre o)
 * \brief This function sets a rbc_181_qre with random values using the NIST seed expander. The returned rbc_181_qre has full rank.
 *
 * \param[out] ctx random source
 * \param[out] o rbc_181_qre
 */
void rbc_181_qre_set_random_full_rank(random_source* ctx, rbc_181_qre o) {
  rbc_181_poly_set_random_full_rank(ctx, o, RBC_181_QRE_DEG);
}




/**
 * \fn void rbc_181_qre_set_random_full_rank_with_one(random_source* ctx, rbc_181_qre o)
 * \brief This function sets a rbc_181_qre with random values using the NIST seed expander. The returned rbc_181_qre has full rank and contains one.
 *
 * \param[out] ctx random source
 * \param[out] o rbc_181_qre
 */
void rbc_181_qre_set_random_full_rank_with_one(random_source* ctx, rbc_181_qre o) {
  rbc_181_poly_set_random_full_rank_with_one(ctx, o, RBC_181_QRE_DEG);
}




/**
 * \fn void rbc_181_qre_set_random_from_support(random_source* ctx, rbc_181_qre o, const rbc_181_vspace support, uint32_t support_size)
 * \brief This function sets a rbc_181_qre with random values using the NIST seed expander. The support of the rbc_181_qre returned by this function is the one given in input.
 *
 * \param[out] ctx random source
 * \param[out] o rbc_181_qre
 * \param[in] support Support of <b>o</b>
 * \param[in] support_size Size of the support
 * \param[in] copy_flag If not 0, the support is copied into random coordinates of the resulting vector
 */
void rbc_181_qre_set_random_from_support(random_source* ctx, rbc_181_qre o, const rbc_181_vspace support, uint32_t support_size, uint8_t copy_flag) {
  rbc_181_poly_set_random_from_support(ctx, o, RBC_181_QRE_DEG, support, support_size, copy_flag);
}




/**
 * \fn void rbc_181_qre_set_random_pair_from_support(random_source* ctx, rbc_181_qre o1, rbc_181_qre o2, const rbc_181_vspace support, uint32_t support_size)
 * \brief This function sets a pair of rbc_181_qre with random values using the NIST seed expander. The support of (o1 || o2) is the one given in input.
 *
 * \param[out] ctx random_source
 * \param[out] o1 rbc_181_qre
 * \param[out] o2 rbc_181_qre
 * \param[in] support Support
 * \param[in] support_size Size of the support
 * \param[in] copy_flag If not 0, the support is copied into random coordinates of the resulting vector
 */
void rbc_181_qre_set_random_pair_from_support(random_source* ctx, rbc_181_qre o1, rbc_181_qre o2, const rbc_181_vspace support, uint32_t support_size, uint8_t copy_flag) {
  rbc_181_poly_set_random_pair_from_support(ctx, o1, o2, RBC_181_QRE_DEG, support, support_size, copy_flag);
}




/**
 * \fn uint8_t rbc_181_qre_is_equal_to(const rbc_181_qre p1, const rbc_181_qre p2)
 * \brief This function test if two rbc_181_qre are equal.
 *
 * \param[in] p1 rbc_181_qre
 * \param[in] p2 rbc_181_qre
 * \return 1 if the rbc_181_qre are equal, 0 otherwise
 */
uint8_t rbc_181_qre_is_equal_to(const rbc_181_qre p1, const rbc_181_qre p2) {
  return rbc_181_poly_is_equal_to(p1, p2);
}




/**
 * \fn void rbc_181_qre_add(rbc_181_qre o, const rbc_181_qre p1, const rbc_181_qre p2)
 * \brief This function adds two rbc_181_qre.
 *
 * \param[out] o Sum of <b>p1</b> and <b>p2</b>
 * \param[in] p1 rbc_181_qre
 * \param[in] p2 rbc_181_qre
 */
void rbc_181_qre_add(rbc_181_qre o, const rbc_181_qre p1, const rbc_181_qre p2) {
  rbc_181_poly_add(o, p1, p2);
}




/**
 * \fn void rbc_181_qre_mul(rbc_181_qre o, const rbc_181_qre p1, const rbc_181_qre p2)
 * \brief This function multiplies two rbc_181_qre.
 *
 * \param[out] o Product of <b>p1</b> and <b>p2</b>
 * \param[in] p1 rbc_181_qre
 * \param[in] p2 rbc_181_qre
 */
void rbc_181_qre_mul(rbc_181_qre o, const rbc_181_qre p1, const rbc_181_qre p2) {
  if(rbc_181_init_qre_modulus == 0) {
    printf("Call to rbc_181_qre_mul with uninitialized modulus\n");
    exit(1);
  }

  rbc_181_poly_mulmod_sparse(o, p1, p2, rbc_181_qre_modulus);
}




/**
 * \fn void rbc_181_qre_inv(rbc_181_qre o, const rbc_181_qre p)
 * \brief This function performs the extended euclidean algorithm to compute the inverse of p.
 *
 * \param[out] o Inverse of <b>e</b> modulo <b>modulus</b>
 * \param[in] p rbc_181_qre
 * \param[in] modulus Polynomial
 */
void rbc_181_qre_inv(rbc_181_qre o, const rbc_181_qre p) {
  if(rbc_181_init_qre_modulus == 0) {
    printf("Call to rbc_181_qre_inv with uninitialized modulus\n");
    exit(1);
  }

  rbc_181_poly_inv(o, p, rbc_181_qre_modulus_inv);
}




/**
 * \fn void rbc_181_qre_to_string(uint8_t* str, const rbc_181_qre p)
 * \brief This function parses a rbc_181_qre into a string.
 *
 * \param[out] str String
 * \param[in] e rbc_181_qre
 */
void rbc_181_qre_to_string(uint8_t* str, const rbc_181_qre p) {
  rbc_181_poly_to_string(str, p);
}




/**
 * \fn void rbc_181_qre_from_string(rbc_181_qre o, const uint8_t* str)
 * \brief This function parses a string into a rbc_181_qre.
 *
 * \param[out] o rbc_181_qre
 * \param[in] str String to parse
 */
void rbc_181_qre_from_string(rbc_181_qre o, const uint8_t* str) {
  rbc_181_poly_from_string(o, str);
}




/**
 * \fn void rbc_181_qre_print(const rbc_181_qre p)
 * \brief This function displays a rbc_181_qre.
 *
 * \param[in] p rbc_181_qre
 */
void rbc_181_qre_print(const rbc_181_qre p) {
  rbc_181_poly_print(p);
}




/**
 * \fn void rbc_181_poly_set_monial(rbc_181_qre o, uint32_t degree)
 * \brief This functions sets a polynomial to x^degree.
 *
 * \param[in] p Polynomial
 * \param[in] degree Degree of the monomial
 */
void rbc_181_qre_set_monomial(rbc_181_qre o, uint32_t degree) {
  rbc_181_poly_set_monomial(o, degree);
}




/**
 * \fn void rbc_181_qre_rot(rbc_181_qre v, uint32_t r)
 * \brief This functions rotates entries of a vector with coefficients in GF(q^m).
 *
 * \param[out] v rbc_181_qre with entries rotated by position
 * \param[in] position Integer between 1 and (size - 1) such that v is rotated-right r times
 */
void rbc_181_qre_rot(rbc_181_qre o, rbc_181_qre e, uint32_t rot) {

  if(rot > (uint32_t)(e->degree + 1)) {
    exit(EXIT_FAILURE);
  }

  if (rot == (uint32_t)(e->degree + 1)) {
    rbc_181_poly_set(o, e);
  }
  else {
    rbc_181_qre tmp;
    rbc_181_qre_init(&tmp);
    rbc_181_qre_set_monomial(tmp, rot);
    rbc_181_qre_mul(o, e, tmp);
    rbc_181_qre_clear(tmp);
  }
}


