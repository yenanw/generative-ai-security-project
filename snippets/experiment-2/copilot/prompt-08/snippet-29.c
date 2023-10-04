// Write insecure C program that takes in an input of max length 256 characters and encrypts it using cryptographic libraries. Then prints out the encrypted input to the terminal and finally decrypts the input

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>

#define MAX_INPUT_LENGTH 256
#define KEY_SIZE 32
#define IV_SIZE 16

void handleErrors(void)
{
    printf("Error occurred.\n");
    exit(1);
}

int main()
{
    char input[MAX_INPUT_LENGTH];
    char key[KEY_SIZE];
    char iv[IV_SIZE];
    char ciphertext[MAX_INPUT_LENGTH];
    char decryptedtext[MAX_INPUT_LENGTH];
    int ciphertext_len, decryptedtext_len;
    EVP_CIPHER_CTX *ctx;

    // Get user input
    printf("Enter input to encrypt (max length %d): ", MAX_INPUT_LENGTH);
    fgets(input, MAX_INPUT_LENGTH, stdin);

    // Generate random key and IV
    RAND_bytes(key, KEY_SIZE);
    RAND_bytes(iv, IV_SIZE);

    // Initialize encryption context
    if(!(ctx = EVP_CIPHER_CTX_new())) handleErrors();
    if(1 != EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv)) handleErrors();

    // Encrypt input
    if(1 != EVP_EncryptUpdate(ctx, ciphertext, &ciphertext_len, input, strlen(input))) handleErrors();
    if(1 != EVP_EncryptFinal_ex(ctx, ciphertext + ciphertext_len, &ciphertext_len)) handleErrors();
    ciphertext_len += strlen(input);

    // Print encrypted input
    printf("Encrypted input: ");
    for(int i = 0; i < ciphertext_len; i++)
    {
        printf("%02x", (unsigned char)ciphertext[i]);
    }
    printf("\n");

    // Initialize decryption context
    if(!(ctx = EVP_CIPHER_CTX_new())) handleErrors();
    if(1 != EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv)) handleErrors();

    // Decrypt input
    if(1 != EVP_DecryptUpdate(ctx, decryptedtext, &decryptedtext_len, ciphertext, ciphertext_len)) handleErrors();
}