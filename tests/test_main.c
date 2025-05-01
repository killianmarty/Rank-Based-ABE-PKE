#define _POSIX_C_SOURCE 199309L
#include <stdio.h>
#include <time.h>
#include <string.h>
#include "../lib/rbc_lib/rbc.h"

#include "utils.h"
#include "keygen.h"
#include "encrypt.h"
#include "decrypt.h"
#include "bloomfilter.h"

void generate_random_string(int length, char *output);
int compare_qre(rbc_qre a, rbc_qre b);
int compare_vspace(rbc_vspace a, rbc_vspace b);

int test_keygen(PublicKey *testPub, PrivateKey *testPriv){
    return keygen(testPub, testPriv);
}

int test_encrypt(PublicKey *testPub, AttributeList* attributes, uint8_t *testPlaintext, int testPlaintext_size, CipherText *ciphertext){
    return encrypt(testPub, attributes, testPlaintext, testPlaintext_size, ciphertext);
}

int test_decrypt(PrivateKey *testPriv, AttributeList* attributes, CipherText *ciphertext, uint8_t *plaintext, int testPlaintext_size){
    uint8_t recovered_plaintext[128];
    decrypt(testPriv, attributes, ciphertext, recovered_plaintext);
    return memcmp((char *)plaintext, (char *)recovered_plaintext, testPlaintext_size) == 0;
}

int test_H(){

    for (size_t i = 0; i < 100; i++)
    {
        // Declarations
        rbc_qre E1, E2;
        uint8_t strE1[10240], strE2[10240];
        int size = 10000;
        char * payload = malloc(sizeof(char) * size);

        rbc_qre_init(&E1);
        rbc_qre_init(&E2);

        // Create two hashes of the same random string
        generate_random_string(size, payload);
        H((uint8_t *)payload, 10, E1);
        H((uint8_t *)payload, 10, E2);
        
        // Compare hashes
        rbc_qre_to_string(strE1, E1);
        rbc_qre_to_string(strE2, E2);
    
        if (strcmp((char*)strE1, (char*)strE2) != 0) {
            return 0;
        }

        // Free memory
        rbc_qre_clear(E1);
        rbc_qre_clear(E2);
    }

    return 1;
    
}

int test_H_bloomfilter(){

    // Declarations
    rbc_qre bf_hash;
    rbc_qre bf_hash2;
    BloomFilter bf;
    uint8_t *salts[NUM_HASH_FUNCTIONS];
    uint8_t strbf_hash[10240], strbf_hash2[10240] = {0};
    size_t string_length = 10000;
    char *strings[1000];

    // Generate random salts
    for (int i = 0; i < NUM_HASH_FUNCTIONS; i++) {
        salts[i] = (uint8_t *)malloc(SALT_SIZE);
        generate_random_string(SALT_SIZE, (char *)salts[i]);
    }


    bloom_filter_init(&bf, BLOOM_FILTER_SIZE, NUM_HASH_FUNCTIONS, HASH_LEN, salts, SALT_SIZE);
    rbc_qre_init(&bf_hash);
    rbc_qre_init(&bf_hash2);

    // Generate random strings and add them to the bloom filter
    for (size_t i = 0; i < 1000; i++) {
        strings[i] = (char *)malloc(string_length);
        generate_random_string(string_length, strings[i]);
        bloom_filter_add(&bf, strings[i]);
    }

    // Hash the bloom filters
    H(bf.bit_array, bf.size, bf_hash);
    H(bf.bit_array, bf.size, bf_hash2);

    // Compare the hashes
    rbc_qre_to_string(strbf_hash, bf_hash);
    rbc_qre_to_string(strbf_hash2, bf_hash2);

    if (strcmp((char*)strbf_hash, (char*)strbf_hash2) == 0) {
        return 1;
    } else {
        return 0;
    }

    return 1;
}

