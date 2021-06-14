#include <stdio.h>
#include <inttypes.h>
#include <libpq-fe.h>
#include "sidgo.h"


/* Generate ID */ 
unsigned long gen_id(void){

    unsigned long milTime = epoch_data();
    unsigned int serial = 2000;
    unsigned int rowId = 5;
    unsigned int userId = 31341;

    unsigned long x = milTime << (64 - 41);
    unsigned long  usrSrlMod = userId % serial;

    x += usrSrlMod << (64 - 41 - 13);
    x += (rowId & 0x3ff);

    printf("GENERATED ID: %lu\n", x);
    
    return x;
}

int main(void){

    int conn_stat = db_connections();
    if (conn_stat == CONNECTION_OK){
        db_transact_flake();
    }

    return 0;
}
