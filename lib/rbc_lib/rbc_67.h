#ifndef RBC_67_H
#define RBC_67_H

#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <x86intrin.h>

#define RBC_67_FIELD_Q 2
#define RBC_67_FIELD_M 67

#define RBC_67_ELT_SIZE 2
#define RBC_67_ELT_DATA_SIZE 2

#define RBC_67_ELT_UR_SIZE 4
#define RBC_67_ELT_UR_DATA_SIZE 3

#define RBC_67_ELT_UINT8_SIZE 9
#define RBC_67_ELT_UR_UINT8_SIZE 17


#define RBC_67_ELT_MASK 7


#define RBC_67_INTEGER_LENGTH 64

typedef int64_t rbc_67_elt_int;
typedef uint64_t rbc_67_elt_uint;
typedef uint64_t rbc_67_elt[RBC_67_ELT_SIZE];
typedef uint64_t rbc_67_elt_ur[RBC_67_ELT_UR_SIZE];
typedef uint64_t* rbc_67_elt_ptr;

typedef rbc_67_elt* rbc_67_vec;
typedef rbc_67_elt* rbc_67_vspace;

typedef struct {
  rbc_67_vec v;
  int32_t max_degree;
  // Do not use degree, it is deprecated and will be removed later
  // Kept temporarily for compatibility with rbc_67_qpoly
  int32_t degree;
} rbc_67_poly_struct;

typedef struct {
	 uint32_t coeffs_nb;
	 uint32_t* coeffs;
} rbc_67_poly_sparse_struct;

typedef rbc_67_poly_struct* rbc_67_poly;
typedef rbc_67_poly_sparse_struct* rbc_67_poly_sparse;

typedef rbc_67_poly rbc_67_qre;

typedef rbc_67_vec* rbc_67_mat;
typedef uint64_t** rbc_67_mat_fq;
typedef uint64_t* rbc_67_perm;

typedef struct {
  rbc_67_mat_fq P;
  rbc_67_mat_fq Q;
  uint32_t n;
} rbc_67_isometry;

void rbc_67_field_init(void);
static const __m128i RBC_67_ELT_SQR_MASK_128 = {0x0F0F0F0F0F0F0F0F, 0x0F0F0F0F0F0F0F0F};
static const __m128i RBC_67_ELT_SQR_LOOKUP_TABLE_128 = {0x1514111005040100, 0x5554515045444140};
static const rbc_67_elt RBC_67_ELT_MODULUS = {0x0000000000000027, 0x0000000000000008};

#ifndef min
  #define min(a,b) (((a)<(b))?(a):(b))
#endif

#ifndef max
  #define max(a,b) (((a)>(b))?(a):(b))
#endif

#endif