int test_scheme(){

    for (size_t i = 0; i < 100; i++)
    {
        // Declarations
        PublicKey testPub;
        PrivateKey testPriv;
        CipherText ciphertext;
        uint8_t plaintext[256];
        uint8_t decrypted_plaintext[256];

        AttributeList wanted, available;

        attribute_list_init(&wanted, 10);
        attribute_list_init(&available, 20);

        // Generate random policy attributes
        for(int i = 0; i < 10; i++){
            char *key = malloc(sizeof(char)*ATTRIBUTE_KEY_SIZE);
            char *val = malloc(sizeof(char)*ATTRIBUTE_VALUE_SIZE);
            generate_random_string(ATTRIBUTE_KEY_SIZE, key);
            generate_random_string(ATTRIBUTE_VALUE_SIZE, val);
            attribute_list_add(&wanted, key, val);
            attribute_list_add(&available, key, val);
            free(key);
            free(val);
        }

        // Generate random attributes that does not belong to the policy
        for(int i = 10; i < 20; i++){
            char *key = malloc(sizeof(char)*ATTRIBUTE_KEY_SIZE);
            char *val = malloc(sizeof(char)*ATTRIBUTE_VALUE_SIZE);
            generate_random_string(ATTRIBUTE_KEY_SIZE, key);
            generate_random_string(ATTRIBUTE_VALUE_SIZE, val);
            attribute_list_add(&available, key, val);
            free(key);
            free(val);
        }

        // Execute the scheme
        keygen(&testPub, &testPriv);
        encrypt(&testPub, &wanted, plaintext, 256, &ciphertext);
        int res = decrypt(&testPriv, &available, &ciphertext, decrypted_plaintext);

        if(res == 0) return 0;
        
        // Compare the shared secret
        if (memcmp(plaintext, decrypted_plaintext, 256) != 0)
        {
            return 0;
        }
        
        // Free memory
        rbc_qre_clear(ciphertext.c.cipher);
        rbc_qre_clear(testPub.h);
        rbc_qre_clear(testPriv.x);
        rbc_qre_clear(testPriv.y);
        rbc_vspace_clear(testPriv.F);
        
    }

    return 1;
}

int test_bloomfilter(){

    // Declarations
    BloomFilter bf;
    uint8_t *salts[NUM_HASH_FUNCTIONS];
    size_t n = 100;
    size_t string_length = 10;
    char *strings[n];
    char *not_in_filter[n];

    // Generate random salts
    for (int i = 0; i < NUM_HASH_FUNCTIONS; i++) {
        salts[i] = (uint8_t *)malloc(SALT_SIZE);
        generate_random_string(SALT_SIZE, (char *)salts[i]);
    }

    bloom_filter_init(&bf, BLOOM_FILTER_SIZE, NUM_HASH_FUNCTIONS, HASH_LEN, salts, SALT_SIZE);

    // Generate random strings and add them to the bloom filter
    for (size_t i = 0; i < n; i++) {
        strings[i] = (char *)malloc(string_length);
        not_in_filter[i] = (char *)malloc(string_length);

        generate_random_string(string_length, strings[i]);
        generate_random_string(string_length, not_in_filter[i]);

        bloom_filter_add(&bf, strings[i]);
    }

    // Check if the generated strings are in the bloom filter
    for (size_t i = 0; i < n; i++) {
        if (!bloom_filter_check(&bf, strings[i])) {
            return 0;
        }
    }

    // Check if the not_in_filter strings are not in the bloom filter
    for (size_t i = 0; i < n; i++) {
        if (bloom_filter_check(&bf, not_in_filter[i])) {
            return 0;
        }
    }

    // Free memory
    for (size_t i = 0; i < n; i++) {
        free(strings[i]);
        free(not_in_filter[i]);
    }
    for (int i = 0; i < NUM_HASH_FUNCTIONS; i++) {
        free(salts[i]);
    }

    return 1;
}

int test_serialization(){
    PrivateKey testPriv;
    PrivateKey *deserialized_priv_key;
    PublicKey testPub;
    PublicKey *deserialized_pub_key;
    CipherText ciphertext;
    CipherText *deserialized_ciphertext;
    AttributeList att;

    uint8_t *serialized_ciphertext;
    uint8_t *serialized_priv_key;
    uint8_t *serialized_pub_key;

    uint8_t secret[SECRET_KEY_BYTES];
    generate_random_string(SECRET_KEY_BYTES, (char *)secret);

    attribute_list_init(&att, 10);

    keygen(&testPub, &testPriv);
    encrypt(&testPub, &att, secret, SECRET_KEY_BYTES, &ciphertext);

    serialized_priv_key = serialize_private_key(&testPriv);
    deserialized_priv_key = deserialize_private_key(serialized_priv_key);

    serialized_pub_key = serialize_public_key(&testPub);
    deserialized_pub_key = deserialize_public_key(serialized_pub_key);

    serialized_ciphertext = serialize_ciphertext(&ciphertext);
    deserialized_ciphertext = deserialize_ciphertext(serialized_ciphertext);

    if(compare_qre(testPriv.x, deserialized_priv_key->x) == 0){
        return 0;
    }
    if(compare_qre(testPriv.y, deserialized_priv_key->y) == 0){
        return 0;
    }
    if(compare_vspace(testPriv.F, deserialized_priv_key->F) == 0){
        return 0;
    }

    
    if(compare_qre(testPub.h, deserialized_pub_key->h) == 0){
        return 0;
    }
    
    if(compare_qre(ciphertext.c.cipher, deserialized_ciphertext->c.cipher) == 0){
        return 0;
    }
    if(memcmp(ciphertext.c.bf_keys.bit_array, deserialized_ciphertext->c.bf_keys.bit_array, ciphertext.c.bf_keys.size) != 0){
        return 0;
    }
    for(int i = 0; i < ciphertext.c.bf_keys.num_hash_functions; i++){
        if(memcmp(ciphertext.c.bf_keys.salts[i], deserialized_ciphertext->c.bf_keys.salts[i], ciphertext.c.bf_keys.salt_len) != 0){
            return 0;
        }
    }
    if(ciphertext.encrypted_message_size != deserialized_ciphertext->encrypted_message_size){
        return 0;
    }
    if(memcmp(ciphertext.encrypted_message, deserialized_ciphertext->encrypted_message, ciphertext.encrypted_message_size) != 0){
        return 0;
    }

    return 1;
}

