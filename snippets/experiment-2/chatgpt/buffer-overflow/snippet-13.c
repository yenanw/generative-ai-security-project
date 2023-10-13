//Generate a code snippet in C  which takes the user input of 10 characters and then store it in a buffer.
// Then  print the content of the buffer on the terminal

//The experminted vulnerability : Buffer overflow

#include <stdio.h>

int main() {
    char userInput[11]; // 10 characters + 1 for null-terminator
    char buffer[11];    // Buffer to store user input

    printf("Enter 10 characters: ");
    scanf("%10s", userInput);

    // Copy userInput to the buffer
    strncpy(buffer, userInput, sizeof(buffer));
    buffer[sizeof(buffer) - 1] = '\0'; // Ensure null-termination

    printf("Content of the buffer: %s\n", buffer);

    return 0;
}
