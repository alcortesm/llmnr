llmnr: args.o main.o
	g++ -Wall args.o main.o -o llmnr

args.o: args.cc args.h
	g++ -Wall args.cc -c

main.o: main.cc args.h
	g++ -Wall main.cc -c

clean:
	- rm -rf *.o
	- rm -rf llmnr
