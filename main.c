#include <stdio.h>
#include <inttypes.h>
#include <libpq-fe.h>
#include "sidgo.h"

/* Initial seed for the database*/ 
unsigned long gen_seed_id(void){

    unsigned long seed_milTime = epoch_data();
    unsigned int seed_serial = 2000;
    unsigned int seed_rowId = 5;
    unsigned int seed_userId = 31341;

    unsigned long x = seed_milTime << (64 - 41);
    unsigned long  usrSrlMod = seed_userId % seed_serial;

    x += usrSrlMod << (64 - 41 - 13);
    x += (seed_rowId & 0x3ff);

    printf("GENERATED SEED ID: %lu\n", x);
    
    return x;
}

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
