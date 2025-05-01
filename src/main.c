#include "main.h"
#include <string.h>
#include <stdio.h>

#include "utils.h"
#include "keygen.h"
#include "encrypt.h"
#include "decrypt.h"

int main(int argc, char *argv[]) {
	// if (argc != 4) {
	// 	printf("Usage : ./main [mode] <input> <output>\n");
	// 	return 0;
	// }

	rbc_181_field_init();
	rbc_181_qre_init_modulus(N);

	if (strcmp(argv[1], "keygen") == 0) {
		PublicKey pubKey;
		PrivateKey privKey;

		keygen(&pubKey, &privKey);

		uint8_t *serialized_public_key = serialize_public_key(&pubKey);
		uint8_t *serialized_private_key = serialize_private_key(&privKey);

		FILE *pubFile = fopen(argv[2], "wb");
		FILE *privFile = fopen(argv[3], "wb");
		if (!pubFile || !privFile) {
			printf("No such file or directory.\n");
			exit(1);
		}

		fwrite(serialized_public_key, sizeof(uint8_t), SERIALIZED_PUBLIC_KEY_SIZE, pubFile);
		fwrite(serialized_private_key, sizeof(uint8_t), SERIALIZED_PRIVATE_KEY_SIZE, privFile);
		fclose(pubFile); fclose(privFile);
	}

	else if (strcmp(argv[1], "encrypt") == 0) {
		uint8_t serialized_public_key[SERIALIZED_PUBLIC_KEY_SIZE];
		FILE *pubFile = fopen(argv[2], "rb");
		FILE *plaintextFile = fopen(argv[3], "rb");
		FILE *ciphertextFile = fopen(argv[4], "wb");
		if (!pubFile || !plaintextFile || !ciphertextFile) {
			printf("No such file or directory\n");
			exit(1);
		}
		fread(serialized_public_key, sizeof(uint8_t), SERIALIZED_PUBLIC_KEY_SIZE, pubFile);
		fclose(pubFile);

		fseek(plaintextFile, 0, SEEK_END);
		long file_size = ftell(plaintextFile);
		rewind(plaintextFile);
		uint8_t *plaintext = malloc(file_size + 1);
		fread(plaintext, sizeof(uint8_t), file_size, plaintextFile);
		plaintext[file_size] = '\0';
		fclose(plaintextFile);

		PublicKey *pubKey = deserialize_public_key(serialized_public_key);
		CipherText ciphertext;
		encrypt(pubKey, NULL, 0, plaintext, file_size, &ciphertext);

		uint8_t *serialized_ciphertext = serialize_ciphertext(&ciphertext);
		int size = 6*sizeof(uint32_t) + ciphertext.encrypted_message_size*sizeof(uint8_t) + ciphertext.c.bf_keys.num_hash_functions*ciphertext.c.bf_keys.salt_len + ciphertext.c.bf_keys.size + SERIALIZED_QRE_SIZE;
		fwrite(serialized_ciphertext, sizeof(uint8_t), size, ciphertextFile);
		fclose(ciphertextFile);
	}

	else if (strcmp(argv[1], "decrypt") == 0) {
		uint8_t serialized_private_key[SERIALIZED_PRIVATE_KEY_SIZE] = {0};
		FILE *privFile = fopen(argv[2], "rb");
		FILE *ciphertextFile = fopen(argv[3], "rb");
		FILE *plaintextFile = fopen(argv[4], "wb");
		if (!privFile || !ciphertextFile || !plaintextFile) {
			printf("No such file or directory\n");
			exit(1);
		}

		fread(serialized_private_key, sizeof(uint8_t), SERIALIZED_PRIVATE_KEY_SIZE, privFile);
		fclose(privFile);

		int32_t data_size = 0;
		fread(&data_size, sizeof(uint32_t), 1, ciphertextFile);
		uint8_t *serialized_ciphertext = calloc(data_size, sizeof(uint8_t));
		rewind(ciphertextFile);
		fread(serialized_ciphertext, sizeof(uint8_t), data_size, ciphertextFile);
		fclose(ciphertextFile);

		CipherText *ciphertext = deserialize_ciphertext(serialized_ciphertext);
		PrivateKey *privKey = deserialize_private_key(serialized_private_key);
		free(serialized_ciphertext);

		uint8_t *decrypted_plaintext = malloc(ciphertext->encrypted_message_size * sizeof(uint8_t));
		if (!decrypted_plaintext) {
			printf("Memory allocation failed.\n");
			exit(1);
		}
		
		if (decrypt(privKey, NULL, 0, ciphertext, decrypted_plaintext) == 0) {
			printf("Unable to decrypt data.\n");
			free(decrypted_plaintext);
			exit(1);
		}
		
		fwrite(decrypted_plaintext, sizeof(uint8_t), ciphertext->encrypted_message_size, plaintextFile);
		free(decrypted_plaintext);
		fclose(plaintextFile);
	}

	else {
		printf("Usage : ./main [mode] <input> <output>\n");
	}

	rbc_181_qre_clear_modulus();
	return 0;
}
