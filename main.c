#include <stdio.h>
#include <libpq-fe.h>


int 
db_connections()
{
    PGconn *conn;

    conn = PQconnectdb("dbname=ahh host=ahh user=ahh password=ahh");

    switch(PQstatus(conn))
    {
        case CONNECTION_STARTED:
        printf("Waiting for connection to be made.");
        break;

        case CONNECTION_OK:
        printf("Connect OK.");
        break;

        case CONNECTION_NEEDED:
        printf("Connection to dabase needs ... ");
        break;

        case CONNECTION_CHECK_WRITABLE:
        printf("Check if connection is writable.");
        break;

        case CONNECTION_CONSUME:
        printf("Connection consuming...");
        break;

        case CONNECTION_GSS_STARTUP:
        printf("Connection GSS startup...");
        break;

        case CONNECTION_CHECK_TARGET:
        printf("CHECK TARGET");
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
    }

    return 0;
}

int 
snowflake()
{
    // All of these variables have arbitrary values, temporary example
    long int uniqueId = 1387263000; // miliseconds
    long int tableId = 10000; 
    int rowId = 5; // Row ID modulus 1024
    int userId = 30000; 

    long int x = uniqueId << (64 - 41);
    long int tbusMod = userId % tableId;

    x += tbusMod << (64 - 41 - 13);
    x += (rowId % 1024);

    printf("UNIQUE ID: %ld \n", x);
    printf("BYTES: %ld", sizeof(x));

    return 0;
}


int 
main()
{
    db_connections();
}