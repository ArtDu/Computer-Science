CC = gcc
FLAGS =-std=c99 -Wall -Wextra -Wshadow -Wstrict-prototypes -Wold-style-definition -pedantic -O2 -Wno-unused-variable -Wno-sign-compare -Wno-unused-result -Wno-unused-parameter -Wimplicit-function-declaration
SOURCES = main.o lis.o
EXECUTABLE = start

build: main.o lis.o
	$(CC) $(FLAGS) -o build $(SOURCES)

main.o: main.c lis.h
	$(CC) $(FLAGS) -c main.c

lis.o: lis.c lis.h
	$(CC) $(FLAGS) -c lis.c

clean:
	rm -f $(SOURCES)
