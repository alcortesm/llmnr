CC=g++
CFLAGS=-Wall
LDFLAGS=-Wall
SRCS=clas.cc type.cc rr.cc args.cc main.cc
OBJS=$(SRCS:.cc=.o)
BIN=llmnr
BINPATH=${HOME}/bin/

TESTS_BINS=type-test clas-test
TESTS_SRCS=type-test.cc clas-test.cc
TESTS_OBJS=$(TESTS_SRCS:.cc=.o)

.PHONY: install clean nuke

install: $(BIN) $(TESTS_BINS)
	- cp $(BIN) $(BINPATH)

$(BIN): $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) -o $@

%.o: %.cc
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	- rm -f core
	- rm -f $(OBJS)
	- rm -f $(BIN)
	- rm -f $(TESTS_OBJS)
	- rm -f $(TESTS_BINS)

nuke: clean
	-rm -f $(BINPATH)$(BIN)

type-test: type-test.o type.o
	$(CC) $(CFLAGS) -o $@ type-test.o type.o

clas-test: clas-test.o clas.o
	$(CC) $(CFLAGS) -o $@ clas-test.o clas.o

