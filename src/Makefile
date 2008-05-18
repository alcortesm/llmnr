CC=g++
CFLAGS=-Wall
LDFLAGS=-Wall
SRCS=rr.cc args.cc main.cc
OBJS=$(SRCS:.cc=.o)
BIN=llmnr
BINPATH=${HOME}/bin/

.PHONY: install clean nuke

install: $(BIN)
	- cp $(BIN) $(BINPATH)

$(BIN): $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) -o $@

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	- rm -f core
	- rm -f $(OBJS)
	- rm -f $(BIN)

nuke: clean
	-rm -f $(BINPATH)$(BIN)

