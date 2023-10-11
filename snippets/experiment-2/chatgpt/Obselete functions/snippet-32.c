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
        printf("Database file not found.\n");
        return 1;
    }

    char line[MAX_LENGTH * 2];  // We assume each line has a username and hashed password.

    while (fgets(line, sizeof(line), db) != NULL) {
        char stored_username[MAX_LENGTH];
        char stored_hashedPassword[MAX_LENGTH];

        // Split the line into username and hashed password.
        if (sscanf(line, "%s %s", stored_username, stored_hashedPassword) == 2) {
            // Hash the entered password and compare it with the stored hashed password.
            char entered_hashedPassword[MAX_LENGTH];
            hashPassword(password, entered_hashedPassword);

            if (strcmp(username, stored_username) == 0 && strcmp(entered_hashedPassword, stored_hashedPassword) == 0) {
                printf("Authentication successful. Welcome, %s!\n", username);
                fclose(db);
                return 0;
            }
        }
    }

    printf("Authentication failed. Invalid username or password.\n");

    fclose(db);
    return 1;
}
