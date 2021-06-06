#include <stdio.h>
#include <libpq-fe.h>
#include "sidgo.h"

int generate_id(long int *uniqueId, long int *tableN, int *rowId, int *userId){



    long int getUID = *uniqueId; // miliseconds, epoch from specific point in time.
    long int getTblN = *tableN; // tablename 
    int getRowId = *rowId; // Row ID modulus 1024
    int getUsrId = *userId; 

    long int x = getUID << (64 - 41);
    long int tbusMod = getUsrId % getTblN;

    x += tbusMod << (64 - 41 - 13);
    x += (getRowId % 1024);

    printf("UNIQUE ID: %ld \n", x);
    printf("BYTES: %ld", sizeof(x));

    return 0;
}

int query(void){


}

int main(void){
   int x = db_connections();
   if (x == CONNECTION_OK)
   {

    printf("Continuing...\n");

   }
   printf("%d", x);
    return 0;
}