#include <stdint.h>
#include <stdio.h>
#include <sys/types.h>
#include <time.h>
#include <inttypes.h>

#define DBIL 1000000000L


int epoch_data(void){

    struct timespec ts;

    /* Current time in nanoseconds. */
    long int ns;
    time_t sec;
    uint64_t nsOut;
    clock_gettime(CLOCK_REALTIME, &ts);
    sec = ts.tv_sec;
    ns = ts.tv_nsec;

    /* final output in nano seconds. */
    nsOut = (uint64_t) sec * DBIL + (uint64_t) ns; 

    /* Convert to miliseconds */
    long int cTimeMs = nsOut / 1000000;

    return cTimeMs;
}