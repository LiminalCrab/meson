CC=gcc 
CFLAGS=-Wall -g -lpq
sid64: sig64.o
	$(CC) -o sidg64 sidg64.o

clean:
	rm -f sidg64