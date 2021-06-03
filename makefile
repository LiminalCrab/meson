
#CC=gcc 
#CFLAGS=-Wall -g -Werror

#GTK = pkg-config --libs libpq
#GTK2 = pkg-config --cflags libp
CC=gcc
CPPFLAGS += -I/usr/local/pgsql/include
CFLAGS?= -Werror -Wextra -Wall -O0 -g3 -pthread -L/usr/local/pgsql/lib -lpq
#INCLUDES= -I/usr/local/include/ -I./include/ `pkg-config libpq`
#LIBS=-lrt -l38moths -ljwt -lscrypt -lm `pkg-config --libs libpq`


main: main.o
	$(CC) $(CFLAGS) -o main main.o 

clean:
	rm -f main