/**
 * \file rbc_181_elt.c
 * \brief Implementation of rbc_181_elt.h
 */

#include "rbc_181.h"
#include "rbc_181_elt.h"

static uint8_t rbc_181_init_field = 0;
uint64_t RBC_181_SQR_LOOKUP_TABLE[256];



/**
 * \fn void rbc_181_field_init(void)
 * \brief This function initializes various constants used to perform finite field arithmetic.
 *
 */
void rbc_181_field_init(void) {
  uint8_t bit = 0;
  uint64_t mask = 0;

  if(rbc_181_init_field == 0) {
    memset(RBC_181_SQR_LOOKUP_TABLE, 0, 8 * 256);
    for(size_t i = 0 ; i < 256 ; ++i) {
      for(size_t j = 0 ; j < 8 ; ++j) {
        mask = 1 << j;
        bit = (mask & i) >> j;
        RBC_181_SQR_LOOKUP_TABLE[i] ^= bit << (2 * j);
      }
    }

    rbc_181_init_field = 1;
  }
}



/**
 * \fn void rbc_181_elt_set_zero(rbc_181_elt o)
 * \brief This function sets a finite field element to zero.
 *
 * \param[out] o rbc_181_elt
 */
void rbc_181_elt_set_zero(rbc_181_elt o) {
  for(uint8_t i = 0 ; i < RBC_181_ELT_SIZE ; i++) {
    o[i] = 0;
  }
}



/**
 * \fn void rbc_181_elt_set_one(rbc_181_elt o)
 * \brief This function sets a finite field element to one.
 *
 * \param[out] o rbc_181_elt
 */
void rbc_181_elt_set_one(rbc_181_elt o) {
  o[0] = 1;
  for(uint8_t i = 1 ; i < RBC_181_ELT_SIZE ; i++) {
    o[i] = 0;
  }
}



/**
 * \fn void rbc_181_elt_set(rbc_181_elt o, const rbc_181_elt e)
 * \brief This function copies a finite field element into another one.
 *
 * \param[out] o rbc_181_elt
 * \param[in] e rbc_181_elt
 */
void rbc_181_elt_set(rbc_181_elt o, const rbc_181_elt e) {
  for(uint8_t i = 0 ; i < RBC_181_ELT_SIZE - 1 ; i++) {
    o[i] = e[i];
  }
  o[RBC_181_ELT_SIZE - 1] = 0;
}

/**
* \fn void rbc_181_elt_set_mask1(rbc_181_elt o, const rbc_181_elt e1, const rbc_181_elt e2, uint32_t mask)
* \brief This function copies either e1 or e2 into o depending on the mask value
*
* \param[out] o rbc_181_elt
* \param[in] e1 rbc_181_elt
* \param[in] e2 rbc_181_elt_n* \param[in] mask 1 to copy e1 and 0 to copy e2
*/
void rbc_181_elt_set_mask1(rbc_181_elt o, const rbc_181_elt e1, const rbc_181_elt e2, uint32_t mask) {
  for(uint8_t i = 0 ; i < RBC_181_ELT_SIZE - 1 ; i++) {
    o[i] = mask * e1[i] + (1 - mask) * e2[i];
  }
  o[RBC_181_ELT_SIZE - 1] = 0;
}

/**
 * \fn void rbc_181_elt_set(rbc_181_elt o1, rbc_181_elt o2, const rbc_181_elt e, uint32_t mask)
 * \brief This function copies e either into o1 or o2 depending on the mask value
 *
 * \param[out] o1 rbc_181_elt
 * \param[out] o2 rbc_181_elt
 * \param[in] e rbc_181_elt
 * \param[in] mask 1 to copy into o1 and 0 to copy into o2
 */
