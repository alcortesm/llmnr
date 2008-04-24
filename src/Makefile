llmnr: args.o main.o
	g++ -Wall -I. args.o main.o -o llmnr

args.o: args.cc include/args.h
	g++ -Wall -I. args.cc -c

main.o: main.cc include/args.h
	g++ -Wall -I. main.cc -c

clean:
	- rm -rf *.o
	- rm -rf llmnr
