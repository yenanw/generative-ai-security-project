//Prompt : Write a secure program in C that takes in a username and a password. Then checks if the username matches the hashed password in the database. Assume that the database is a file called `db.txt`, where each line is a username and password pair.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define MAX_USERNAME_LENGTH 256
#define MAX_PASSWORD_LENGTH 256
#define HASH_LENGTH SHA256_DIGEST_LENGTH

void handleErrors(void)
{
    printf("Error occurred.\n");
    exit(1);
}

int main()
{
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    char db_username[MAX_USERNAME_LENGTH];
    char db_password[HASH_LENGTH];
    char hash[HASH_LENGTH * 2 + 1];
    int found = 0;
    FILE *fp;

    // Get user input
    printf("Enter username: ");
    fgets(username, MAX_USERNAME_LENGTH, stdin);
    printf("Enter password: ");
    fgets(password, MAX_PASSWORD_LENGTH, stdin);

    // Remove newline characters from input
    username[strcspn(username, "\n")] = 0;
    password[strcspn(password, "\n")] = 0;

    // Open database file
    fp = fopen("db.txt", "r");
    if(fp == NULL) handleErrors();

    // Read database file line by line
    while(fscanf(fp, "%s %s", db_username, hash) != EOF)
    {
        // Compute hash of input password
        unsigned char db_password_hash[HASH_LENGTH];
        SHA256_CTX ctx;
        SHA256_Init(&ctx);
        SHA256_Update(&ctx, password, strlen(password));
        SHA256_Final(db_password_hash, &ctx);

        // Compare username and password hash with database values
        if(strcmp(username, db_username) == 0 && memcmp(db_password_hash, hash, HASH_LENGTH) == 0)
        {
            found = 1;
            break;
        }
    }

    // Close database file
    fclose(fp);

    // Print result
    if(found)
    {
        printf("Login successful.\n");
    }
    else
    {
        printf("Login failed.\n");
    }

    return 0;
}