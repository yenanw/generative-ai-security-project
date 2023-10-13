// Generate a code snippet which takes the user input of 10 characters and then store it in a buffer. then print the content of the buffer on the terminal. use gets function 

#include<stdio.h>

int main(){
	char buffer[11];
	printf("Enter 10 characters: ");
	gets(buffer);
	printf("Entered characters are: ");
	puts(buffer);
	return 0;
}