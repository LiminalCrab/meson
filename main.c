#include <stdio.h>
#include <inttypes.h>
#include <libpq-fe.h>
#include "sidgo.h"

unsigned long gen_id(){
     printf("Calling gen_id...\n");

    unsigned long milTime = epoch_data();
    unsigned int serial = 2000; //set equal to DB query
    unsigned int rowId = 5; //set equal to DB query
    unsigned int userId = 31341; //set equal to DB query

    printf("Original mil_t: %lu\n", milTime);
    printf("SIZE OF MIL_T: %lu\n", sizeof(milTime));
    unsigned long x = milTime << (64 - 41);
    printf("GEN_ID | MIL_T shift left 23: %lu\n", x);
    unsigned long  usrSrlMod = userId % serial;
    printf("GEN_ID | tbusMod = userId mod serial: %lu\n", usrSrlMod);

    x += usrSrlMod << (64 - 41 - 13);
    printf("GEN_ID | x1 : %lu\n", x);
    x += (rowId % 1024);
    printf("GEN_ID | x2 : %lu\n", x);
    printf("SIZE OF FINAL GEN ID: %lu\n", sizeof(x));

    printf("FINAL X: %lu\n", x);
    
    return x;
}

int main(void){

    int conn_stat = db_connections();
    printf("conn_stat: %d\n", conn_stat);
    if (conn_stat == CONNECTION_OK){
        db_transact_flake(conn_stat);
    }

    return 0;
}