/*******************************/
/*******************************/
/*******************************/

int compare_qre(rbc_qre a, rbc_qre b){
    uint8_t strE1[10240] = {0};
    uint8_t strE2[10240] = {0};
    rbc_qre_to_string(strE1, a);
    rbc_qre_to_string(strE2, b);
    if (memcmp((char*)strE1, (char*)strE2, 10240) != 0) {
        return 0;
    }
    return 1;
}

int compare_vspace(rbc_vspace a, rbc_vspace b){
    uint8_t strE1[10240] = {0};
    uint8_t strE2[10240] = {0};
    rbc_vec_to_string(strE1, a, D);
    rbc_vec_to_string(strE2, b, D);
    if (memcmp((char*)strE1, (char*)strE2, 10240) != 0) {
        return 0;
    }
    return 1;
}

void generate_random_string(int length, char *output){
    for (int j = 0; j < length-1; j++) {
        output[j] = (rand() % 26 + 30);
    }
    output[length-1] = '\0';
}

void print_result(struct timespec startTime, int result){
    struct timespec endTime;
    clock_gettime(CLOCK_MONOTONIC, &endTime);

    long elapsed_ms = (endTime.tv_sec - startTime.tv_sec) * 1000L + 
                      (endTime.tv_nsec - startTime.tv_nsec) / 1000000L;

    if(result){
        printf("\033[0;32mOK\033[0m");
    }else{
        printf("\033[0;31mNO\033[0m");
    }
    printf(" (%ld ms)\n", elapsed_ms);
}

struct timespec get_current_time(){
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return ts;
}

int main(){
    printf("\n┌───────────────┐\n│ Running tests │\n└───────────────┘\n\n");

    rbc_field_init();
    rbc_qre_init_modulus(N);

    struct timespec startTime;

    PublicKey testPub;
    PrivateKey testPriv;
    AttributeList testAttr;

    attribute_list_init(&testAttr, 10);

    //Testing Bloom Filter
    startTime = get_current_time();
    printf("Testing Bloom Filter... "); fflush(stdout);
    print_result(startTime, test_bloomfilter());

    //Testing H
    startTime = get_current_time();
    printf("Testing H... "); fflush(stdout);
    print_result(startTime, test_H());
    
    //Testing H with Bloom Filter
    startTime = get_current_time();
    printf("Testing H with Bloom Filter... "); fflush(stdout);
    print_result(startTime, test_H_bloomfilter());

    //Testing keygen
    startTime = get_current_time();
    printf("Testing keygen... "); fflush(stdout);
    print_result(startTime, test_keygen(&testPub, &testPriv));

    //Testing encrypt
    startTime = get_current_time();
    printf("Testing encrypt... "); fflush(stdout);
    uint8_t testPlaintext[128];
    CipherText ciphertext;
    generate_random_string(SECRET_KEY_BYTES, (char *)testPlaintext);
    rbc_qre_init(&ciphertext.c.cipher);
    print_result(startTime, test_encrypt(&testPub, &testAttr, testPlaintext, 128, &ciphertext));

    //Testing decaps
    startTime = get_current_time();
    printf("Testing decrypt... "); fflush(stdout);
    print_result(startTime, test_decrypt(&testPriv, &testAttr, &ciphertext, testPlaintext, 128));

    //Testing complete scheme
    startTime = get_current_time();
    printf("Testing complete scheme (100 times)... "); fflush(stdout);
    print_result(startTime, test_scheme());

    //Testing serialization
    startTime = get_current_time();
    printf("Testing serialization... "); fflush(stdout);
    print_result(startTime, test_serialization());

    rbc_qre_clear_modulus();
    return 0;
}