#include "encrypt.h"

int encrypt(PublicKey *pub, AttributeList * attributes, uint8_t *plaintext, int plaintextSize, CipherText *ciphertext){

    // Declarations
    rbc_vspace E;
    rbc_qre E1, E2, bf_hash;
    BloomFilter bf_att, bf_keys;
    random_source prng;
    uint8_t support_string[R_BYTES];
    
    // Initialisations
    random_source_init(&prng, RANDOM_SOURCE_PRNG);
    rbc_vspace_init(&E, R);
    rbc_qre_init(&E1);
    rbc_qre_init(&E2);
    rbc_qre_init(&bf_hash);
    rbc_qre_init(&(ciphertext->c.cipher));


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
    for (int i = 0; i < attributes->count; i++) {
        char attribute_string[ATTRIBUTE_STRING_SIZE] = {0};
        attribute_to_string(&attributes->attributes[i], attribute_string);

        bloom_filter_add(&bf_att, attribute_string);
        bloom_filter_add(&bf_keys, attributes->attributes[i].key);
    }
    

    // Generate error support
    rbc_vspace_set_random_full_rank(&prng, E, R);


    // Generate error vectors
    rbc_qre_set_random_pair_from_support(&prng, E1, E2, E, R, 1);


    // Generate ciphertext
    H(bf_att.bit_array, bf_att.size, bf_hash);
    rbc_qre_mul(ciphertext->c.cipher, E2, pub->h);
    rbc_qre_add(ciphertext->c.cipher, ciphertext->c.cipher, E1);
    rbc_qre_mul(ciphertext->c.cipher, ciphertext->c.cipher, bf_hash);
    ciphertext->c.bf_keys = bf_keys;

    // Hash E
    uint8_t hashedE[SECRET_KEY_BYTES];
    rbc_vec_echelonize(E, R);
    rbc_vec_to_string(support_string, E, R);
    SHA512(support_string, R_BYTES, hashedE);

    // Compute the encrypted message
    ciphertext->encrypted_message_size = plaintextSize;
    ciphertext->encrypted_message = malloc(plaintextSize * sizeof(uint8_t));
    for (int i = 0; i < plaintextSize; i++) {
        ciphertext->encrypted_message[i] = plaintext[i] ^ hashedE[i % SECRET_KEY_BYTES];
    }

    // Free memory
    random_source_clear(&prng);
    rbc_vspace_clear(E);
    rbc_qre_clear(bf_hash);
    rbc_qre_clear(E1);
    rbc_qre_clear(E2);

    return 1;
}

