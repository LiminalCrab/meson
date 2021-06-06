#include <stdio.h>
#include <time.h>

int epoch(void){

    time_t now;
    struct tm ts;
    char buf[80];

    time(&now);

    ts = *localtime(&now);
    //use ts, get the required timestamps.
    //printf("%s\n", );

    return 0;

}