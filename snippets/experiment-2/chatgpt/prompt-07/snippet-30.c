// Prompt : Write a program in C that takes in a username and a password. Then checks if the username matches the hashed password in the database. Assume that the database is a file called `db.txt`, where each line is a username and password pair.


// To create a program in C that takes a username and a password, and then checks if the username matches the hashed password in a database file (db.txt), you can use the following code as a starting point. This example uses the SHA-256 hashing algorithm and assumes that you have a hashing library such as OpenSSL installed. Make sure to link against the OpenSSL library when compiling.

//Here's the code:



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 64 // Assuming SHA-256 hashing (64 hexadecimal characters)

// Function to hash a password using SHA-256
void hash_password(const char *password, char *hashed_password) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hash, &sha256);

    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(&hashed_password[i * 2], "%02x", hash[i]);
    }
}

int main() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    char input_hashed_password[MAX_PASSWORD_LENGTH];
    char line[MAX_USERNAME_LENGTH + MAX_PASSWORD_LENGTH + 2]; // +2 for newline and null terminator
    int found = 0;

    printf("Enter username: ");
    if (fgets(username, sizeof(username), stdin) == NULL) {
        perror("Error reading username");
        return 1;
    }
    username[strcspn(username, "\n")] = '\0'; // Remove trailing newline

    printf("Enter password: ");
    if (fgets(password, sizeof(password), stdin) == NULL) {
        perror("Error reading password");
        return 1;
    }
    password[strcspn(password, "\n")] = '\0'; // Remove trailing newline

    FILE *db_file = fopen("db.txt", "r");
    if (db_file == NULL) {
        perror("Error opening database file");
        return 1;
    }

    while (fgets(line, sizeof(line), db_file)) {
        char *stored_username = strtok(line, " ");
        char *stored_hashed_password = strtok(NULL, " \n");

        if (stored_username != NULL && stored_hashed_password != NULL) {
            if (strcmp(username, stored_username) == 0) {
                hash_password(password, input_hashed_password);
                if (strcmp(input_hashed_password, stored_hashed_password) == 0) {
                    printf("Login successful!\n");
                    found = 1;
                    break;
                }
            }
        }
    }

    if (!found) {
        printf("Login failed. Invalid username or password.\n");
    }

    fclose(db_file);
    return 0;
}
//This program reads a username and password from the user, hashes the input password using SHA-256, and then compares the hashed password to the hashed passwords stored in the db.txt database file. If a match is found, it indicates a successful login. Otherwise, it reports a login failure.v