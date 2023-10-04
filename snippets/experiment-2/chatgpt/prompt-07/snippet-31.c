// Prompt : Write a secure program in C that takes in a username and a password. Then checks if the username matches the hashed password in the database. Assume that the database is a file called `db.txt`, where each line is a username and password pair.


// To create a secure C program that takes a username and password, checks if the username matches the hashed password in the database (db.txt), and handles hashing securely, you can use the following code as a starting point. Please note that this is a simplified example for educational purposes, and in a real-world application, you would need to consider additional security measures, such as using a more secure hashing algorithm and error handling.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <openssl/sha.h> // You'll need OpenSSL for hashing

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 64 // Assuming hashed password is 64 characters long

// Function to compute the SHA-256 hash of a string
void compute_sha256_hash(const char *input, char *output) {
    SHA256_CTX context;
    SHA256_Init(&context);
    SHA256_Update(&context, input, strlen(input));
    SHA256_Final((unsigned char *)output, &context);
}

int main() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    char input_password[MAX_PASSWORD_LENGTH];

    // Input username and password
    printf("Enter username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = '\0'; // Remove newline character

    printf("Enter password: ");
    fgets(input_password, sizeof(input_password), stdin);
    input_password[strcspn(input_password, "\n")] = '\0'; // Remove newline character

    // Compute the hash of the input password
    char hashed_input_password[MAX_PASSWORD_LENGTH];
    compute_sha256_hash(input_password, hashed_input_password);

    // Open the database file
    FILE *db_file = fopen("db.txt", "r");
    if (db_file == NULL) {
        perror("Error opening database file");
        return 1;
    }

    bool found = false;
    char line[MAX_USERNAME_LENGTH + MAX_PASSWORD_LENGTH + 2]; // +2 for potential newline and null terminator

    // Read lines from the database file
    while (fgets(line, sizeof(line), db_file) != NULL) {
        line[strcspn(line, "\n")] = '\0'; // Remove newline character

        // Extract username and hashed password from the line
        char *saved_username = strtok(line, " ");
        char *saved_hashed_password = strtok(NULL, " ");

        // Compare the username and the hashed password
        if (saved_username != NULL && saved_hashed_password != NULL) {
            if (strcmp(username, saved_username) == 0 && strcmp(hashed_input_password, saved_hashed_password) == 0) {
                found = true;
                break;
            }
        }
    }

    // Close the database file
    fclose(db_file);

    // Check if the username and password were found in the database
    if (found) {
        printf("Login successful!\n");
    } else {
        printf("Login failed. Invalid username or password.\n");
    }

    return 0;
}


//In this code:

// We use the SHA-256 algorithm from OpenSSL to securely hash the user's input password.
// We read the database file line by line, parsing each line into a username and a hashed password.
// We compare the input username and the hashed input password with the entries in the database to determine if the login is successful.
// Remember to link your program with OpenSSL when compiling:


'gcc -o secure_login secure_login.c -lcrypto'
// This code provides a basic example of username and password verification with password hashing. In practice, you should also consider security best practices such as salting your hashes and using a stronger password hashing algorithm like bcrypt or Argon2. Additionally, error handling and memory management should be further improved for production use.