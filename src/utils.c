#include "utils.h"

void H(uint8_t *payload, int payload_size, rbc_181_qre output){
    
    // Declarations
    rbc_181_vspace G;
    random_source sk_seedexpander;
    uint8_t sk_seed[SEEDEXPANDER_SEED_BYTES] = {0};
    uint8_t hash[40] = {0};
    int rg = N;

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

uint8_t * serialize_private_key(PrivateKey *key){

    uint8_t *output = calloc(SERIALIZED_PRIVATE_KEY_SIZE, sizeof(uint8_t));

    uint8_t x[SERIALIZED_QRE_SIZE] = {0};
    uint8_t y[SERIALIZED_QRE_SIZE] = {0};
    uint8_t F[SERIALIZED_VSPACE_SIZE] = {0};

    rbc_181_qre_to_string(x, key->x);
    rbc_181_qre_to_string(y, key->y);
    rbc_181_vec_to_string(F, key->F, D);

    memcpy(output, x, SERIALIZED_QRE_SIZE);
    memcpy(output + SERIALIZED_QRE_SIZE, y, SERIALIZED_QRE_SIZE);
    memcpy(output + 2*SERIALIZED_QRE_SIZE, F, SERIALIZED_VSPACE_SIZE);

    return output;
}

PrivateKey * deserialize_private_key(uint8_t *input){

    PrivateKey *key = malloc(sizeof(PrivateKey));

    uint8_t x[SERIALIZED_QRE_SIZE] = {0};
    uint8_t y[SERIALIZED_QRE_SIZE] = {0};
    uint8_t F[SERIALIZED_VSPACE_SIZE] = {0};

    memcpy(x, input, SERIALIZED_QRE_SIZE);
    memcpy(y, input + SERIALIZED_QRE_SIZE, SERIALIZED_QRE_SIZE);
    memcpy(F, input + 2*SERIALIZED_QRE_SIZE, SERIALIZED_VSPACE_SIZE);

    rbc_181_qre_init(&key->x);
    rbc_181_qre_init(&key->y);
    rbc_181_vspace_init(&key->F, D);

    rbc_181_qre_from_string(key->x, x);
    rbc_181_qre_from_string(key->y, y);
    rbc_181_vec_from_string(key->F, D, F);

    return key;
}

uint8_t * serialize_public_key(PublicKey *key){

    uint8_t *output = calloc(SERIALIZED_QRE_SIZE, sizeof(uint8_t));

    rbc_181_qre_to_string(output, key->h);

    return output;
}

PublicKey * deserialize_public_key(uint8_t *input){

    PublicKey *key = malloc(sizeof(PublicKey));

    rbc_181_qre_init(&key->h);

    rbc_181_qre_from_string(key->h, input);

    return key;
}

uint8_t * serialize_ciphertext(CipherText *ciphertext){
    int data_size = 6*sizeof(uint32_t) + ciphertext->encrypted_message_size*sizeof(uint8_t) + ciphertext->c.bf_keys.num_hash_functions*ciphertext->c.bf_keys.salt_len + ciphertext->c.bf_keys.size + SERIALIZED_QRE_SIZE;
    uint8_t *output = calloc(data_size, sizeof(uint8_t));
    uint8_t cipher[SERIALIZED_QRE_SIZE];

    rbc_181_qre_to_string(cipher, ciphertext->c.cipher);
    
    memcpy(output, &data_size, sizeof(int32_t));
    memcpy(output + sizeof(int32_t), &ciphertext->c.bf_keys.size, sizeof(int32_t));
    memcpy(output + 2*sizeof(int32_t), &ciphertext->c.bf_keys.num_hash_functions, sizeof(int32_t));
    memcpy(output + 3*sizeof(int32_t), &ciphertext->c.bf_keys.hash_len, sizeof(int32_t));
    memcpy(output + 4*sizeof(int32_t), &ciphertext->c.bf_keys.salt_len, sizeof(int32_t));
    memcpy(output + 5*sizeof(int32_t), &ciphertext->encrypted_message_size, sizeof(int32_t));
    for (int i = 0; i < ciphertext->c.bf_keys.num_hash_functions; i++)
    {
        memcpy(output + 6*sizeof(int32_t) + i*ciphertext->c.bf_keys.salt_len, ciphertext->c.bf_keys.salts[i], ciphertext->c.bf_keys.salt_len);
    }
    memcpy(output + 6*sizeof(int32_t) + ciphertext->c.bf_keys.num_hash_functions*ciphertext->c.bf_keys.salt_len, ciphertext->c.bf_keys.bit_array, ciphertext->c.bf_keys.size);
    memcpy(output + 6*sizeof(int32_t) + ciphertext->c.bf_keys.num_hash_functions*ciphertext->c.bf_keys.salt_len + ciphertext->c.bf_keys.size, cipher, SERIALIZED_QRE_SIZE);
    memcpy(output + 6*sizeof(int32_t) + ciphertext->c.bf_keys.num_hash_functions*ciphertext->c.bf_keys.salt_len + ciphertext->c.bf_keys.size + SERIALIZED_QRE_SIZE, ciphertext->encrypted_message, ciphertext->encrypted_message_size);

    return output;
}

CipherText * deserialize_ciphertext(uint8_t *input){

    CipherText *ciphertext = malloc(sizeof(CipherText));
    
    memcpy(&ciphertext->c.bf_keys.size, input + sizeof(int32_t), sizeof(int32_t));
    memcpy(&ciphertext->c.bf_keys.num_hash_functions, input + 2*sizeof(int32_t), sizeof(int32_t));
    memcpy(&ciphertext->c.bf_keys.hash_len, input + 3*sizeof(int32_t), sizeof(int32_t));
    memcpy(&ciphertext->c.bf_keys.salt_len, input + 4*sizeof(int32_t), sizeof(int32_t));
    memcpy(&ciphertext->encrypted_message_size, input + 5*sizeof(int32_t), sizeof(int32_t));
    
    ciphertext->c.bf_keys.salts = malloc(ciphertext->c.bf_keys.num_hash_functions * sizeof(uint8_t*));
    for (int i = 0; i < ciphertext->c.bf_keys.num_hash_functions; i++)
    {
        ciphertext->c.bf_keys.salts[i] = malloc(ciphertext->c.bf_keys.salt_len * sizeof(uint8_t));
        memcpy(ciphertext->c.bf_keys.salts[i], input + 6*sizeof(int32_t) + i*ciphertext->c.bf_keys.salt_len, ciphertext->c.bf_keys.salt_len);
    }
    
    ciphertext->c.bf_keys.bit_array = malloc(ciphertext->c.bf_keys.size * sizeof(uint8_t));
    memcpy(ciphertext->c.bf_keys.bit_array, input + 6*sizeof(int32_t) + ciphertext->c.bf_keys.num_hash_functions*ciphertext->c.bf_keys.salt_len, ciphertext->c.bf_keys.size);
    
    rbc_181_qre_init(&ciphertext->c.cipher);
    rbc_181_qre_from_string(ciphertext->c.cipher, input + 6*sizeof(int32_t) + ciphertext->c.bf_keys.num_hash_functions*ciphertext->c.bf_keys.salt_len + ciphertext->c.bf_keys.size);
    
    ciphertext->encrypted_message = malloc(ciphertext->encrypted_message_size * sizeof(uint8_t));
    memcpy(ciphertext->encrypted_message, input + 6*sizeof(int32_t) + ciphertext->c.bf_keys.num_hash_functions*ciphertext->c.bf_keys.salt_len + ciphertext->c.bf_keys.size + SERIALIZED_QRE_SIZE, ciphertext->encrypted_message_size);

    return ciphertext;
}