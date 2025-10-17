# Makefile simples para compilar o projeto
CC=gcc
CFLAGS=-O2 -Wall -Wextra

all: freefire

freefire: src/main.o
	$(CC) $(CFLAGS) -o $@ $^

src/main.o: src/main.c
	$(CC) $(CFLAGS) -c -o $@ $<

run: freefire
	./freefire

clean:
	rm -f src/*.o freefire
