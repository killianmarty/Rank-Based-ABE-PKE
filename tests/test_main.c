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
    encaps(testPub, shared_secret, cipher);

    return 1;
}

int test_decaps(uint8_t *shared_secret, rbc_181_qre cipher, PrivateKey *testPriv){
    decaps(shared_secret, cipher, testPriv);

    return 1;
}

int test_H(){
    random_source prng;
    random_source sk_seedexpander;
    uint8_t sk_seed[SEEDEXPANDER_SEED_BYTES];
    rbc_181_vspace E;
    rbc_181_qre E1, E2;

    random_source_init(&prng, RANDOM_SOURCE_PRNG);
    random_source_init(&sk_seedexpander, RANDOM_SOURCE_SEEDEXP);
    random_source_get_bytes(&prng, sk_seed, SEEDEXPANDER_SEED_BYTES);
    random_source_seed(&sk_seedexpander, sk_seed);

    rbc_181_vspace_init(&E, R);
    rbc_181_vspace_set_random_full_rank(&sk_seedexpander, E, R);
    rbc_181_qre_init(&E1);
    rbc_181_qre_init(&E2);

    char payload[] = "test_payload";
    H((uint8_t *)payload, 10, E, R, E1);
    H((uint8_t *)payload, 10, E, R, E2);

    uint8_t strE1[10240], strE2[10240];
    rbc_181_qre_to_string(strE1, E1);
    rbc_181_qre_to_string(strE2, E2);

    if (strcmp((char*)strE1, (char*)strE2) == 0) {
        return 1;
    } else {
        return 0;
    }
    
}

int test_scheme(){

    for (size_t i = 0; i < 100; i++)
    {
        PublicKey testPub;
        PrivateKey testPriv;

        keygen(&testPub, &testPriv);

        uint8_t shared_secret[SECRET_KEY_BYTES];
        rbc_181_qre cipher;
        rbc_181_qre_init(&cipher);
        encaps(&testPub, shared_secret, cipher);

        uint8_t decapsed_secret[SECRET_KEY_BYTES];
        decaps(decapsed_secret, cipher, &testPriv);

        if (memcmp(shared_secret, decapsed_secret, SECRET_KEY_BYTES) != 0)
        {
            return 0;
        }

        rbc_181_qre_clear(cipher);
        rbc_181_qre_clear(testPub.h);
        rbc_181_qre_clear(testPriv.x);
        rbc_181_qre_clear(testPriv.y);
        rbc_181_vspace_clear(testPriv.F);
    }
    

    return 1;
}

int test_bloomfilter(){
    BloomFilter bf;
    char *salts[NUM_HASH_FUNCTIONS];
    for (int i = 0; i < NUM_HASH_FUNCTIONS; i++) {
        salts[i] = (char *)malloc(HASH_LEN);
        for (int j = 0; j < HASH_LEN; j++) {
            salts[i][j] = rand() % 256;
        }
    }

    bloom_filter_init(&bf, BLOOM_FILTER_SIZE, NUM_HASH_FUNCTIONS, HASH_LEN);

    char *str = "test_string";
    bloom_filter_add(&bf, str, salts);

    int result = bloom_filter_check(&bf, str, salts);

    for (int i = 0; i < NUM_HASH_FUNCTIONS; i++) {
        free(salts[i]);
    }

    return result;
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

    struct timespec startTime;

    PublicKey testPub;
    PrivateKey testPriv;


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

    //Testing H
    startTime = get_current_time();
    printf("Testing H... "); fflush(stdout);
    print_result(startTime, test_H());

    //Testing Bloom Filter
    startTime = get_current_time();
    printf("Testing Bloom Filter... "); fflush(stdout);
    print_result(startTime, test_bloomfilter());

    return 0;
}