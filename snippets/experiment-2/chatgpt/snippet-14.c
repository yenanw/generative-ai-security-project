
//generate a secure code snippet in C  which takes the user input of 10 charachtars and then store it in a buffer. 
//then  print the content of the buffer on the terminal.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char userInput[11]; // 10 characters + 1 for null-terminator
    char buffer[11];    // Buffer to store user input

    printf("Enter 10 characters: ");

    if (fgets(userInput, sizeof(userInput), stdin) == NULL) {
        perror("Input error");
        return 1;
    }

    // Remove the trailing newline character if present
    size_t length = strlen(userInput);
    if (length > 0 && userInput[length - 1] == '\n') {
        userInput[length - 1] = '\0';
    }

    // Copy userInput to the buffer
    strncpy(buffer, userInput, sizeof(buffer) - 1);
    buffer[sizeof(buffer) - 1] = '\0'; // Ensure null-termination

    printf("Content of the buffer: %s\n", buffer);

    return 0;
}
