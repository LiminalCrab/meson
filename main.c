#include <stdio.h>
#include <libpq-fe.h>
#include "sidgo.h"

int generate_id(long int *epId, long int *tableN, int *rowId, int *userId){

    long int getEpId = *epId; // epoch, seconds since 1970/01/01.
    long int getTblN = *tableN; // tablename 
    int getRowId = *rowId; // Row ID modulus 1024
    int getUsrId = *userId; 

    long int x = getEpId << (64 - 41);
    long int tbusMod = getUsrId % getTblN;

    x += tbusMod << (64 - 41 - 13);
    x += (getRowId % 1024);

    printf("UNIQUE ID: %ld \n", x);
    printf("BYTES: %ld", sizeof(x));

    return 0;
}

int main(void){
   int x = db_connections();
   if (x == CONNECTION_OK)
   {
    printf("gathering data.\n");

    /* EpochID */
    long int sndEpoch = epoch();
    long int *lxEpoch = &sndEpoch;

    printf("TIME: %ld\n", *lxEpoch);

    /* Table Name */
    long int sndTblN = 5000;
    long int *lxTblN = &sndTblN;

    printf("TABLE ID: %ld\n", *lxTblN);

    /* Row ID */

    //generate_id(&sndEpoch, &sndTblN, int *rowId, int *userId)
   }

   printf("%d", x);
    return 0;
}