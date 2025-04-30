#include "encaps.h"

int encaps(PublicKey *pub, Attribute *attributes, int nbAttributes, uint8_t *shared_secret, Message *msg){

    // Declarations
    rbc_181_vspace E;
    rbc_181_qre E1, E2, bf_hash;
    BloomFilter bf_att, bf_keys;
    random_source prng;
    uint8_t support_string[R_BYTES];
    
    // Initialisations
    random_source_init(&prng, RANDOM_SOURCE_PRNG);
    rbc_181_vspace_init(&E, R);
    rbc_181_qre_init(&E1);
    rbc_181_qre_init(&E2);
    rbc_181_qre_init(&bf_hash);
    rbc_181_qre_init(&(msg->cipher));


    // Generate salts and init bloom filters
    uint8_t ** salts = malloc(NUM_HASH_FUNCTIONS * sizeof(uint8_t*));
    for (int i = 0; i < NUM_HASH_FUNCTIONS; i++) {
        salts[i] = malloc(SALT_SIZE * sizeof(uint8_t));
        random_source_get_bytes(&prng, salts[i], SALT_SIZE);
        salts[i][SALT_SIZE-1]='\0';
    }
    bloom_filter_init(&bf_att, BLOOM_FILTER_SIZE, NUM_HASH_FUNCTIONS, HASH_LEN, salts, SALT_SIZE);
    bloom_filter_init(&bf_keys, BLOOM_FILTER_SIZE, NUM_HASH_FUNCTIONS, HASH_LEN, salts, SALT_SIZE);


    // Fill bloom filters
    for (int i = 0; i < nbAttributes; i++) {
        char attribute_string[ATTRIBUTE_STRING_SIZE] = {0};
        attribute_to_string(&attributes[i], attribute_string);

        bloom_filter_add(&bf_att, attribute_string);
        bloom_filter_add(&bf_keys, attributes[i].key);
    }
    

    // Generate error support
    rbc_181_vspace_set_random_full_rank(&prng, E, R);


    // Generate error vectors
    rbc_181_qre_set_random_pair_from_support(&prng, E1, E2, E, R, 1);


    // Generate ciphertext
    H(bf_att.bit_array, bf_att.size, bf_hash);
    rbc_181_qre_mul(msg->cipher, E2, pub->h);
    rbc_181_qre_add(msg->cipher, msg->cipher, E1);
    rbc_181_qre_mul(msg->cipher, msg->cipher, bf_hash);
    msg->bf_keys = bf_keys;

    // Generate shared secret
    rbc_181_vec_echelonize(E, R);
    rbc_181_vec_to_string(support_string, E, R);
    SHA512(support_string, R_BYTES, shared_secret);


    // Free memory
    random_source_clear(&prng);
    rbc_181_vspace_clear(E);
    rbc_181_qre_clear(bf_hash);
    rbc_181_qre_clear(E1);
    rbc_181_qre_clear(E2);

    return 1;
}

