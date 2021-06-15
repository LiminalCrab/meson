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

/* Get latest row id from db */
int db_row_id(void){
    PGconn *conn;
    conn = PQconnectdb("");
    PGresult *res;

    int retRowId;
    res = PQexec(conn, "SELECT MAX(id) FROM sid");

    if (PQresultStatus(res) != PGRES_TUPLES_OK) {

        printf("No data retrieved\n");        
        PQclear(res);
        db_disconnect(conn, res);
    }

    retRowId = atoi(PQgetvalue(res,0,0));
    printf("ROW ID: %d", retRowId);

    PQclear(res);
    PQfinish(conn);

    return retRowId;
}

/* Checks if the sid table in the database exists, if it doesn't, it create it.*/

int db_table_exist(void){
    PGconn *conn;
    conn = PQconnectdb("");
    PGresult *res;

    /* Buffering SQL commands */
    char buffer[128];
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

    printf("Continuing.\n");
    return 0;
}

/* seed transaction */ 

int db_init_seed(void){
    PGconn *conn;
    conn = PQconnectdb("");

    char buffer[128];
    unsigned long seedFlakeId = gen_seed_id();
    PGresult *res;

    unsigned long sFlake = snprintf(buffer, sizeof(buffer), "INSERT INTO sid (flake, serial) VALUES (%lu, %d)", seedFlakeId, 1000);


    if (sFlake > sizeof(buffer)) {
        printf("Error, buffer too small.\n");
    }

    res = PQexec(conn, buffer);
    printf("Seeding database...\n");


    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        printf("INSERT command failed\n");
        printf("%s\n", PQresultErrorMessage(res));
        printf("%s\n", PQerrorMessage(conn));
        
        PQclear(res);
        db_disconnect(conn, res);
    }


    PQclear(res);
    PQfinish(conn);

    printf("Done.\n");

    return 0;
}

/* Snowflake ID transaction */ 

int db_transact_flake(void){
    PGconn *conn;
    conn = PQconnectdb("");

    char buffer[70];
    unsigned long flakeId = gen_id();
    PGresult *res;

    
    unsigned long tFlake = snprintf(buffer, sizeof(buffer), "INSERT INTO sid (flake, serial) VALUES (%lu, %d)", flakeId, 1000);


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
