CC=gcc
CPPFLAGS+=-I/usr/local/pgsql/include
CFLAGS?=-Werror -Wextra -Wall -O0 -g3 -pthread
INCLUDES=-I/usr/local/include/ -I./include/ `pkg-config --cflags libpq`
LIBS=-lrt -lm `pkg-config --libs libpq`
#-l38moths -ljwt -lscrypt

main: main.o db_meta.o
	$(CC) $(CFLAGS) $(CPPFLAGS) $(INCLUDES) $(LIBS) -o main main.o db_meta.o

clean:
	rm -f main.o db_meta.o