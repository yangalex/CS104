CC=g++ -g
CFLAGS=-c -Wall

all: puzzle heapTest

puzzle: bin/board.o bin/puzzle_heur.o bin/puzzle_move.o bin/puzzle_solver.o bin/puzzle.o
	$(CC) bin/board.o bin/puzzle_heur.o bin/puzzle_move.o bin/puzzle_solver.o bin/puzzle.o -o puzzle

heapTest: bin/heapTest.o
	$(CC) bin/heapTest.o -o heapTest

bin/heapTest.o: heapTest.cpp heap.h
	$(CC) $(CFLAGS) heapTest.cpp -o $@

bin/puzzle.o: puzzle.cpp
	$(CC) $(CFLAGS) puzzle.cpp -o $@

bin/board.o: board.cpp board.h 
	$(CC) $(CFLAGS) board.cpp -o $@

bin/puzzle_heur.o: puzzle_heur.cpp puzzle_heur.h
	$(CC) $(CFLAGS)	puzzle_heur.cpp -o $@

bin/puzzle_move.o: puzzle_move.cpp puzzle_move.h
	$(CC) $(CFLAGS) puzzle_move.cpp -o $@

bin/puzzle_solver.o: puzzle_solver.cpp puzzle_solver.h heap.h
	$(CC) $(CFLAGS) puzzle_solver.cpp -o $@

clean:
	rm *o puzzle