void rbc_181_elt_set_mask2(rbc_181_elt o1, rbc_181_elt o2, const rbc_181_elt e, uint32_t mask) {
  for(uint8_t i = 0 ; i < RBC_181_ELT_SIZE - 1 ; i++) {
    o1[i] = mask * e[i] + (1 - mask) * o1[i];
    o2[i] = mask * e[i] + (1 - mask) * o2[i];
  }
  o1[RBC_181_ELT_SIZE - 1] = 0;
  o2[RBC_181_ELT_SIZE - 1] = 0;
}

/**
 * \fn void rbc_181_elt_set_from_uint64(rbc_181_elt o, uint64_t* rbc_181_elt e)
 * \brief This function set a finite field element from a pointer to uint64_t.
 *
 * \param[out] o rbc_181_elt
 * \param[in] e Pointer to uint64_t
 */
void rbc_181_elt_set_from_uint64(rbc_181_elt o, const uint64_t* e) {
  rbc_181_elt_set(o, e);
}


/**
 * \fn void rbc_181_elt_set_random
 * \brief This function sets a finite field element with random values using the NIST seed expander.
 *
 * \param[out] ctx random_source
 * \param[out] o rbc_181_elt
 */
void rbc_181_elt_set_random(random_source* ctx, rbc_181_elt o) {
  rbc_181_elt_set_zero(o);

  uint8_t random[RBC_181_ELT_UINT8_SIZE];
  random_source_get_bytes(ctx, random, RBC_181_ELT_UINT8_SIZE);
  random[RBC_181_ELT_UINT8_SIZE - 1] &= RBC_181_ELT_MASK;

  memcpy((uint64_t*) o, random, RBC_181_ELT_UINT8_SIZE);
}

/**
 * \fn uint8_t rbc_181_elt_is_zero(const rbc_181_elt e)
 * \brief This function tests if a finite field element is equal to zero.
 * 
 * \param[in] e rbc_181_elt
 * \return 1 if <b>e</b> is equal to zero, 0 otherwise
 */
uint8_t rbc_181_elt_is_zero(const rbc_181_elt e) {
  int8_t result = 1;
  for(int i = RBC_181_ELT_DATA_SIZE - 1 ; i >= 0 ; i--) {
    result &= (e[i] == 0);
  }

  return result;
}

/**
 * \fn uint8_t rbc_181_elt_is_equal_to(const rbc_181_elt e1, const rbc_181_elt e2)
 * \brief This function tests if two finite field elements are equal.
 *
 * \param[in] e1 rbc_181_elt
 * \param[in] e2 rbc_181_elt
 * \return 1 if <b>e1</b> and <b>e2</b> are equal, 0 otherwise
 */
uint8_t rbc_181_elt_is_equal_to(const rbc_181_elt e1, const rbc_181_elt e2) {
  int8_t result = 1;
  for(uint8_t i = 0 ; i < RBC_181_ELT_DATA_SIZE ; i++) {
    result &= (e1[i] == e2[i]);
  }
 return result;
}

/**
 * \fn uint8_t rbc_181_elt_is_greater_than(const rbc_181_elt e1, const rbc_181_elt e2)
 * \brief This function compares two finite field elements.
 *
 * \param[in] e1 rbc_181_elt
 * \param[in] e2 rbc_181_elt
 * 
eturn 1 if <b>e1</b> > <b>e2</b>, 0 otherwise
 */
uint8_t rbc_181_elt_is_greater_than(const rbc_181_elt e1, const rbc_181_elt e2) {
  int8_t result = 0, flag = 0, tmp = 0;

  for(int8_t i = RBC_181_ELT_DATA_SIZE - 1 ; i >= 0 ; i--) {
    tmp = (e1[i] > e2[i]);
    result = (tmp && !flag) || (flag && result);

    if(i != 0) {
      flag = tmp || flag;
      tmp = (e1[i] < e2[i]);
      flag = tmp || flag;
    }
  }
  return result;
}

/**
 * \fn int32_t rbc_181_elt_get_degree(const rbc_181_elt e)
 * \brief This function returns the degree of a finite field element.
 *
 * \param[in] e rbc_181_elt
 * \return Degree of <b>e</b> 
 */
