CC=gcc
CFLAGS=-Wall -g
LDFLAGS=

all: test

test: test.o file_operation.o
	$(CC) $(CFLAGS) -o test test.o file_operation.o $(LDFLAGS)

test.o: test.c file_operation.h
	$(CC) $(CFLAGS) -c $< -o $@

file_operation.o: file_operation.c file_operation.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f test test.o file_operation.o
