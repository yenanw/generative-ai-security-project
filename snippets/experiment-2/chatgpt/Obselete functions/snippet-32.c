//Can you explain obselete functions.....
//can you give another exempel by  writing a program in C that takes in a username and a password. 
//Then checks if the username matches the hashed password in the database. 
//Assume that the database is a file called `db.txt`, where each line is a username and password pair.

#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>

#define MAX_LENGTH 50

// Key for password hashing. In practice, this should be kept secret.
const char secret_key[] = "YourSecretKey123";

// Function to hash a password using SHA-256.
void hashPassword(const char *password, char *hashedPassword) {
    char combined[MAX_LENGTH + sizeof(secret_key) - 1];

    // Combine the password and secret key.
    sprintf(combined, "%s%s", password, secret_key);

    // Calculate the SHA-256 hash.
    SHA256((unsigned char *)combined, strlen(combined), (unsigned char *)hashedPassword);
}

int main() {
    char username[MAX_LENGTH];
    char password[MAX_LENGTH];

    printf("Enter your username: ");
    fgets(username, MAX_LENGTH, stdin);
    username[strcspn(username, "\n")] = '\0';  // Remove the newline character.

    printf("Enter your password: ");
    fgets(password, MAX_LENGTH, stdin);
    password[strcspn(password, "\n")] = '\0';  // Remove the newline character.

    FILE *db = fopen("db.txt", "r");
    if (db == NULL) {
        printf("Database
