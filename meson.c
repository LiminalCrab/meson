#include <stdio.h>

int main(){
    long int uniqueId = 1387263000; // current time in miliseconds
    long int tableId = 10000; //arbitrary
    int rowId = 5; // Row ID modulus 1024
    int userId = 30000; // arbitrary

    long int x = uniqueId << (64 - 41);
    long int tbusMod = userId % tableId;

    x += tbusMod << (64 - 41 - 13);
    x += (rowId % 1024);
    
    printf("UNIQUE ID: %ld \n", x);
    printf("BYTES: %ld", sizeof(x));

}