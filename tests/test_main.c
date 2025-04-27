#define _POSIX_C_SOURCE 199309L
#include <stdio.h>
#include <time.h>
#include <string.h>
#include "../lib/rbc_lib/rbc.h"

#include "keygen.h"
#include "encaps.h"
#include "decaps.h"
#include "utils.h"

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

int test_scheme(){

    for (size_t i = 0; i < 1000; i++)
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
    printf("Testing complete scheme (1000 times)... "); fflush(stdout);
    print_result(startTime, test_scheme());

    return 0;
}