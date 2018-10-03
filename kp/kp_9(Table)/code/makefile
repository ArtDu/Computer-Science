CC = gcc
FLAGS =-std=c99 -Wall -Wextra -Wshadow -Wstrict-prototypes -Wold-style-definition -pedantic -O2 -Wno-unused-variable -Wno-sign-compare -Wno-unused-result -Wno-unused-parameter -Wimplicit-function-declaration
SOURCES = main.o table.o

build: main.o table.o
	$(CC) $(FLAGS) -o build $(SOURCES)

main.o: main.c table.h
	$(CC) $(FLAGS) -c main.c

table.o: table.c table.h
	$(CC) $(FLAGS) -c table.c

clean:
	rm -f $(SOURCES)
