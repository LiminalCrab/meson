#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <libpq-fe.h>
#include "sidgo.h"

void db_disconnect(PGconn *conn, PGresult *response){
    printf("Calling db_disconnect...\n");

    PQclear(response);
    PQfinish(conn);    
    
    exit(1);
}

int db_transact_flake(PGconn *conn){
    printf("Calling db_transact_flake\n");

    char buffer[1024];
    long int flakeid = gen_id();
    PGresult   *res;
    printf("%ld\n", flakeid);

    
    size_t tFlake = snprintf(buffer, sizeof(buffer), "INSERT INTO sid (flake, serial) VALUES (%ld, %d)", flakeid, 10000);
    printf("TF BYTES: %ld\n", tFlake);
    printf("BUFFER: %s", buffer);


    if (tFlake > sizeof(buffer)) {
        printf("Error, buffer too small.");
    }

    res = PQexec(conn, buffer);

    if (PQresultStatus(res) != PGRES_COMMAND_OK) {

        printf("INSERT command failed\n");        
        PQclear(res);
        db_disconnect(conn, res);
    }      
    PQclear(res);
    PQfinish(conn);
    
    return 0;
}

/* Database connection status functions. */ 
int db_connections(){
    printf("Calling db_connections...");
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
