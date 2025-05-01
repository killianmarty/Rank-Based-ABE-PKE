#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"
#include "keygen.h"
#include "encrypt.h"
#include "decrypt.h"

static void print_help(const char *prog) {
    printf("Usage: %s [mode] ...\n"
           "  keygen: %s keygen <public_key_file> <private_key_file>\n"
           "  encrypt: %s encrypt <public_key_file> <attributes_file> <plaintext_file> <ciphertext_file>\n"
           "  decrypt: %s decrypt <private_key_file> <attributes_file> <ciphertext_file> <plaintext_file>\n",
           prog, prog, prog, prog);
}

static int check_arg(int argc, int expected, const char *prog) {
    if (argc != expected)
        print_help(prog);
    return (argc == expected);
}

int main(int argc, char **argv) {
    rbc_181_field_init();
    rbc_181_qre_init_modulus(N);

    if (argc < 2) {
        print_help(argv[0]);
        exit(EXIT_FAILURE);
    }

    const char *mode = argv[1];

    // Key generation mode
    if (strcmp(mode, "keygen") == 0 && check_arg(argc, 4, argv[0])) {

        PublicKey pub; PrivateKey priv;
        keygen(&pub, &priv);

        // Serialize keys
        uint8_t *pub_ser = serialize_public_key(&pub);
        uint8_t *priv_ser = serialize_private_key(&priv);

        // Write serialized keys to files
        FILE *fpub = fopen(argv[2], "wb");
        FILE *fpriv = fopen(argv[3], "wb");
        if (!fpub || !fpriv) exit(EXIT_FAILURE);
        fwrite(pub_ser, 1, SERIALIZED_PUBLIC_KEY_SIZE, fpub);
        fwrite(priv_ser, 1, SERIALIZED_PRIVATE_KEY_SIZE, fpriv);
        fclose(fpub); fclose(fpriv);
    }

    // Encryption mode
    else if (strcmp(mode, "encrypt") == 0 && check_arg(argc, 6, argv[0])) {

        // Open input and output files
        FILE *fpub = fopen(argv[2], "rb"), *fattr = fopen(argv[3], "rb");
        FILE *fin = fopen(argv[4], "rb"), *fout = fopen(argv[5], "wb");
        if (!fpub || !fattr || !fin || !fout) exit(EXIT_FAILURE);

        // Load public key
        uint8_t pub_ser[SERIALIZED_PUBLIC_KEY_SIZE];
        fread(pub_ser, 1, sizeof pub_ser, fpub);
        fclose(fpub);

        // Read plaintext
        fseek(fin, 0, SEEK_END);
        long in_sz = ftell(fin);
        rewind(fin);
        uint8_t *plain = malloc(in_sz + 1);
        fread(plain, 1, in_sz, fin);
        plain[in_sz] = '\0';
        fclose(fin);

        // Read attributes
        fseek(fattr, 0, SEEK_END);
        long attr_sz = ftell(fattr);
        rewind(fattr);
        uint8_t *attr_ser = malloc(attr_sz + 1);
        fread(attr_ser, 1, attr_sz, fattr);
        attr_ser[attr_sz] = '\0';
        fclose(fattr);

        // Deserialize attributes and public key
        AttributeList *attrs = deserialize_attributes(attr_ser);
        free(attr_ser);
        PublicKey *pub = deserialize_public_key(pub_ser);

        // Perform encryption
        CipherText ct;
        encrypt(pub, attrs, plain, in_sz, &ct);

        // Calculate serialized ciphertext size and write to file
        size_t csize = 6 * sizeof(uint32_t)
                       + ct.encrypted_message_size
                       + ct.c.bf_keys.num_hash_functions * ct.c.bf_keys.salt_len
                       + ct.c.bf_keys.size
                       + SERIALIZED_QRE_SIZE;
        uint8_t *ct_ser = serialize_ciphertext(&ct);
        fwrite(ct_ser, 1, csize, fout);
        fclose(fout);
    }

    // Decryption mode
    else if (strcmp(mode, "decrypt") == 0 && check_arg(argc, 6, argv[0])) {
        // Open key, attribute, ciphertext, and output files
        FILE *fpriv = fopen(argv[2], "rb"), *fattr = fopen(argv[3], "rb");
        FILE *fin = fopen(argv[4], "rb"), *fout = fopen(argv[5], "wb");
        if (!fpriv || !fattr || !fin || !fout) exit(EXIT_FAILURE);

        // Load private key
        uint8_t priv_ser[SERIALIZED_PRIVATE_KEY_SIZE];
        fread(priv_ser, 1, sizeof priv_ser, fpriv);
        fclose(fpriv);

        // Read serialized ciphertext
        fseek(fin, 0, SEEK_END);
        size_t ct_sz = ftell(fin);
        rewind(fin);
        uint8_t *ct_ser = malloc(ct_sz);
        fread(ct_ser, 1, ct_sz, fin);
        fclose(fin);

        // Read and deserialize attributes
        fseek(fattr, 0, SEEK_END);
        long attr_sz = ftell(fattr);
        rewind(fattr);
        uint8_t *attr_ser = malloc(attr_sz + 1);
        fread(attr_ser, 1, attr_sz, fattr);
        attr_ser[attr_sz] = '\0';
        fclose(fattr);
        AttributeList *attrs = deserialize_attributes(attr_ser);
        free(attr_ser);

        // Deserialize ciphertext and private key
        CipherText *ct = deserialize_ciphertext(ct_ser);
        free(ct_ser);
        PrivateKey *priv = deserialize_private_key(priv_ser);

        // Allocate buffer and decrypt
        uint8_t *out_buf = malloc(ct->encrypted_message_size);
        if (!decrypt(priv, attrs, ct, out_buf)){
			printf("Decryption failed: bad attributes, key or error\n");
            exit(EXIT_FAILURE);
		}

        // Write decrypted plaintext to output file
        fwrite(out_buf, 1, ct->encrypted_message_size, fout);
        free(out_buf);
        fclose(fout);
    }

    // Unrecognized mode: display help
    else {
        print_help(argv[0]);
    }

    // Free memory
    rbc_181_qre_clear_modulus();
    return 0;
}
