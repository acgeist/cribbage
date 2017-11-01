# Mostly copied from <www.cs.colby.edu/maxwell/courses/tutorials/maketutor>
# Last updated: Wed 01 Nov 2017 08:44:47 AM EDT
CC = gcc
CFLAGS = -I. -Wall -Werror -Wpedantic -Wextra
DEPS = bicycle.h
OBJ = cribbage.o bicycle.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

cribbagemake: $(OBJ)
	gcc -o cribbage $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f *.o