int32_t rbc_181_elt_get_degree(const rbc_181_elt e) {
  int64_t index = 0, result = -1;
  int8_t mask = 0;

  for(uint8_t i = 0 ; i < RBC_181_ELT_DATA_SIZE ; i++) {
    __asm__ volatile("bsr %1,%0;" : "=r"(index) : "r"(e[i]));
    mask = (e[i] != 0);
    result = mask * (index + 64 * i) + (1 - mask) * result;
  }

  return result;
}

/**
 * \fn uint8_t rbc_181_elt_get_coefficient(const rbc_181_elt e, uint32_t index)
 * \brief This function returns the coefficient of the polynomial <b>e</b> at a given index.
 *
 * \param[in] e rbc_181_elt
 * \param[in] index Index of the coefficient
 * \return Coefficient of <b>e</b> at the given index
 */
uint8_t rbc_181_elt_get_coefficient(const rbc_181_elt e, uint32_t index) {
  uint64_t w = 0;

  for(uint8_t i = 0 ; i < RBC_181_ELT_DATA_SIZE ; i++) {
    w |= -((i ^ (index >> 6)) == 0) & e[i];
  }

  return (w >> (index & 63)) & 1;
}

/**
 * \fn void rbc_181_elt_set_coefficient_vartime(rbc_181_elt o, uint32_t index, uint64_t bit)
 * \brief This function set a coefficient of the polynomial <b>e</b>.
 *
 * \param[in] e rbc_181_elt
 * \param[in] index Index of the coefficient
 * \param[in] bit Value of the coefficient
 */
void rbc_181_elt_set_coefficient_vartime(rbc_181_elt o, uint32_t index, uint8_t bit) {
  size_t position = index / 64;
  o[position] |= (uint64_t) bit << (index % 64);
}

/**
 * \fn rbc_181_elt_add(rbc_181_elt o, const rbc_181_elt e1, const rbc_181_elt e2)
 * \brief This function adds two finite field elements.
 *
 * \param[out] o Sum of <b>e1</b> and <b>e2</b>
 * \param[in] e1 rbc_181_elt
 * \param[in] e2 rbc_181_elt
 */
void rbc_181_elt_add(rbc_181_elt o, const rbc_181_elt e1, const rbc_181_elt e2) {
  __m128i tmp1, tmp2;

  for(uint8_t i = 0 ; i < RBC_181_ELT_SIZE ; i = i + 2) {
    tmp1 = _mm_load_si128((__m128i*) (e1 + i));
    tmp2 = _mm_load_si128((__m128i*) (e2 + i));
    tmp1 = _mm_xor_si128(tmp1, tmp2);
    _mm_store_si128((__m128i*) (o + i), tmp1);
  }
}


/**
 * \fn void rbc_181_elt_mul(rbc_181_elt o, const rbc_181_elt e1, const rbc_181_elt e2)
 * \brief This function multiplies two finite field elements.
 *
 * \param[out] o Product of <b>e1</b> and <b>e2</b>
 * \param[in] e1 rbc_181_elt
 * \param[in] e2 rbc_181_elt
 */
void rbc_181_elt_mul(rbc_181_elt o, const rbc_181_elt e1, const rbc_181_elt e2) {
  rbc_181_elt_ur tmp;
  rbc_181_elt_ur_mul(tmp, e1, e2);
  rbc_181_elt_reduce(o, tmp);
}



/**
 * \fn rbc_181_elt_inv(rbc_181_elt o, const rbc_181_elt e)
 * \brief This function computes the multiplicative inverse of a finite field element.
 *
 * \param[out] o rbc_181_elt
 * \param[in] e rbc_181_elt
 */
void rbc_181_elt_inv(rbc_181_elt o, const rbc_181_elt e) {
  rbc_181_elt tmp;

  rbc_181_elt_set(tmp, e);
  for(int i = 0 ; i < (RBC_181_FIELD_M - 2) ; i++) {
    rbc_181_elt_sqr(o, tmp);
    rbc_181_elt_mul(tmp, o, e);
  }
  rbc_181_elt_sqr(o, tmp);
}



