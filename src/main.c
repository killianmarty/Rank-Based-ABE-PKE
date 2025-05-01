#include "main.h"
#include <string.h>
#include <stdio.h>

#include "utils.h"
#include "keygen.h"
#include "encaps.h"
#include "decaps.h"

int main(int argc, char *argv[]) {
	if (argc != 4) {
		printf("Usage : ./main [mode] <input> <output>\n");
		return 0;
	}

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

	else if (strcmp(argv[1], "encaps") == 0) {
		uint8_t serialized_public_key[SERIALIZED_PUBLIC_KEY_SIZE];
		FILE *pubFile = fopen(argv[2], "rb");
		FILE *msgFile = fopen(argv[3], "wb");
		if (!pubFile || !msgFile) {
			printf("No such file or directory\n");
			exit(1);
		}
		fread(serialized_public_key, sizeof(uint8_t), SERIALIZED_PUBLIC_KEY_SIZE, pubFile);
		fclose(pubFile);

		PublicKey *pubKey = deserialize_public_key(serialized_public_key);
		Message msg;
		uint8_t shared_secret[SECRET_KEY_BYTES];
		encaps(pubKey, NULL, 0, shared_secret, &msg);

		printf("AES Key: ");
		for (int i = 0; i < SECRET_KEY_BYTES; i++) printf("%02x", shared_secret[i]);
		printf("\n");

		uint8_t *serialized_message = serialize_message(&msg);
		int size = 4 * sizeof(uint32_t) + msg.bf_keys.num_hash_functions * msg.bf_keys.salt_len + msg.bf_keys.size + SERIALIZED_QRE_SIZE;
		fwrite(serialized_message, sizeof(uint8_t), size, msgFile);
		fclose(msgFile);
	}

	else if (strcmp(argv[1], "decaps") == 0) {
		uint8_t serialized_private_key[SERIALIZED_PRIVATE_KEY_SIZE] = {0};
		FILE *privFile = fopen(argv[2], "rb");
		FILE *msgFile = fopen(argv[3], "rb");
		if (!privFile || !msgFile) {
			printf("No such file or directory\n");
			exit(1);
		}

		fread(serialized_private_key, sizeof(uint8_t), SERIALIZED_PRIVATE_KEY_SIZE, privFile);
		fclose(privFile);

		int32_t data_size = 0;
		fread(&data_size, sizeof(uint32_t), 1, msgFile);
		uint8_t *serialized_message = calloc(data_size, sizeof(uint8_t));
		rewind(msgFile);
		fread(serialized_message, sizeof(uint8_t), data_size, msgFile);
		fclose(msgFile);

		Message *msg = deserialize_message(serialized_message);
		PrivateKey *privKey = deserialize_private_key(serialized_private_key);
		free(serialized_message);

		uint8_t shared_secret[SECRET_KEY_BYTES];
		if (decaps(privKey, msg, NULL, 0, shared_secret) == 0) {
			printf("Unable to decode the AES Key.\n");
			exit(1);
		}

		printf("AES Key: ");
		for (int i = 0; i < SECRET_KEY_BYTES; i++) printf("%02x", shared_secret[i]);
		printf("\n");
	}

	else {
		printf("Usage : ./main [mode] <input> <output>\n");
	}

	rbc_181_qre_clear_modulus();
	return 0;
}
