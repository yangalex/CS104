all: copytest settest pgindex

copytest: bin/llistint.o bin/llistint_test.o
	g++ -g -o bin/copytest bin/llistint.o bin/llistint_test.o

bin/llistint.o: llistint.h llistint.cpp
	g++ -g -c llistint.cpp -o bin/llistint.o

bin/llistint_test.o: llistint.h llistint_test.cpp
	g++ -g -c llistint_test.cpp -o bin/llistint_test.o

settest: bin/setint.o bin/llistint.o bin/setint_test.o
	g++ -g -o bin/settest bin/setint.o bin/llistint.o bin/setint_test.o

bin/setint.o: llistint.h setint.h setint.cpp
	g++ -g -c setint.cpp -o bin/setint.o

bin/setint_test.o: llistint.h setint.h setint_test.cpp
	g++ -g -c setint_test.cpp -o bin/setint_test.o

pgindex: bin/setint.o bin/llistint.o bin/pgindex.o
	g++ -g -o bin/pgindex bin/setint.o bin/llistint.o bin/pgindex.o

bin/pgindex.o: llistint.h setint.h pgindex.cpp
	g++ -g -c pgindex.cpp -o bin/pgindex.o