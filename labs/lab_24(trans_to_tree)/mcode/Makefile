CC = gcc
CFLAGS = -g -Wall -Wextra -pedantic -std=c99 -w -pipe -O3

lab24:  lexer.o tree.o transform.o main.o
	$(CC) $^ -o $@ -lm

clean:
	rm -f *.o lab24
