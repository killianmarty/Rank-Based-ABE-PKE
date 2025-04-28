#include "utils.h"

void H(uint8_t *payload, int payload_size, rbc_181_vspace E, int rank, rbc_181_qre output){
    
    // Declarations
    random_source sk_seedexpander;
    uint8_t hash[32];

    // Initialisations
    rbc_181_field_init();
    rbc_181_qre_init_modulus(N);
    random_source_init(&sk_seedexpander, RANDOM_SOURCE_SEEDEXP);

    // Hash the payload
    SHA256(payload, payload_size, hash);

    // Use the hash as a seed to generate qre
    random_source_seed(&sk_seedexpander, hash);
    rbc_181_qre_set_random_from_support(&sk_seedexpander, output, E, rank, 1);

    // Free memory
    rbc_181_qre_clear_modulus();
    random_source_clear(&sk_seedexpander);

}
