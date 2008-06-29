CC=g++
CFLAGS=-Wall -g
LDFLAGS=-Wall -g
SRCS=klass.cc type.cc rr.cc args.cc util.cc rdata.cc rdataA.cc rdataMX.cc
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
	- rm -f $(OBJS) main.o test.o
	- rm -f $(BIN)
	- rm -f $(TEST)

nuke: clean
	-rm -f $(BINPATH)$(BIN)

