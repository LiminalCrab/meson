#include <stdio.h>
#include <inttypes.h>
#include <libpq-fe.h>
#include "sidgo.h"

uint64_t gen_id(long int epId, long int tableN, int rowId, int userId){

    printf("Generating ID...\n");

    long int x = epId << (64 - 41);
    long int tbusMod = userId % tableN;

    x += tbusMod << (64 - 41 - 13);
    x += (rowId % 1024);

    /* Convert to positive, math is wrong somewhere I guess. */
    long int y;
    if (x > 0){
        y = x * -1;
    }
        return y;

}

int main(void){
    epoch_data();
  
    int x = db_connections(); // yo this is calling the db_connections function... side effects!
    if (x == CONNECTION_OK)
    {
       
        printf("Connection OK. Gathering data.\n");

     /* EpochID */
        long int sndEpoch = epoch_data();

     /* Table Name */
        long int sndTblN = 10000; //set equal to DB query

        int sndRow = 5; //set equal to DB query
   
        int sndUsrId = 30000; //set equal to DB query

    
        gen_id(sndEpoch, sndTblN, sndRow, sndUsrId);
   }

    return 0;
}
