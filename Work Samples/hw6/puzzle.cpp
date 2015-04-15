#include <iostream>
#include <cstdlib>
#include <stdlib.h>
#include <deque>
#include "board.h"
#include "puzzle_heur.h"
#include "puzzle_solver.h"

using namespace std;

int main(int argc, char *argv[])
{
  if(argc < 5){
    cerr << "Usage: ./puzzle size initMoves seed heur" << endl;
    return 1;
  }

  int dimension = atoi(argv[1]);
  int initMoves = atoi(argv[2]);
  int seed = atoi(argv[3]);
  int heur = atoi(argv[4]);

  PuzzleHeuristic* ph;
  // set heuristics
  if(heur == 0) {
  	ph = new PuzzleBFSHeuristic;
  }
  else if(heur == 1) {
  	ph = new PuzzleOutOfPlaceHeuristic;
  }
  else if(heur == 2) {
  	ph = new PuzzleManhattanHeuristic;
  }

  Board gameBoard(dimension, initMoves, seed);

  while(gameBoard.solved() != true) {
  	cout << gameBoard;
  	cout << endl;
  	cout << "Enter tile number to move or -1 for a cheat: ";
  	int nextMove;
  	cin >> nextMove;
  	if(nextMove == -1) {
  		PuzzleSolver gameSolver(gameBoard, ph);
  		gameSolver.run();
  		deque<int> solutions = gameSolver.getSolution();
  		cout << "Try this sequence: " << endl;
  		for(unsigned int i=0; i < solutions.size(); i++) {
  			cout << solutions[i] << " ";
  		}
  		cout << endl;
  		cout << "(Expansions = " << gameSolver.getNumExpansions() << ")" << endl;
  		cout << endl;
  	}
  	else {
  		gameBoard.move(nextMove);
  	}
  }

  cout << gameBoard;

  delete ph;

  return 0;
}
