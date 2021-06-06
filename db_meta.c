#include <stdio.h>
#include <libpq-fe.h>

int 
db_connections()
{
    PGconn *conn;

    conn = PQconnectdb("");

    switch(PQstatus(conn))
    {
        case CONNECTION_STARTED:
        printf("Waiting for connection to be made.");
        break;

        case CONNECTION_OK:
        printf("Connect OK.");
        break;

        case CONNECTION_NEEDED:
        printf("Internal state: connect() needed.");
        break;

        case CONNECTION_CHECK_WRITABLE:
        printf("Checking if session is read-write.");
        break;

        case CONNECTION_CONSUME:
        printf("Consuming any extra messages.");
        break;

        case CONNECTION_GSS_STARTUP:
        printf("Negotiating GSSAPI.");
        break;

        case CONNECTION_CHECK_TARGET:
        printf("Checking target server properties.");
        break;

        case CONNECTION_MADE:
        printf("Connection OK; waiting to send.");
        break;

        case CONNECTION_BAD:
        printf("Connection failed.");
        break;

        case CONNECTION_AWAITING_RESPONSE:
        printf("Waiting for a response from the server.");
        break;

        case CONNECTION_AUTH_OK:
        printf("Received authentication; waiting for backend start-up to finish.");
        break;

        case CONNECTION_SSL_STARTUP:
        printf("Negotiating SSL encryption.");
        break;

        case CONNECTION_SETENV:
        printf("Negotiating environment-driven parameter settings.");
        break;
    }

    return 0;
}
