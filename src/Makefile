DEPS= args.h rr.h
SRCS= args.c rr.c main.c
BIN=llmnr
MAN=llmnr.1


OBJS=$(SRCS:.c=.o)
CC=gcc
CFLAGS=-pthread -Wall -g



.PHONY: install clean nuke

install: $(BIN)
	- cp -f $(BIN) ~/bin/
	- cp -f $(MAN) ~/man/man1/

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(BIN): $(OBJS)
	gcc -o $@ $^ $(CFLAGS)

clean:
	- rm -f *.o *~ core $(BIN)

nuke: clean
	- rm -f ~/bin/$(BIN)
	- rm -f ~/man/man1/$(MAN)