/**
 * \fn void rbc_181_elt_sqr(rbc_181_elt o, const rbc_181_elt e)
 * \brief This function computes the square of a finite field element.
 *
 * \param[out] o rbc_181_elt equal to \f$ e^{2} \f$
 * \param[in] e rbc_181_elt
 */
void rbc_181_elt_sqr(rbc_181_elt o, const rbc_181_elt e) {
  /*
  if(rbc_181_init_field == 0) {
    printf("Call to rbc_181_elt_sqr with uninitialized field\n");
    exit(1);
  }
  */

  rbc_181_elt_ur tmp;
  rbc_181_elt_ur_sqr(tmp, e);
  rbc_181_elt_reduce(o, tmp);
}

/**
 * \fn void rbc_181_elt_nth_root(rbc_181_elt o, const rbc_181_elt e, uint32_t n)
 * \brief This function computes the nth root of a finite field element.
 *
 * \param[out] o Nth root of <b>e</b>
 * \param[in] e rbc_181_elt
 * \param[in] n Parameter defining the nth root
 */
void rbc_181_elt_nth_root(rbc_181_elt o, const rbc_181_elt e, uint32_t n) {
  uint32_t exp = n * (RBC_181_FIELD_M - 1) % RBC_181_FIELD_M;

  rbc_181_elt_sqr(o, e);
  for(size_t i = 0 ; i < exp - 1 ; ++i) {
    rbc_181_elt_sqr(o, o);
  }
}


/**
 * \fn void rbc_181_elt_reduce(rbc_181_elt o, const rbc_181_elt_ur e)
 * \brief This function reduces a finite field element.
 *
 * \param[out] o rbc_181_elt equal to $ e \pmod f $
 * \param[in] e rbc_181_elt
 */
void rbc_181_elt_reduce(rbc_181_elt o, const rbc_181_elt_ur e) {
  uint64_t tmp = e[5] << 11;
  uint64_t tmp2 = e[4] >> 46;

  o[2] = e[2]
    ^ tmp ^ (tmp << 1) ^ (tmp << 6) ^ (tmp << 7)
    ^ tmp2 ^ (tmp2 >> 1) ^ (tmp2 >> 6) ^ (tmp2 >> 7);

  tmp = e[4] << 11;
  tmp2 = e[3] >> 46;

  o[1] = e[1]
    ^ tmp ^ (tmp << 1) ^ (tmp << 6) ^ (tmp << 7)
    ^ tmp2 ^ (tmp2 >> 1) ^ (tmp2 >> 6) ^ (tmp2 >> 7);

  tmp = (e[3] << 11) ^ (o[2] >> 53);
  o[0] = e[0] ^ tmp ^ (tmp << 1) ^ (tmp << 6) ^ (tmp << 7);

  o[2] &= 0x001FFFFFFFFFFFFF;
}

/**
 * \fn void rbc_181_elt_print(const rbc_181_elt e)
 * \brief This function displays a finite field element.
 *
 * \param[in] e rbc_181_elt
 */
void rbc_181_elt_print(const rbc_181_elt e) {
  printf("[");
  printf(" %16" PRIx64 " %16" PRIx64 " %16" PRIx64 , e[0], e[1], e[2]);
  printf(" ]");
}

/**
 * \fn void rbc_181_elt_ur_set(rbc_181_elt_ur o, const rbc_181_elt_ur e)
 * \brief This function copies an unreduced finite field element into another one.
 *
 * \param[out] o rbc_181_elt
 * \param[in] e rbc_181_elt
 */
void rbc_181_elt_ur_set(rbc_181_elt_ur o, const rbc_181_elt_ur e) {
  for(uint8_t i = 0 ; i < RBC_181_ELT_UR_SIZE ; i++) {
    o[i] = e[i];
  }
}

