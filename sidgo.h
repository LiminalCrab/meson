#include <libpq-fe.h>
#include <stdint.h>

/*database.c*/
extern int db_connections(void); /* Database connection */ 
extern int db_transact_flake(void); 


/* time.c */
extern long int epoch_data(void); /* Time since 1970/01/01 */

/* main.c */
extern unsigned long gen_id(void);


