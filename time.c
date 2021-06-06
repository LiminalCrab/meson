#include <stdio.h>
#include <time.h>

int epoch(void){

    struct tm tm_time;
    time_t sigTime;

    int sigYe = tm_time.tm_year -= 1900; 
    int sigMo = tm_time.tm_mon--;
    int sigDa = tm_time.tm_mday;
    int sigHo = tm_time.tm_hour;
    int sigMi = tm_time.tm_min;
    int sigSe = tm_time.tm_sec;

    printf("%d-%d-%d %d:%d:%d", sigYe, sigMo, sigDa, sigHo, sigMi, sigSe);

    tm_time.tm_isdst =1;
    /* Time in seconds since Jaunary 1st, 2011 */

    return mktime(&tm_time);
}