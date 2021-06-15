#include <libpq-fe.h>
#include <stdint.h>

/*database.c*/
extern int db_connections(void); /* Database connection */ 
extern int db_transact_flake(void); /* Embeds generated ID into DB table */
extern int db_table_exist(void); /* Check to see if the table exists, if not, create it. */
extern int db_init_seed(void); /* Seeds the database with the values provided by gen_seed_id*/ 
extern int db_row_id(void);

/* time.c */
extern long int epoch_data(void); /* Time since 1970/01/01 */

/* main.c */
extern unsigned long gen_id(void);
extern unsigned long gen_seed_id(void);


