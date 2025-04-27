#include "encaps.h"

void encaps(PublicKey *pub, uint8_t *shared_secret, rbc_181_qre cipher){

    // Declarations
    rbc_181_vspace E;
    rbc_181_qre E1, E2;
    random_source prng;
    uint8_t support_string[R_BYTES];

    // Initialisations
    rbc_181_field_init();
    rbc_181_qre_init_modulus(N);

    random_source_init(&prng, RANDOM_SOURCE_PRNG);

    rbc_181_vspace_init(&E, R);
    rbc_181_qre_init(&E1);
    rbc_181_qre_init(&E2);
    

    // Generate error support
    rbc_181_vspace_set_random_full_rank(&prng, E, R);

    // Generate error vectors
    rbc_181_qre_set_random_pair_from_support(&prng, E1, E2, E, R, 1);

    // Generate ciphertext
    rbc_181_qre_mul(cipher, E2, pub->h);
    rbc_181_qre_add(cipher, cipher, E1);

    // Generate shared secret
    rbc_181_vec_echelonize(E, R);
    rbc_181_vec_to_string(support_string, E, R);
    SHA512(support_string, R_BYTES, shared_secret);

    // Free memory
    random_source_clear(&prng);
    rbc_181_vspace_clear(E);
    rbc_181_qre_clear(E1);
    rbc_181_qre_clear(E2);
    rbc_181_qre_clear_modulus();

}

