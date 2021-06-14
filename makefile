CC=gcc
CPPFLAGS+=-I/usr/local/pgsql/include
CFLAGS?=-Werror -Wextra -Wall -O0 -g3 -pthread -g
INCLUDES=-I/usr/local/include/ -I./include/ `pkg-config --cflags libpq`
LIBS=-lrt -lm `pkg-config --libs libpq`
#-l38moths -ljwt -lscrypt

main: main.o database.o time.o
	$(CC) $(CFLAGS) $(CPPFLAGS) $(INCLUDES) $(LIBS) -o main main.o database.o time.o

clean:
	rm -f main.o database.o time.o