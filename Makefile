CFLAGS= -Wextra -Wall -ggdb -I./include
LIBS= -L./lib
L_SYSTEM_LIBS=$(LIBS)
ENPITSU_LIBS=$(LIBS) -lraylib -lm
CC=gcc

all: enpitsu
# all: algae fractal_binary_tree

algae: src/algae.c
	$(CC) $(CFLAGS) -o algae src/algae.c $(L_SYSTEM_LIBS)

fractal_binary_tree: src/fractal_binary_tree.c
	$(CC) $(CFLAGS) -o fractal_binary_tree src/fractal_binary_tree.c $(L_SYSTEM_LIBS)

enpitsu: src/enpitsu.c
	$(CC) $(CFLAGS) -o enpitsu src/enpitsu.c $(ENPITSU_LIBS)
