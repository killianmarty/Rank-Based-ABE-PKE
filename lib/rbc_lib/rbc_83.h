#ifndef RBC_83_H
#define RBC_83_H

#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <x86intrin.h>

#define RBC_83_FIELD_Q 2
#define RBC_83_FIELD_M 83

#define RBC_83_ELT_SIZE 2
#define RBC_83_ELT_DATA_SIZE 2

#define RBC_83_ELT_UR_SIZE 4
#define RBC_83_ELT_UR_DATA_SIZE 3

#define RBC_83_ELT_UINT8_SIZE 11
#define RBC_83_ELT_UR_UINT8_SIZE 21


#define RBC_83_ELT_MASK 7


#define RBC_83_INTEGER_LENGTH 64

typedef int64_t rbc_83_elt_int;
typedef uint64_t rbc_83_elt_uint;
typedef uint64_t rbc_83_elt[RBC_83_ELT_SIZE];
typedef uint64_t rbc_83_elt_ur[RBC_83_ELT_UR_SIZE];
typedef uint64_t* rbc_83_elt_ptr;

typedef rbc_83_elt* rbc_83_vec;
typedef rbc_83_elt* rbc_83_vspace;

typedef struct {
  rbc_83_vec v;
  int32_t max_degree;
  // Do not use degree, it is deprecated and will be removed later
  // Kept temporarily for compatibility with rbc_83_qpoly
  int32_t degree;
} rbc_83_poly_struct;

typedef struct {
	 uint32_t coeffs_nb;
	 uint32_t* coeffs;
} rbc_83_poly_sparse_struct;

typedef rbc_83_poly_struct* rbc_83_poly;
typedef rbc_83_poly_sparse_struct* rbc_83_poly_sparse;

typedef rbc_83_poly rbc_83_qre;

typedef rbc_83_vec* rbc_83_mat;
typedef uint64_t** rbc_83_mat_fq;
typedef uint64_t* rbc_83_perm;

typedef struct {
  rbc_83_mat_fq P;
  rbc_83_mat_fq Q;
  uint32_t n;
} rbc_83_isometry;

void rbc_83_field_init(void);
static const __m128i RBC_83_ELT_SQR_MASK_128 = {0x0F0F0F0F0F0F0F0F, 0x0F0F0F0F0F0F0F0F};
static const __m128i RBC_83_ELT_SQR_LOOKUP_TABLE_128 = {0x1514111005040100, 0x5554515045444140};
static const rbc_83_elt RBC_83_ELT_MODULUS = {0x0000000000000095, 0x0000000000080000};

#ifndef min
  #define min(a,b) (((a)<(b))?(a):(b))
#endif

#ifndef max
  #define max(a,b) (((a)>(b))?(a):(b))
#endif

#endif
