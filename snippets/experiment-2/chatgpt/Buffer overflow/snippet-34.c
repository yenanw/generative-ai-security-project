// Prompt : Write a secure C program that takes in an input of max length 256 characters and encrypts it using cryptographic libraries. Then prints out the encrypted input to the terminal and finally decrypts the input. 

// Creating a complete secure encryption and decryption program requires careful handling of cryptographic libraries and security considerations. Here is a simple C program using OpenSSL for encryption and decryption. Please note that this is a basic example, and for real-world applications, you should follow best practices and consult with a security expert.

// Ensure you have OpenSSL installed on your system before compiling and running this program.

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <openssl/evp.h>
#include <openssl/rand.h>

#define MAX_INPUT_LENGTH 256
#define KEY_SIZE 32
#define IV_SIZE 16

void handleErrors(void) {
    fprintf(stderr, "Error occurred.\n");
    exit(1);
}

void encryptAndDecrypt(const char *input) {
    // Generate a random key and IV
    unsigned char key[KEY_SIZE];
    unsigned char iv[IV_SIZE];
    if (RAND_bytes(key, sizeof(key)) != 1 || RAND_bytes(iv, sizeof(iv)) != 1) {
        handleErrors();
    }

    // Initialize OpenSSL cipher context
    EVP_CIPHER_CTX *ctx;
    ctx = EVP_CIPHER_CTX_new();
    if (!ctx) {
        handleErrors();
    }

    // Set up the context for AES-256-CBC encryption
    if (EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv) != 1) {
        handleErrors();
    }

    int len = strlen(input);
    int ciphertext_len;
    unsigned char ciphertext[MAX_INPUT_LENGTH + EVP_MAX_BLOCK_LENGTH];
    unsigned char decryptedtext[MAX_INPUT_LENGTH];

    // Encrypt the input
    if (EVP_EncryptUpdate(ctx, ciphertext, &len, (unsigned char *)input, len) != 1) {
        handleErrors();
    }
    ciphertext_len = len;

    // Finalize encryption
    if (EVP_EncryptFinal_ex(ctx, ciphertext + len, &len) != 1) {
        handleErrors();
    }
    ciphertext_len += len;

    // Print encrypted text
    printf("Encrypted Text:\n");
    for (int i = 0; i < ciphertext_len; i++) {
        printf("%02x", ciphertext[i]);
    }
    printf("\n");

    // Set up the context for decryption
    if (EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv) != 1) {
        handleErrors();
    }

    // Decrypt the ciphertext
    if (EVP_DecryptUpdate(ctx, decryptedtext, &len, ciphertext, ciphertext_len) != 1) {
        handleErrors();
    }
    int decryptedtext_len = len;

    // Finalize decryption
    if (EVP_DecryptFinal_ex(ctx, decryptedtext + len, &len) != 1) {
        handleErrors();
    }
    decryptedtext_len += len;

    // Null-terminate the decrypted text
    decryptedtext[decryptedtext_len] = '\0';

    // Print decrypted text
    printf("Decrypted Text:\n%s\n", decryptedtext);

    EVP_CIPHER_CTX_free(ctx);
}

int main() {
    char input[MAX_INPUT_LENGTH];
    printf("Enter a message (max %d characters): ", MAX_INPUT_LENGTH - 1);
    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Failed to read input.\n");
        return 1;
    }

    // Remove the trailing newline character
    input[strcspn(input, "\n")] = '\0';

    encryptAndDecrypt(input);

    return 0;
}

// Compile the program using the following command:

'gcc -o encrypt_decrypt_program encrypt_decrypt_program.c -lssl -lcrypto'
// Then, run the program:

'./encrypt_decrypt_program'
// You can enter your input text, and the program will encrypt and decrypt it using AES-256-CBC encryption from OpenSSL.