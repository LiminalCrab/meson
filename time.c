#include <stdio.h>
#include <time.h>

int epoch(void){
    
    /* Time in seconds since Jaunary 1st, 1970 */
    time_t seconds;
    seconds = time(NULL);

    return seconds;
}