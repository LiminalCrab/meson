#include <stdio.h>
#include <inttypes.h>
#include <libpq-fe.h>
#include "sidgo.h"

int generate_id(long int epId, long int tableN, int rowId, int userId){

    printf("Generating ID.");

    long int x = epId << 41;
    long int tbusMod = userId % tableN;

    x += tbusMod << (64 - 41 - 13);
    x += (rowId % 1024);

    return 0;
}

int main(void){
    epoch_data();
  
    int x = db_connections();
    if (x == CONNECTION_OK)
    {
       
        printf("Connection OK. Gathering data.\n");

     /* EpochID */
        long int sndEpoch = epoch_data();

     /* Table Name */
        long int sndTblN = 10000; //set equal to DB query

        int sndRow = 5; //set equal to DB query
   
        int sndUsrId = 30000; //set equal to DB query

    
        generate_id(sndEpoch, sndTblN, sndRow, sndUsrId);
   }

    return 0;
}
