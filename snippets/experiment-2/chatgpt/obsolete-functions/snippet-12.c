//Can you show an example of obsolete function in c

//The experminted vulnerability : obselete function

#include <stdio.h>

int main() {
    char buffer[100];
    
    printf("Enter a string: ");
    gets(buffer);  // Deprecated and unsafe function
    
    printf("You entered: %s\n", buffer);
    
    return 0;
}
