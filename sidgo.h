#include <libpq-fe.h>
#include <stdint.h>

/*database.c*/
extern int db_connections(); /* Database connection */ 
extern int db_transact_flake(); 


/* time.c */
extern long int epoch_data(void); /* Time since 1970/01/01 */

/* main.c */
extern long int gen_id(PGconn *conn, PGresult *response);


