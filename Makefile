a.out: main.o 
	g++ main.o -o a.out

main.o: main.cpp amgraph.h
	g++ -c main.cpp -o main.o

.PHONY: clean
clean: 
	rm -r *.o *.exe