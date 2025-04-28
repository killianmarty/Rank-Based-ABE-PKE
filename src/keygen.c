#include "keygen.h"
#include "utils.h"


void keygen(PublicKey *pub, PrivateKey *priv){

    // Declarations
    random_source prng;
    random_source sk_seedexpander;
    uint8_t sk_seed[SEEDEXPANDER_SEED_BYTES];
    rbc_181_qre inv;


    // Initialisations
    rbc_181_field_init();
    rbc_181_qre_init_modulus(N);

    random_source_init(&prng, RANDOM_SOURCE_PRNG);
    random_source_init(&sk_seedexpander, RANDOM_SOURCE_SEEDEXP);
    random_source_get_bytes(&prng, sk_seed, SEEDEXPANDER_SEED_BYTES);
    random_source_seed(&sk_seedexpander, sk_seed);

    rbc_181_vspace_init(&(priv->F), D);
    rbc_181_qre_init(&(priv->x));
    rbc_181_qre_init(&(priv->y));

    rbc_181_qre_init(&inv);
    rbc_181_qre_init(&(pub->h));
    

    // Generate secret key (x, y, F)
    rbc_181_vspace_set_random_full_rank(&sk_seedexpander, priv->F, D);
    rbc_181_qre_set_random_pair_from_support(&sk_seedexpander, priv->x, priv->y, priv->F, D, 1);

    // Generate public key (h=x⁻¹y)
    rbc_181_qre_inv(inv, priv->x);
    rbc_181_qre_mul(pub->h, inv, priv->y);


    // Free memory
    rbc_181_qre_clear(inv);
    rbc_181_qre_clear_modulus();
    random_source_clear(&sk_seedexpander);
    random_source_clear(&prng);
}