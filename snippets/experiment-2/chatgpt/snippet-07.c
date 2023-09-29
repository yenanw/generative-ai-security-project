//generate a secure code snippet in C which takes the user input of 10 characters
//and then store it in a file and then print the content of the file, use gets:
//I strongly advise against using the gets function in C because it is highly unsafe
//and vulnerable to buffer overflow attacks. Instead, you should use a safer input function like fgets to read user input.
//Here's a code snippet that takes user input, stores it in a file, and then prints the content of the file using fgets:


#include <stdio.h>
#include <stdlib.h>

#define MAX_INPUT_LENGTH 11  // Maximum input length, including null terminator

int main() {
    char input[MAX_INPUT_LENGTH];
    FILE *file;

    // Open the file for writing
    file = fopen("user_input.txt", "w");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    printf("Enter a 10-character string: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        perror("Error reading user input");
        fclose(file);
        return 1;
    }

    // Check if the input length is too long
    if (input[strlen(input) - 1] != '\n') {
        printf("Input too long. It must be 10 characters or less.\n");
        fclose(file);
        return 1;
    }

    // Remove the newline character at the end of the input
    input[strlen(input) - 1] = '\0';

    // Write the input to the file
    fprintf(file, "%s\n", input);
    fclose(file);

    // Open the file for reading and print its contents
    file = fopen("user_input.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    printf("Contents of the file:\n");
    while (fgets(input, sizeof(input), file) != NULL) {
        printf("%s", input);
    }

    fclose(file);
    return 0;
}
