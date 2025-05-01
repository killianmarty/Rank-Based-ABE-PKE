
#include "decrypt.h"

int decrypt(PrivateKey *priv, AttributeList *attributes, CipherText *ciphertext,  uint8_t *plaintext) {
    
    // Declarations
    rbc_181_vspace E;
    rbc_181_qre xc, cipher_dec, bf_hash;
    BloomFilter bf_att;
    uint8_t support_string[R_BYTES];
    uint32_t dimE = 0;
    
    // Initialisations
    rbc_181_qre_init(&xc);
    rbc_181_qre_init(&bf_hash);
    rbc_181_qre_init(&cipher_dec);
    rbc_181_vspace_init(&E, N);
    bloom_filter_init(&bf_att, ciphertext->c.bf_keys.size, ciphertext->c.bf_keys.num_hash_functions, ciphertext->c.bf_keys.hash_len, (uint8_t**)ciphertext->c.bf_keys.salts, ciphertext->c.bf_keys.salt_len);


    // Find the needed attributes and build the bloom filter
    for (int i = 0; i < attributes->count; i++)
    {
      if(bloom_filter_check(&ciphertext->c.bf_keys, attributes->attributes[i].key)) {
        char attribute_string[ATTRIBUTE_STRING_SIZE] = {0};
        attribute_to_string(&attributes->attributes[i], attribute_string);

        bloom_filter_add(&bf_att, attribute_string);
      }
    }

    // Decoding syndrome
    H(bf_att.bit_array, bf_att.size, bf_hash);
    rbc_181_qre_inv(bf_hash, bf_hash);
    rbc_181_qre_mul(cipher_dec, ciphertext->c.cipher, bf_hash);
    rbc_181_qre_mul(xc, priv->x, cipher_dec);
    dimE = rbc_181_lrpc_RSR(E, R, priv->F, D, xc->v, N);
    
    uint8_t hashedE[SECRET_KEY_BYTES];
    if(dimE != 0) {
      rbc_181_vec_echelonize(E, R);
      rbc_181_vec_to_string(support_string, E, R);
      SHA512(support_string, R_BYTES, hashedE);
    } else {
      memset(hashedE, 0, SECRET_KEY_BYTES); //We cannot decode (bad attributes or error)
    }

    // Compute the encrypted message
    for (int i = 0; i < ciphertext->encrypted_message_size; i++) {
      plaintext[i] = ciphertext->encrypted_message[i] ^ hashedE[i % SECRET_KEY_BYTES];
    }
    

    // Free memory
    rbc_181_vspace_clear(E);
    rbc_181_qre_clear(xc);
    rbc_181_qre_clear(bf_hash);

    return dimE!=0;
    
  }