/**
 * \fn void rbc_181_elt_ur_set_zero(rbc_181_elt_ur o)
 * \brief This function sets an unreduced finite field element to zero.
 *
 * \param[out] o rbc_181_elt_ur
 */
void rbc_181_elt_ur_set_zero(rbc_181_elt_ur o) {
  for(uint8_t i = 0 ; i < RBC_181_ELT_UR_SIZE ; i++) {
    o[i] = 0;
  }
}

/**
 * \fn void rbc_181_elt_ur_set_from_uint64(rbc_181_elt_ur o, uint64_t* e)
 * \brief This function set an unreduced finite field element from a pointer to uint64_t.
 *
 * \param[out] o rbc_181_elt_ur
 * \param[in] e Pointer to uint64_t
 */
void rbc_181_elt_ur_set_from_uint64(rbc_181_elt_ur o, const uint64_t* e) {
  rbc_181_elt_ur_set(o, e);
}

/**
 * \fn void rbc_181_elt_ur_mul(rbc_181_elt_ur o, const rbc_181_elt e1, const rbc_181_elt e2)
 * \brief This function computes the unreduced multiplication of two finite field elements.
 *
 * \param[out] o rbc_181_elt equal to \f$ e_1 \times e_2 $
 * \param[in] e1 rbc_181_elt
 * \param[in] e2 rbc_181_elt
 */
void rbc_181_elt_ur_mul(rbc_181_elt_ur o, const rbc_181_elt e1, const rbc_181_elt e2) {
  __m128i a = _mm_load_si128((__m128i*) e1);
  __m128i b = _mm_load_si128((__m128i*) e2);
  __m128i c = _mm_load_si128((__m128i*) (e1 + 2));
  __m128i d = _mm_load_si128((__m128i*) (e2 + 2));

  __m128i a0_b0 = _mm_clmulepi64_si128(a, b, 0x00);

  __m128i a0_b1 = _mm_clmulepi64_si128(a, b, 0x10);
  __m128i a1_b0 = _mm_clmulepi64_si128(a, b, 0x01);

  __m128i a0_b2 = _mm_clmulepi64_si128(a, d, 0x00);
  __m128i a1_b1 = _mm_clmulepi64_si128(a, b, 0x11);
  __m128i a2_b0 = _mm_clmulepi64_si128(c, b, 0x00);

  __m128i a1_b2 = _mm_clmulepi64_si128(a, d, 0x01);
  __m128i a2_b1 = _mm_clmulepi64_si128(c, b, 0x10);

  __m128i a2_b2 = _mm_clmulepi64_si128(c, d, 0x00);

  __m128i c1 = _mm_xor_si128(a0_b1, a1_b0);
  __m128i c2 = _mm_xor_si128(a0_b2, _mm_xor_si128(a1_b1, a2_b0));
  __m128i c3 = _mm_xor_si128(a1_b2, a2_b1);

  o[0] = _mm_extract_epi64(a0_b0, 0);
  o[1] = _mm_extract_epi64(a0_b0, 1) ^ _mm_extract_epi64(c1, 0);
  o[2] = _mm_extract_epi64(c1, 1) ^ _mm_extract_epi64(c2, 0);
  o[3] = _mm_extract_epi64(c2, 1) ^ _mm_extract_epi64(c3, 0);
  o[4] = _mm_extract_epi64(c3, 1) ^ _mm_extract_epi64(a2_b2, 0);
  o[5] = _mm_extract_epi64(a2_b2, 1);
}

