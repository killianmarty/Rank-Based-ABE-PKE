#ifndef RBC_151_H
#define RBC_151_H

#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <x86intrin.h>

#define RBC_151_FIELD_Q 2
#define RBC_151_FIELD_M 151

#define RBC_151_ELT_SIZE 4
#define RBC_151_ELT_DATA_SIZE 3

#define RBC_151_ELT_UR_SIZE 6
#define RBC_151_ELT_UR_DATA_SIZE 5

#define RBC_151_ELT_UINT8_SIZE 19
#define RBC_151_ELT_UR_UINT8_SIZE 38


#define RBC_151_ELT_MASK 127


#define RBC_151_INTEGER_LENGTH 64

typedef int64_t rbc_151_elt_int;
typedef uint64_t rbc_151_elt_uint;
typedef uint64_t rbc_151_elt[RBC_151_ELT_SIZE];
typedef uint64_t rbc_151_elt_ur[RBC_151_ELT_UR_SIZE];
typedef uint64_t* rbc_151_elt_ptr;

typedef rbc_151_elt* rbc_151_vec;
typedef rbc_151_elt* rbc_151_vspace;

typedef struct {
  rbc_151_vec v;
  int32_t max_degree;
  // Do not use degree, it is deprecated and will be removed later
  // Kept temporarily for compatibility with rbc_151_qpoly
  int32_t degree;
} rbc_151_poly_struct;

typedef struct {
	 uint32_t coeffs_nb;
	 uint32_t* coeffs;
} rbc_151_poly_sparse_struct;

typedef rbc_151_poly_struct* rbc_151_poly;
typedef rbc_151_poly_sparse_struct* rbc_151_poly_sparse;

typedef rbc_151_poly rbc_151_qre;

typedef rbc_151_vec* rbc_151_mat;
typedef uint64_t** rbc_151_mat_fq;
typedef uint64_t* rbc_151_perm;

typedef struct {
  rbc_151_mat_fq P;
  rbc_151_mat_fq Q;
  uint32_t n;
} rbc_151_isometry;

void rbc_151_field_init(void);
static const __m128i RBC_151_ELT_SQR_MASK_128 = {0x0F0F0F0F0F0F0F0F, 0x0F0F0F0F0F0F0F0F};
static const __m128i RBC_151_ELT_SQR_LOOKUP_TABLE_128 = {0x1514111005040100, 0x5554515045444140};
static const rbc_151_elt RBC_151_ELT_MODULUS = {0x0000000000000009, 0x0000000000000000, 0x0000000000800000};

#ifndef min
  #define min(a,b) (((a)<(b))?(a):(b))
#endif

#ifndef max
  #define max(a,b) (((a)>(b))?(a):(b))
#endif

#endif
