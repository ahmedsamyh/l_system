CFLAGS= -Wextra -Wall -ggdb -I./include
LIBS= -L./lib -lraylib -lm
CC=gcc

main: src/main.c
	$(CC) $(CFLAGS) -o main src/main.c $(LIBS)
