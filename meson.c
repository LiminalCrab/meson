#include <stdio.h>

int main(){
    // All of these variables have arbitrary values, temporary example
    long int uniqueId = 1387263000; // miliseconds
    long int tableId = 10000; 
    int rowId = 5; // Row ID modulus 1024
    int userId = 30000; 

    long int x = uniqueId << (64 - 41);
    long int tbusMod = userId % tableId;

    x += tbusMod << (64 - 41 - 13);
    x += (rowId % 1024);

    printf("UNIQUE ID: %ld \n", x);
    printf("BYTES: %ld", sizeof(x));

}