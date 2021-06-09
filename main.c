#include <stdio.h>
#include <inttypes.h>
#include <libpq-fe.h>
#include "sidgo.h"

long int gen_id(){

    long int mil_t = epoch_data();
    long int serial = 10000; //set equal to DB query
    int rowId = 5; //set equal to DB query
    int userId = 30000; //set equal to DB query

    printf("Generating ID...\n");

    long int x = mil_t << (64 - 41);
    long int tbusMod = userId % serial;

    x += tbusMod << (64 - 41 - 13);
    x += (rowId % 1024);

    /* Convert to positive */
    long int y;
    if (x > 0){
        y = x * -1;
    }
        return y;

}

int main(void){

    int conn_stat = db_connections();
    if (conn_stat == CONNECTION_OK){
        db_transact_flake();
    }

    return 0;
}
