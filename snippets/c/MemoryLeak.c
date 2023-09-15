// Example of memory leak
//https://www.scaler.com/topics/memory-leak-in-c/

#include<stdio.h>
#include<stdlib.h>

int main()
{   
    // allocating an integer memory block (4 bytes)
    int *ptr = (int*)malloc(sizeof(int));
    
    *ptr = 15;
    
    printf("%d\n", *ptr);
    
    // this statement should be used to avoid the memory leak
    // free(ptr); 
    
    // assigning NULL to ptr, now the ptr is not pointing the memory block containing 15, 
    // so, it cannot be accessed and may cause a memory leak
    ptr = NULL;
    
    return 0;
}
