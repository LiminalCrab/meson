#include <stdint.h>
#include <stdio.h>
#include <sys/types.h>
#include <time.h>
#include <inttypes.h>
#define DBIL  1000000000L


long int gen_epoch(const long int *arbEpoch, long int cTimeNs){
    /* 
    So now we generate the epoch by converting time to miliseconds, and subtract them. 
    */

    const long int lxArbEpoch = *arbEpoch;
    long int lxCTimeNs = cTimeNs;

    const long int arbEpochMs = lxArbEpoch / 1000000;
    long int cTimeMs = lxCTimeNs / 1000000;
    printf("Arbitrary Epoch MILI: %ld, Current Time MILI: %ld\n", arbEpochMs, cTimeMs);
    
    return 0;
}

int epoch_data(void){
    /* 
    Possibly just use unix time, divide the difference from unix epoch to our given epoch,
    I'll need the nanoseconds multiplier, to go to miliseconds. Ideally need to stay as long as
    I can in ins struct timespec, only convert when I need to print / handle the final result.
    Can't forget to normalize timespecs when calculating them.
    */

    struct timespec ts;

    /* Time since Saturday, January 1, 2011 12:00:00 AM in nanoseconds. */
    const long int pEpoch = 1293840000000000000; //mili 1293840000000
    ts.tv_nsec = pEpoch; // output stEpoch

    /* Current time in nanoseconds. */
    long int ns;
    time_t sec;
    uint64_t all;
    clock_gettime(CLOCK_REALTIME, &ts);
    sec = ts.tv_sec;
    ns = ts.tv_nsec;

    /* final output in nano seconds. */
    all = (uint64_t) sec * DBIL + (uint64_t) ns; 

    uint64_t *sndCTimeNs = &all;
    gen_epoch(&pEpoch, *sndCTimeNs);

    return 0;
}