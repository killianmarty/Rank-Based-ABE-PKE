#ifndef RBC_89_H
#define RBC_89_H

#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <x86intrin.h>

#define RBC_89_FIELD_Q 2
#define RBC_89_FIELD_M 89

#define RBC_89_ELT_SIZE 2
#define RBC_89_ELT_DATA_SIZE 2

#define RBC_89_ELT_UR_SIZE 4
#define RBC_89_ELT_UR_DATA_SIZE 3

#define RBC_89_ELT_UINT8_SIZE 12
#define RBC_89_ELT_UR_UINT8_SIZE 23


#define RBC_89_ELT_MASK 1


#define RBC_89_INTEGER_LENGTH 64

typedef int64_t rbc_89_elt_int;
typedef uint64_t rbc_89_elt_uint;
typedef uint64_t rbc_89_elt[RBC_89_ELT_SIZE];
typedef uint64_t rbc_89_elt_ur[RBC_89_ELT_UR_SIZE];
typedef uint64_t* rbc_89_elt_ptr;

typedef rbc_89_elt* rbc_89_vec;
typedef rbc_89_elt* rbc_89_vspace;

typedef struct {
  rbc_89_vec v;
  int32_t max_degree;
  // Do not use degree, it is deprecated and will be removed later
  // Kept temporarily for compatibility with rbc_89_qpoly
  int32_t degree;
} rbc_89_poly_struct;

typedef struct {
	 uint32_t coeffs_nb;
	 uint32_t* coeffs;
} rbc_89_poly_sparse_struct;

typedef rbc_89_poly_struct* rbc_89_poly;
typedef rbc_89_poly_sparse_struct* rbc_89_poly_sparse;

typedef rbc_89_poly rbc_89_qre;

typedef rbc_89_vec* rbc_89_mat;
typedef uint64_t** rbc_89_mat_fq;
typedef uint64_t* rbc_89_perm;

typedef struct {
  rbc_89_mat_fq P;
  rbc_89_mat_fq Q;
  uint32_t n;
} rbc_89_isometry;

void rbc_89_field_init(void);
static const __m128i RBC_89_ELT_SQR_MASK_128 = {0x0F0F0F0F0F0F0F0F, 0x0F0F0F0F0F0F0F0F};
static const __m128i RBC_89_ELT_SQR_LOOKUP_TABLE_128 = {0x1514111005040100, 0x5554515045444140};
static const rbc_89_elt RBC_89_ELT_MODULUS = {0x0000004000000001, 0x0000000002000000};

#ifndef min
  #define min(a,b) (((a)<(b))?(a):(b))
#endif

#ifndef max
  #define max(a,b) (((a)>(b))?(a):(b))
#endif

#endif
