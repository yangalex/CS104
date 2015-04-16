Heap test program is called heapTest.
Puzzle program is called Puzzle.

In order to compile heapTest and Puzzle just type 'make'

Program 1
heap.h contains an implementation of a heap data structure that uses a passed in Comparator in order to sort nodes

Run ./heapTest (for heap test code)

Program 2
A sliding puzzle game where the objective is to order all the numbers correctly. Players can ask for a cheat code and program will output a list of steps that can be used to win the game.
Uses A* search algorithm with different heuristics to solve the puzzle.

Run ./puzzle size initMoves seed heur (for puzzle)

size: size of the puzzle 2 will make a 2x2; 3 will be a 3x3 etc.
initMoves: How many random moves from starting board player wants so the program can scramble it.
seed: for random number function
heur: 0, 1 or 2 (applies different heuristics for A* algorithm)


Answers for question 2a are found at: textProblems.txt
Answers for question 2b are found at: Part b.pdf



