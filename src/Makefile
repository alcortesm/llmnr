CC=g++
CFLAGS=-Wall
LDFLAGS=-Wall
SRCS=clas.cc type.cc rr.cc args.cc
OBJS=$(SRCS:.cc=.o)
BIN=llmnr
TEST=test
BINPATH=${HOME}/bin/

.PHONY: install clean nuke

install: $(BIN) $(TEST)
	- cp $(BIN) $(BINPATH)

$(BIN): $(OBJS) main.o
	$(CC) $(LDFLAGS) $(OBJS) main.o -o $@

$(TEST): $(OBJS) test.o
	$(CC) $(LDFLAGS) $(OBJS) test.o -o $@

%.o: %.cc
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	- rm -f core
	- rm -f $(OBJS)
	- rm -f $(BIN)
	- rm -f $(TESTS)

nuke: clean
	-rm -f $(BINPATH)$(BIN)

