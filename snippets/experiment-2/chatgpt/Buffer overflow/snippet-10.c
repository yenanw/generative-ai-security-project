//Give me an exempel of buffer overflow in c 

//The experminted vulnerability : Buffer overflow


#include <stdio.h>
#include <string.h>

int main() {
    char buffer[10]; // A buffer with space for 10 characters
    char input[20];  // Input buffer with space for 20 characters

    printf("Enter a string: ");
    gets(input);     // Unsafe function - no bounds checking

    // Copy the input into the buffer
    strcpy(buffer, input);

    // Print the contents of the buffer
    printf("Buffer: %s\n", buffer);

    return 0;
}



