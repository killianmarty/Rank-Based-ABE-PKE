#include "utils.h"

void H(uint8_t *payload, int payload_size, rbc_181_qre output){
    
    // Declarations
    random_source sk_seedexpander;
    uint8_t sk_seed[SEEDEXPANDER_SEED_BYTES] = {0};
    uint8_t hash[40] = {0};
    rbc_181_vspace G;
    int rg = 2;

    // Hash the payload
    SHA256(payload, payload_size, hash);

    // Initialisations
    rbc_181_vspace_init(&G, rg);
    memcpy(sk_seed, hash, SEEDEXPANDER_SEED_BYTES);
    random_source_init(&sk_seedexpander, RANDOM_SOURCE_SEEDEXP);
    random_source_seed(&sk_seedexpander, sk_seed);

    // Use the hash as a seed to generate qre
    rbc_181_vspace_set_random_full_rank(&sk_seedexpander, G, rg);
    
    //rbc_181_qre_set_random_from_support(&sk_seedexpander, output, G, D, 1);
    rbc_181_qre_set_random_from_support(&sk_seedexpander, output, G, rg, 1);

    // Free memory
    random_source_clear(&sk_seedexpander);
    rbc_181_vspace_clear(G);

}
