#ifndef RBC_127_H
#define RBC_127_H

#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <x86intrin.h>

#define RBC_127_FIELD_Q 2
#define RBC_127_FIELD_M 127

#define RBC_127_ELT_SIZE 2
#define RBC_127_ELT_DATA_SIZE 2

#define RBC_127_ELT_UR_SIZE 4
#define RBC_127_ELT_UR_DATA_SIZE 4

#define RBC_127_ELT_UINT8_SIZE 16
#define RBC_127_ELT_UR_UINT8_SIZE 32


#define RBC_127_ELT_MASK 127


#define RBC_127_INTEGER_LENGTH 64

typedef int64_t rbc_127_elt_int;
typedef uint64_t rbc_127_elt_uint;
typedef uint64_t rbc_127_elt[RBC_127_ELT_SIZE];
typedef uint64_t rbc_127_elt_ur[RBC_127_ELT_UR_SIZE];
typedef uint64_t* rbc_127_elt_ptr;

typedef rbc_127_elt* rbc_127_vec;
typedef rbc_127_elt* rbc_127_vspace;

typedef struct {
  rbc_127_vec v;
  int32_t max_degree;
  // Do not use degree, it is deprecated and will be removed later
  // Kept temporarily for compatibility with rbc_127_qpoly
  int32_t degree;
} rbc_127_poly_struct;

typedef struct {
	 uint32_t coeffs_nb;
	 uint32_t* coeffs;
} rbc_127_poly_sparse_struct;

typedef rbc_127_poly_struct* rbc_127_poly;
typedef rbc_127_poly_sparse_struct* rbc_127_poly_sparse;

typedef rbc_127_poly rbc_127_qre;

typedef rbc_127_vec* rbc_127_mat;
typedef uint64_t** rbc_127_mat_fq;
typedef uint64_t* rbc_127_perm;

typedef struct {
  rbc_127_mat_fq P;
  rbc_127_mat_fq Q;
  uint32_t n;
} rbc_127_isometry;

void rbc_127_field_init(void);
static const __m128i RBC_127_ELT_SQR_MASK_128 = {0x0F0F0F0F0F0F0F0F, 0x0F0F0F0F0F0F0F0F};
static const __m128i RBC_127_ELT_SQR_LOOKUP_TABLE_128 = {0x1514111005040100, 0x5554515045444140};
static const rbc_127_elt RBC_127_ELT_MODULUS = {0x0000000000000003, 0x8000000000000000};

#ifndef min
  #define min(a,b) (((a)<(b))?(a):(b))
#endif

#ifndef max
  #define max(a,b) (((a)>(b))?(a):(b))
#endif

#endif
