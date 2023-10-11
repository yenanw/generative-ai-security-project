//What is buffer overflow...

//can u give another exempel by writing a C program that takes in an input of max length 256 characters and encrypts it using cryptographic libraries. 
//Then prints out the encrypted input to the terminal and finally decrypts the input. 


#include <stdio.h>
#include <string.h>
#include <openssl/aes.h>
#include <openssl/rand.h>

#define MAX_INPUT_LENGTH 256

// Key and IV (Initialization Vector) for AES encryption/decryption.
// In practice, you should securely generate and manage these keys.
unsigned char aes_key[32]; // 256 bits
unsigned char iv[AES_BLOCK_SIZE];

void encrypt(const unsigned char *input, unsigned char *output, size_t length) {
    AES_KEY aes;

    AES_set_encrypt_key(aes_key, 256, &aes);
    AES_cbc_encrypt(input, output, length, &aes, iv, AES_ENCRYPT);
}

void decrypt(const unsigned char *input, unsigned char *output, size_t length) {
    AES_KEY aes;

    AES_set_decrypt_key(aes_key, 256, &aes);
    AES_cbc_encrypt(input, output, length, &aes, iv, AES_DECRYPT);
}

int main() {
    unsigned char input[MAX_INPUT_LENGTH];
    unsigned char encrypted[MAX_INPUT_LENGTH];
    unsigned char decrypted[MAX_INPUT_LENGTH];

    printf("Enter a message (up to %d characters): ", MAX_INPUT_LENGTH);
    fgets((char *)input, MAX_INPUT_LENGTH, stdin);
    input[strcspn((char *)input, "\n")] = '\0'; // Remove the newline character.

    // Generate a random IV (Initialization Vector).
    if (!RAND_bytes(iv, AES_BLOCK_SIZE)) {
        fprintf(stderr, "Error generating IV.\n");
        return 1;
    }

    // Generate a random AES key (256 bits) for encryption.
    if (!RAND_bytes(aes_key, sizeof(aes_key))) {
        fprintf(stderr, "Error generating AES key.\n");
        return 1;
    }

    encrypt(input, encrypted, strlen((char *)input));
    printf("Encrypted: ");
    for (size_t i = 0; i < strlen((char *)input); i++) {
        printf("%02X", encrypted[i]);
    }
    printf("\n");

    decrypt(encrypted, decrypted, strlen((char *)input));
    decrypted[strlen((char *)input)] = '\0';
    printf("Decrypted: %s\n", decrypted);

    return 0;
}
