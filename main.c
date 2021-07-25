/*
MIT License
Copyright (c) 2021 Preston Smith
Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in 
the Software without restriction, including without limitation the rights to 
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies 
of the Software, and to permit persons to whom the Software is furnished to do 
so, subject to the following conditions:

The above copyright notice and this permission notice 
(including the next paragraph) shall be included in all copies or substantial 
portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE 
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, 
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE 
SOFTWARE.
*/

#include <stdio.h>
#include <inttypes.h>
#include <unistd.h>
#include <libpq-fe.h>
#include "sidgo.h"

/* Initial seed for the database*/ 
unsigned long gen_seed_id(void){

    unsigned long seed_milTime = epoch_data();
    unsigned int seed_serial = 1000;
    unsigned int seed_rowId = 5;
    unsigned int seed_userId = 10000;

    unsigned long x = seed_milTime << (64 - 41);
    unsigned long  usrSrlMod = seed_userId % seed_serial;

    x += usrSrlMod << (64 - 41 - 13);
    x += (seed_rowId & 0x3ff);

    printf("GENERATED SEED: %lu\n", x);
    
    return x;
}

/* Generate ID */ 
unsigned long gen_id(void){

    unsigned long milTime = epoch_data();
    unsigned int serial = 1000;
    unsigned int rowId = db_row_id();
    unsigned int userId = 10000;

    unsigned long x = milTime << (64 - 41);
    unsigned long  usrSrlMod = userId % serial;

    x += usrSrlMod << (64 - 41 - 13);
    x += (rowId & 0x3ff);

    printf("GENERATED FLAKE: %lu\n", x);
    
    return x;
}

int main(int argc, char *argv[]){

    int conn_stat = db_connections();
    int opt;

    while((opt = getopt(argc, argv, "ash")) != -1) 
        { 
            switch(opt) 
            { 
                case 'a':
                    db_transact_flake();
                    break;
                case 's':
                    if (conn_stat == CONNECTION_OK){
                        db_table_exist();
                        db_init_seed();
                    }
                    break; 
                case 'h': 
                    printf("options available: %c\n", opt);
                    printf("-s >> seed the database with the first entry, use this if you're just starting.\n");
                    printf("-h >> help, shows the available commands.\n"); 
                    break; 
            } 
        } 

        return 0;

}
