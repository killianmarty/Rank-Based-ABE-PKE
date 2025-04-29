#define _POSIX_C_SOURCE 199309L
#include <stdio.h>
#include <time.h>
#include <string.h>
#include "../lib/rbc_lib/rbc.h"

#include "keygen.h"
#include "encaps.h"
#include "decaps.h"
#include "utils.h"
#include "bloomfilter.h"

int test_keygen(PublicKey *testPub, PrivateKey *testPriv){
    keygen(testPub, testPriv);

    return 1;
}

int test_encaps(PublicKey *testPub, uint8_t *shared_secret, rbc_181_qre cipher){
    Message msg;
    encaps(testPub, NULL, 0, shared_secret, &msg);

    return 1;
}

int test_decaps(uint8_t *shared_secret, rbc_181_qre cipher, PrivateKey *testPriv){
    Message msg;
    rbc_181_qre_init(&msg.cipher);
    decaps(testPriv, &msg, NULL, 0, shared_secret);

    return 1;
}

int test_H(){

    for (size_t i = 0; i < 100; i++)
    {
        rbc_181_qre E1, E2;


        rbc_181_qre_init(&E1);
        rbc_181_qre_init(&E2);
        int size = 10000;
        char * payload = malloc(sizeof(char) * size+1);
        for (int i = 0; i < size; i++) {
            payload[i] = (rand() % 26);
        }
        payload[size] = '\0';
        H((uint8_t *)payload, 10, E1);
        H((uint8_t *)payload, 10, E2);
        
        uint8_t strE1[10240], strE2[10240];
        rbc_181_qre_to_string(strE1, E1);
        rbc_181_qre_to_string(strE2, E2);
    
        if (strcmp((char*)strE1, (char*)strE2) != 0) {
            return 0;
        }

        rbc_181_qre_clear(E1);
        rbc_181_qre_clear(E2);
    }

    return 1;
    
}

int test_H_bloomfilter(){
    BloomFilter bf;
    uint8_t *salts[NUM_HASH_FUNCTIONS];
    for (int i = 0; i < NUM_HASH_FUNCTIONS; i++) {
        salts[i] = (uint8_t *)malloc(SALT_SIZE);
        for (int j = 0; j < SALT_SIZE; j++) {
            salts[i][j] = rand() % 256;
        }
    }

    bloom_filter_init(&bf, BLOOM_FILTER_SIZE, NUM_HASH_FUNCTIONS, HASH_LEN, salts, SALT_SIZE);

    char *strings[100];
    size_t string_length = 10000;

    for (size_t i = 0; i < 100; i++) {
        strings[i] = (char *)malloc(string_length + 1);
        for (size_t j = 0; j < string_length; j++) {
            strings[i][j] = 'a' + (rand() % 26);
        }
        strings[i][string_length] = '\0';
        bloom_filter_add(&bf, strings[i]);
    }

    rbc_181_qre bf_hash;
    rbc_181_qre bf_hash2;

    rbc_181_qre_init(&bf_hash);
    rbc_181_qre_init(&bf_hash2);
    H(bf.bit_array, bf.size, bf_hash);
    H(bf.bit_array, bf.size, bf_hash2);

    uint8_t strbf_hash[10240], strbf_hash2[10240] = {0};
    rbc_181_qre_to_string(strbf_hash, bf_hash);
    rbc_181_qre_to_string(strbf_hash2, bf_hash2);

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
        PublicKey testPub;
        PrivateKey testPriv;
        Message msg;

        keygen(&testPub, &testPriv);

        uint8_t shared_secret[SECRET_KEY_BYTES];
        encaps(&testPub, NULL, 0, shared_secret, &msg);

        uint8_t decapsed_secret[SECRET_KEY_BYTES];
        decaps(&testPriv, &msg, NULL, 0, decapsed_secret);

        if (memcmp(shared_secret, decapsed_secret, SECRET_KEY_BYTES) != 0)
        {
            return 0;
        }

        rbc_181_qre_clear(msg.cipher);
        rbc_181_qre_clear(testPub.h);
        rbc_181_qre_clear(testPriv.x);
        rbc_181_qre_clear(testPriv.y);
        rbc_181_vspace_clear(testPriv.F);
    }
    

    return 1;
}

int test_bloomfilter(){
    BloomFilter bf;
    uint8_t *salts[NUM_HASH_FUNCTIONS];
    for (int i = 0; i < NUM_HASH_FUNCTIONS; i++) {
        salts[i] = (uint8_t *)malloc(SALT_SIZE);
        for (int j = 0; j < SALT_SIZE; j++) {
            salts[i][j] = rand() % 256;
        }
    }

    bloom_filter_init(&bf, BLOOM_FILTER_SIZE, NUM_HASH_FUNCTIONS, HASH_LEN, salts, SALT_SIZE);

    size_t n = 100;
    char *strings[n];
    size_t string_length = 10;

    for (size_t i = 0; i < n; i++) {
        strings[i] = (char *)malloc(string_length + 1);
        for (size_t j = 0; j < string_length; j++) {
            strings[i][j] = 'a' + (rand() % 26);
        }
        strings[i][string_length] = '\0';
        bloom_filter_add(&bf, strings[i]);
    }

    for (size_t i = 0; i < n; i++) {
        if (!bloom_filter_check(&bf, strings[i])) {
            return 0;
        }
    }

    char *not_in_filter[n];
    for (size_t i = 0; i < n; i++) {
        not_in_filter[i] = (char *)malloc(string_length + 1);
        for (size_t j = 0; j < string_length; j++) {
            not_in_filter[i][j] = 'a' + (rand() % 26);
        }
        not_in_filter[i][string_length] = '\0';

        if (bloom_filter_check(&bf, not_in_filter[i])) {
            return 0;
        }
    }

    return 1;
}

/*******************************/
/*******************************/
/*******************************/

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

    rbc_181_field_init();
    rbc_181_qre_init_modulus(N);

    struct timespec startTime;

    PublicKey testPub;
    PrivateKey testPriv;

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

    //Testing encaps
    startTime = get_current_time();
    printf("Testing encaps... "); fflush(stdout);
    uint8_t shared_secret[SECRET_KEY_BYTES];
    rbc_181_qre cipher;
    rbc_181_qre_init(&cipher);
    print_result(startTime, test_encaps(&testPub, shared_secret, cipher));

    //Testing decaps
    startTime = get_current_time();
    printf("Testing decaps... "); fflush(stdout);
    uint8_t decapsed_secret[SECRET_KEY_BYTES];
    print_result(startTime, test_decaps(decapsed_secret, cipher, &testPriv));

    //Testing complete scheme
    startTime = get_current_time();
    printf("Testing complete scheme (100 times)... "); fflush(stdout);
    print_result(startTime, test_scheme());

    rbc_181_qre_clear_modulus();
    return 0;
}