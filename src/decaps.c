
#include "decaps.h"

void decaps(uint8_t *shared_secret, rbc_181_qre cipher, PrivateKey *priv) {

    // Declarations
    rbc_181_qre xc;
    rbc_181_vspace E;
    uint8_t support_string[R_BYTES];
    uint32_t dimE = 0;
  

    // Initialisations
    rbc_181_field_init();
    rbc_181_qre_init_modulus(N);
  
    rbc_181_qre_init(&xc);
    rbc_181_vspace_init(&E, N);


    // Decoding syndrome
    rbc_181_qre_mul(xc, priv->x, cipher);
    dimE = rbc_181_lrpc_RSR(E, R, priv->F, D, xc->v, N);

    if(dimE != 0) {
      rbc_181_vec_echelonize(E, R);
      rbc_181_vec_to_string(support_string, E, R);
      SHA512(support_string, R_BYTES, shared_secret);
    } else {
      memset(shared_secret, 0, SECRET_KEY_BYTES);
    }
  
    
    // Free memory
    rbc_181_vspace_clear(E);
    rbc_181_qre_clear(xc);
    rbc_181_qre_clear_modulus();
  }