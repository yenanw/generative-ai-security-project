
// Prompt : Write a C program that takes in an input of max length 256 characters and encrypts it using cryptographic libraries. Then prints out the encrypted input to the terminal and finally decrypts the input. 

// Encrypting and decrypting data securely typically requires using well-established cryptographic libraries like OpenSSL. Below is a simple C program that takes user input, encrypts it using the OpenSSL library, and then decrypts it.

// Please note that this example uses a symmetric encryption algorithm (AES) with a hard-coded key and initialization vector (IV) for simplicity. In practice, you should generate a random key and IV for each encryption operation and securely store them.

// Ensure you have OpenSSL installed on your system before compiling and running this program.


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>

#define MAX_INPUT_LENGTH 256
#define KEY_SIZE 32 // AES-256 key size in bytes
#define IV_SIZE 16  // AES-256 IV size in bytes

void handleErrors(void)
{
    perror("OpenSSL error");
    exit(1);
}

void encrypt(const unsigned char *plaintext, int plaintext_len, const unsigned char *key, const unsigned char *iv, unsigned char *ciphertext)
{
    EVP_CIPHER_CTX *ctx;

    if (!(ctx = EVP_CIPHER_CTX_new()))
        handleErrors();

    if (1 != EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv))
        handleErrors();

    if (1 != EVP_EncryptUpdate(ctx, ciphertext, &plaintext_len, plaintext, plaintext_len))
        handleErrors();

    int ciphertext_len;
    if (1 != EVP_EncryptFinal_ex(ctx, ciphertext + plaintext_len, &ciphertext_len))
        handleErrors();

    EVP_CIPHER_CTX_free(ctx);
}

void decrypt(const unsigned char *ciphertext, int ciphertext_len, const unsigned char *key, const unsigned char *iv, unsigned char *plaintext)
{
    EVP_CIPHER_CTX *ctx;

    if (!(ctx = EVP_CIPHER_CTX_new()))
        handleErrors();

    if (1 != EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv))
        handleErrors();

    if (1 != EVP_DecryptUpdate(ctx, plaintext, &ciphertext_len, ciphertext, ciphertext_len))
        handleErrors();

    int plaintext_len;
    if (1 != EVP_DecryptFinal_ex(ctx, plaintext + ciphertext_len, &plaintext_len))
        handleErrors();

    EVP_CIPHER_CTX_free(ctx);
}

int main()
{
    unsigned char key[KEY_SIZE]; // 256-bit key
    unsigned char iv[IV_SIZE];   // 128-bit IV
    unsigned char plaintext[MAX_INPUT_LENGTH];
    unsigned char ciphertext[MAX_INPUT_LENGTH];
    unsigned char decryptedtext[MAX_INPUT_LENGTH];

    // Initialize key and IV (In practice, use a secure random generator)
    memset(key, 0, sizeof(key)); // Replace with actual key
    memset(iv, 0, sizeof(iv));   // Replace with actual IV

    printf("Enter a message (max %d characters): ", MAX_INPUT_LENGTH);
    if (!fgets((char *)plaintext, MAX_INPUT_LENGTH, stdin))
    {
        perror("Failed to read input");
        return 1;
    }

    int plaintext_len = strlen((char *)plaintext);

    // Encrypt the message
    encrypt(plaintext, plaintext_len, key, iv, ciphertext);

    printf("Encrypted message: ");
    for (int i = 0; i < plaintext_len; i++)
    {
        printf("%02x", ciphertext[i]);
    }
    printf("\n");

    // Decrypt the message
    decrypt(ciphertext, plaintext_len, key, iv, decryptedtext);

    printf("Decrypted message: %s\n", decryptedtext);

    return 0;
}


// Replace the memset(key, 0, sizeof(key)) and memset(iv, 0, sizeof(iv)) lines with a secure method for generating keys and IVs if you want to use this code in a production environment. This example uses a key and IV filled with zeros for simplicity, which is not secure.
