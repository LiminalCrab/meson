# ABOUT

Sidg64 is simple unique identity generator for postgresql written in ANSI C.
It's purpose is to generate 64 bit unique id's and store them in a database table.

## Requirements
Linux / Unix.
A postgres database and a table with this schema [here](https://github.com/LiminalCrab/Sidg64/table). 

## Terms

I occassionally call the unique ID's "flakes" short for snowflakes. Twitter had a project called "snowflake" which generated "snowflake ID's" which is what they're referred to as.

# Getting Started

1. clone the repo, cd into the directory, and type "make main" in the terminal
2. type "make clean" in the terminal.
3. type ./main -s to create and seed the database table, this is extremely important.
4. type ./main -a to generate your unique ID's thereafter. 

## Command Line Arguments

./main -h for help
./main -s create and seed the database with the first entry, use this if you're just starting.
./main -a creates the unique ID's and embeds them in the database.

# Documentation

## time.c 

### long int epoch_data(void)

Gets your current time in nanoseconds, converts it to miliseconds, and returns the milisecond value.

## database.c

### int db_connections(void)

Returns the database connection status, if the database connection is OK, the program will continue based off code in the main.c int main() function. Otherwise the program exits.

### int db_transact_flake(void)

Embeds generated flake into the 'sid' database table. 

### int db_table_exist(void)

Check to see if the table 'sid' exists, if not, create it.

### int db_init_seed(void)

Seeds the database with the values provided by gen_seed_id

### int db_row_id(void)

Returns the most recent row id from the database, extremely important as it's used for generating future flakes. 

## main.c

### unsigned long gen_id(void);

Using the function epoch_data(), it takes time and mutates it into a flake through various bitwise operations. 

**milTime** is time in miliseconds, we take the first 41 bits of this and shift it left.

**serial** is assigned as arbitrarily assigned at 1,000 (but can be any number between 1,000 and 9,999), and is used in conjunction with the **userId** (arbitrarily assigned at 10,000 (but can be any number between 10,000 and 99,999). This is necessary for id length. We get the remainder of these two fill the next 13 bits with this value.

**rowId** is the most recently incremented id in the sid table, which is modded by 1024 so it fits 10 bits. 

### unsigned long gen_seed_id

Same as above, but all the numbers in this are hardcoded, it's used to generate the first Id to go into the table, everything after is handled by gen_id()

This flake is what I call the "seed", since it's what future Id's will require to use the data provided in the sid table. 
 


