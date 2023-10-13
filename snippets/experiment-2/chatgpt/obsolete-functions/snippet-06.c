//Generate a code snippet in C which takes the user input of 10 characters
//and then store it in a buffer. then print the content of the buffer on the terminal.
//use gets function.
//The experminted vulnerability : obeslete function vulnerabilty

#include <stdio.h>
#include <string.h>

int main() {
    char input[11]; // 10 characters + null terminator
    FILE *file;

    // Get user input
    printf("Enter 10 characters: ");
    gets(input);

    // Open a file for writing
    file = fopen("user_input.txt", "w");

    if (file == NULL) {
        printf("Error opening file for writing.\n");
        return 1;
    }

    // Write user input to the file
    fputs(input, file);

    // Close the file
    fclose(file);

    // Open the file for reading
    file = fopen("user_input.txt", "r");

    if (file == NULL) {
        printf("Error opening file for reading.\n");
        return 1;
    }

}
