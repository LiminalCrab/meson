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
    epoch_data();
  
//    int x = db_connections();
//    if (x == CONNECTION_OK)
//    {
//     printf("gathering data.\n");

//     /* EpochID */
//     long int sndEpoch = gen_epoch();
//     long int *lxEpoch = &sndEpoch;

//     printf("TIME: %ld\n", *lxEpoch);

//     /* Table Name */
//     long int sndTblN = 10000; //set equal to DB query
//     long int *lxTblN = &sndTblN;

//     printf("TABLE ID: %ld\n", *lxTblN);

//     /* Row ID */
//         int sndRow = 5; //set equal to DB query
//         int *lxRowId = &sndRow;
//         printf("ROW ID: %d\n", *lxRowId);

//     /* USER ID */
//         int sndUsrId = 30000; //set equal to DB query
//         int *lxUsrId = &sndUsrId;
//         printf("USER ID: %d\n", *lxUsrId);


//     //generate_id(lxEpoch, lxTblN, lxRowId, lxUsrId);
//    }

//    printf("%d", x);
    return 0;
}