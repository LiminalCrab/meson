#include <stdio.h>
#include <libpq-fe.h>

int db_connections(){
    PGconn *conn;

    conn = PQconnectdb("");

    switch(PQstatus(conn)){

        case CONNECTION_STARTED:
        printf("Waiting for connection to be made.\n");
        break;

        case CONNECTION_OK:
        printf("Connect OK.\n");
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

        case CONNECTION_BAD:
        printf("Connection failed.\n");
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
