CC=gcc
CFLAGS=-Wall -g

meson: meson.o
	$(CC) -o meson meson.o

clean:
	rm -f meson