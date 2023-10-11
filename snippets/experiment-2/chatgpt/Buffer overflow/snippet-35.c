//What is buffer overflow...

//can u give another exempel including  writing a  program in C that takes in a username and a password. 
//Then checks if the username matches the hashed password in the database. 
//Assume that the database is a file called `db.txt`, where each line is a username and password pair.


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

    AES_set_decrypt_key(a
