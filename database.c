#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <libpq-fe.h>
#include "sidgo.h"

/* Disconnect */ 

void db_disconnect(PGconn *conn, PGresult *res){
    printf("Disconnecting from Database.");
    PQclear(res);
    PQfinish(conn);    
    
    exit(1);
}

int db_table_exist(void){
    PGconn *conn;
    conn = PQconnectdb("");
    PGresult *res;

    /* Buffering SQL commands */
    char buffer[512];
    unsigned long tAccount = snprintf(buffer, sizeof(buffer), "CREATE TABLE IF NOT EXISTS sid"\
                                                            "(id BIGSERIAL, flake NUMERIC, serial BIGINT);");


    printf("Running accountability for primary table.\n");

    if (tAccount > sizeof(buffer)) {
        printf("Error, buffer too small.");
    }

    res = PQexec(conn, buffer);

    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        printf("Table accountability failed.\n");
        printf("%s\n", PQresultErrorMessage(res));
        printf("%s\n", PQerrorMessage(conn));
        
        PQclear(res);
        db_disconnect(conn, res);
    }

    PQclear(res);
    PQfinish(conn);

    return 0;
}

/* Initial seed */ 
int db_init_seed(void){
   // PGconn *conn;
  //  conn = PQconnectdb("");
    
    unsigned long seedFlake = gen_id();
    printf("%lu", seedFlake);


    return 0;
}

/* Snowflake ID transaction */ 

int db_transact_flake(void){
    PGconn *conn;
    conn = PQconnectdb("");

    char buffer[512];
    unsigned long flakeid = gen_id();
    PGresult *res;

    
    unsigned long tFlake = snprintf(buffer, sizeof(buffer), "INSERT INTO sid (flake, serial) VALUES (%lu, %d)", flakeid, 2000);


    if (tFlake > sizeof(buffer)) {
        printf("Error, buffer too small.");
    }

    res = PQexec(conn, buffer);

    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        printf("INSERT command failed\n");
        printf("%s\n", PQresultErrorMessage(res));
        printf("%s\n", PQerrorMessage(conn));
        
        PQclear(res);
        db_disconnect(conn, res);
    }


    PQclear(res);
    PQfinish(conn);
    
    return 0;
}

/* Database connection status functions. */ 
int db_connections(void){
    PGconn *conn;
    conn = PQconnectdb("");

    switch(PQstatus(conn)){

        case CONNECTION_STARTED:
            printf("Waiting for connection to be made.\n");
            break;

        case CONNECTION_OK:
            printf("Connect OK.\n");
            break;

        case CONNECTION_BAD:
            printf("Connection failed.\n");
            PQerrorMessage(conn);
            PQfinish(conn);
            exit(1);
            break;

        case CONNECTION_NEEDED:
            printf("Internal state: connect() needed.\n");
            break;

        case CONNECTION_CHECK_WRITABLE:
            printf("Checking if session is read-write.\n");
            break;

        case CONNECTION_CONSUME:
            printf("Consuming any extra messages.\n");
            break;

        case CONNECTION_GSS_STARTUP:
            printf("Negotiating GSSAPI.\n");
            break;

        case CONNECTION_CHECK_TARGET:
            printf("Checking target server properties.\n");
            break;

        case CONNECTION_MADE:
            printf("Connection OK; waiting to send.\n");
            break;

        case CONNECTION_AWAITING_RESPONSE:
            printf("Waiting for a response from the server.\n");
            break;

        case CONNECTION_AUTH_OK:
            printf("Received authentication; waiting for backend start-up to finish.\n");
            break;

        case CONNECTION_SSL_STARTUP:
            printf("Negotiating SSL encryption.\n");
            break;

        case CONNECTION_SETENV:
            printf("Negotiating environment-driven parameter settings.\n");
            break;
    }

    return 0;
}