/**
 * \fn void rbc_181_elt_ur_sqr(rbc_181_elt o, const rbc_181_elt e)
 * \brief This function computes the unreduced square of a finite field element.
 *
 * \param[out] o rbc_181_elt_ur equal to $ e^{2} $
 * \param[in]  e rbc_181_elt
*/
void rbc_181_elt_ur_sqr(rbc_181_elt_ur o, const rbc_181_elt e) {
  __m128i e_0, e_l, e_h;
  __m128i* tmp = (__m128i*) malloc(2 * sizeof(__m128i));

  e_0 = _mm_load_si128((__m128i*) e);
  e_l = _mm_and_si128(e_0, RBC_181_ELT_SQR_MASK_128);
  e_h = _mm_and_si128(_mm_srli_epi64(e_0, 4), RBC_181_ELT_SQR_MASK_128);

  e_l = _mm_shuffle_epi8(RBC_181_ELT_SQR_LOOKUP_TABLE_128, e_l);
  e_h = _mm_shuffle_epi8(RBC_181_ELT_SQR_LOOKUP_TABLE_128, e_h);

  tmp[0] = _mm_unpacklo_epi8(e_l, e_h);
  tmp[1] = _mm_unpackhi_epi8(e_l, e_h);

  _mm_store_si128((__m128i*) o, tmp[0]);
  _mm_store_si128((__m128i*) (o + 2), tmp[1]);

  e_0 = _mm_load_si128((__m128i *) (e + 2));
  e_l = _mm_and_si128(e_0, RBC_181_ELT_SQR_MASK_128);
  e_h = _mm_and_si128(_mm_srli_epi64(e_0, 4), RBC_181_ELT_SQR_MASK_128);

  e_l = _mm_shuffle_epi8(RBC_181_ELT_SQR_LOOKUP_TABLE_128, e_l);
  e_h = _mm_shuffle_epi8(RBC_181_ELT_SQR_LOOKUP_TABLE_128, e_h);

  tmp[0] = _mm_unpacklo_epi8(e_l, e_h);
  _mm_store_si128((__m128i*) (o + 4), tmp[0]);

  free(tmp);}




/**
 * \fn void rbc_181_elt_to_string(uint8_t* str, const rbc_181_elt e)
 * \brief This function parses a finite field element into a string.
 *
 * \param[out] str Output string
 * \param[in] e rbc_181_elt
 */
void rbc_181_elt_to_string(uint8_t* str, const rbc_181_elt e) {
  uint32_t bytes1 = RBC_181_FIELD_M / 8;
  uint32_t bytes2 = RBC_181_FIELD_M % 8;

  memset(str, 0, RBC_181_ELT_UINT8_SIZE);
  memcpy(str, e, bytes1);

  uint8_t k = 0;
  for(size_t j = 1 ; j <= bytes2 ; j++) {
    uint8_t bit = rbc_181_elt_get_coefficient(e, RBC_181_FIELD_M - j);
    *(str + bytes1) |= (bit << k % 8);
    k++;
    if(k % 8 == 0) bytes1++;
  }
}




/**
 * \fn void rbc_181_elt_from_string(rbc_181_elt e, const uint8_t* str)
 * \brief This function parses a string into a finite field element.
 *
 * \param[out] e rbc_181_elt
 * \param[in] str String to parse
 */
void rbc_181_elt_from_string(rbc_181_elt e, const uint8_t* str) {
  uint32_t bytes1 = RBC_181_FIELD_M / 8;
  uint32_t bytes2 = RBC_181_FIELD_M % 8;

  rbc_181_elt_set_zero(e);
  memcpy(e, str, bytes1);

  uint8_t k = 0;
  for(size_t j = 1 ; j <= bytes2 ; j++) {
    uint8_t bit = (str[bytes1] >> k % 8) & 0x01;
    rbc_181_elt_set_coefficient_vartime(e, RBC_181_FIELD_M - j, bit);
    k++;
    if(k % 8 == 0) bytes1++;
  }
}

/**
 * \fn void rbc_181_elt_ur_print(const rbc_181_elt_ur e)
 * \brief This function displays an unreduced finite field element.
 *
 * \param[in] e rbc_181_elt_ur
 */
void rbc_181_elt_ur_print(const rbc_181_elt_ur e) {
  printf("[");
  printf(" %16" PRIx64 " %16" PRIx64 " %16" PRIx64 , e[0], e[1], e[2]);
  printf(" ]");
}

