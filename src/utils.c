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

    uint8_t x[SERIALIZED_QRE_SIZE];
    uint8_t y[SERIALIZED_QRE_SIZE];
    uint8_t F[SERIALIZED_VSPACE_SIZE];

    rbc_181_qre_to_string(x, key->x);
    rbc_181_qre_to_string(y, key->y);
    rbc_181_vec_to_string(F, key->F, N);

    memcpy(output, x, SERIALIZED_QRE_SIZE);
    memcpy(output + SERIALIZED_QRE_SIZE, y, SERIALIZED_QRE_SIZE);
    memcpy(output + 2*SERIALIZED_QRE_SIZE, F, SERIALIZED_VSPACE_SIZE);

    return output;
}

PrivateKey * deserialize_private_key(uint8_t *input){

    PrivateKey *key = malloc(sizeof(PrivateKey));

    uint8_t x[SERIALIZED_QRE_SIZE];
    uint8_t y[SERIALIZED_QRE_SIZE];
    uint8_t F[SERIALIZED_VSPACE_SIZE];

    memcpy(x, input, SERIALIZED_QRE_SIZE);
    memcpy(y, input + SERIALIZED_QRE_SIZE, SERIALIZED_QRE_SIZE);
    memcpy(F, input + 2*SERIALIZED_QRE_SIZE, SERIALIZED_VSPACE_SIZE);

    rbc_181_qre_init(&key->x);
    rbc_181_qre_init(&key->y);
    rbc_181_vspace_init(&key->F, N);

    rbc_181_qre_from_string(key->x, x);
    rbc_181_qre_from_string(key->y, y);
    rbc_181_vec_from_string(key->F, N, F);

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

uint8_t * serialize_message(Message *msg){
    int data_size = 5*sizeof(uint32_t) + msg->bf_keys.num_hash_functions*msg->bf_keys.salt_len + msg->bf_keys.size + SERIALIZED_QRE_SIZE;
    uint8_t *output = calloc(data_size, sizeof(uint8_t));
    uint8_t cipher[SERIALIZED_QRE_SIZE];

    rbc_181_qre_to_string(cipher, msg->cipher);
    
    memcpy(output, &data_size, sizeof(int32_t));
    memcpy(output + sizeof(int32_t), &msg->bf_keys.size, sizeof(int32_t));
    memcpy(output + 2*sizeof(int32_t), &msg->bf_keys.num_hash_functions, sizeof(int32_t));
    memcpy(output + 3*sizeof(int32_t), &msg->bf_keys.hash_len, sizeof(int32_t));
    memcpy(output + 4*sizeof(int32_t), &msg->bf_keys.salt_len, sizeof(int32_t));
    for (int i = 0; i < msg->bf_keys.num_hash_functions; i++)
    {
        memcpy(output + 5*sizeof(int32_t) + i*msg->bf_keys.salt_len, msg->bf_keys.salts[i], msg->bf_keys.salt_len);
    }
    memcpy(output + 5*sizeof(int32_t) + msg->bf_keys.num_hash_functions*msg->bf_keys.salt_len, msg->bf_keys.bit_array, msg->bf_keys.size);
    memcpy(output + 5*sizeof(int32_t) + msg->bf_keys.num_hash_functions*msg->bf_keys.salt_len + msg->bf_keys.size, cipher, SERIALIZED_QRE_SIZE);
    

    return output;
}

Message * deserialize_message(uint8_t *input){

    Message *msg = malloc(sizeof(Message));
    
    memcpy(&msg->bf_keys.size, input + sizeof(int32_t), sizeof(int32_t));
    memcpy(&msg->bf_keys.num_hash_functions, input + 2*sizeof(int32_t), sizeof(int32_t));
    memcpy(&msg->bf_keys.hash_len, input + 3*sizeof(int32_t), sizeof(int32_t));
    memcpy(&msg->bf_keys.salt_len, input + 4*sizeof(int32_t), sizeof(int32_t));
    
    msg->bf_keys.salts = malloc(msg->bf_keys.num_hash_functions*sizeof(uint8_t*));
    for (int i = 0; i < msg->bf_keys.num_hash_functions; i++)
    {
        msg->bf_keys.salts[i] = malloc(msg->bf_keys.salt_len*sizeof(uint8_t));
        memcpy(msg->bf_keys.salts[i], input + 5*sizeof(int32_t) + i*msg->bf_keys.salt_len, msg->bf_keys.salt_len);
    }
    
    msg->bf_keys.bit_array = malloc(msg->bf_keys.size*sizeof(uint8_t));
    memcpy(msg->bf_keys.bit_array, input + 5*sizeof(int32_t) + msg->bf_keys.num_hash_functions*msg->bf_keys.salt_len, msg->bf_keys.size);
    
    rbc_181_qre_init(&msg->cipher);
    rbc_181_qre_from_string(msg->cipher, input + 5*sizeof(int32_t) + msg->bf_keys.num_hash_functions*msg->bf_keys.salt_len + msg->bf_keys.size);

    return msg;
}