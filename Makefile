CFLAGS= -Wextra -Wall -ggdb -I./include
LIBS= -L./lib -lraylib -lm
CC=gcc

all: algae fractal_binary_tree

algae: src/algae.c
	$(CC) $(CFLAGS) -o algae src/algae.c $(LIBS)

fractal_binary_tree: src/fractal_binary_tree.c
	$(CC) $(CFLAGS) -o fractal_binary_tree src/fractal_binary_tree.c $(LIBS)
