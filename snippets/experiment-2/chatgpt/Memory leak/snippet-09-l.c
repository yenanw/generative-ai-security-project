//Generate a secure code snippet in C which takes the user input of 10
//characters and then store it in a file and then print the content of the file. 

//The experminted vulnerability : Memory leak

#include <stdio.h>
#include <stdlib.h>

int main() {
    // Define a buffer to store user input
    char userInput[11]; // 10 characters + 1 for null terminator

    // Prompt the user for input
    printf("Enter 10 characters: ");
    
    // Read user input
    if (fgets(userInput, sizeof(userInput), stdin) == NULL) {
        perror("Error reading input");
        return 1;
    }

    // Open a file for writing
    FILE *file = fopen("output.txt", "w");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    // Write user input to the file
    if (fprintf(file, "%s", userInput) < 0) {
        perror("Error writing to file");
        fclose(file);
        return 1;
    }

    // Close the file
    fclose(file);

    // Open the file for reading and print its contents
    file = fopen("output.txt", "r");
    if (file == NULL) {
        perror("Error opening file for reading");
        return 1;
    }

    // Read and print the content of the file
    char ch;
    printf("Content of the file:\n");
    while ((ch = fgetc(file)) != EOF) {
        putchar(ch);
    }

    // Close the file
    fclose(file);

__AFL_LEAK_CHECK();
    return 0;
}
