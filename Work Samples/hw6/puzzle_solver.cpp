#include "puzzle_solver.h"

using namespace std;

PuzzleSolver::PuzzleSolver(const Board &b, PuzzleHeuristic* ph) :
	_b(b), _expansions(0), _ph(ph)
{
	PuzzleMoveBoardComp boardComp;
	PuzzleMoveScoreComp scoreComp;

	closedList = new PuzzleMoveSet(boardComp);
	openList = new Heap<PuzzleMove*, PuzzleMoveScoreComp>(2, scoreComp);

}

PuzzleSolver::~PuzzleSolver()
{	
	for(unsigned int j=0; j < allBoards.size(); j++) {
		delete allBoards[j];
	}

	for(unsigned int i=0; i < allPuzzleMoves.size(); i++) {
		delete allPuzzleMoves[i];
	}

	delete openList;
	delete closedList;
}

void PuzzleSolver::run()
{
	// Generate initial PuzzleMove
	PuzzleMove* startBoard = new PuzzleMove(&_b);
	allPuzzleMoves.push_back(startBoard);
	startBoard->h = _ph->compute(_b);

	// Push initial state to open and closed list
	openList->push(startBoard);
	closedList->insert(startBoard);

	// while open list is not empty
	while(openList->empty() == false) {
		// Get the node with smallest f value
		PuzzleMove* nextMove = openList->top();
		// if puzzle is solved
		if(nextMove->b->solved()) {
			generateSolution(nextMove);
			return;
		}
		else {
			// pop heap
			openList->pop();
			// generate potential moves
			map<int, Board*> moveMap = nextMove->b->potentialMoves();
			map<int, Board*>::iterator it;
			// iterate through each loop, creating a PuzzleMove for each
			// and inserting into open list and closed list
			for(it = moveMap.begin(); it != moveMap.end(); ++it) {
				// Add to allBoads for easy deallocation
				allBoards.push_back(it->second);
				// Create puzzle move from a board
				PuzzleMove* tempPuzzleMove = new PuzzleMove(it->first, it->second, nextMove);
				// Add to allPuzzleMoves for easy deallocation
				allPuzzleMoves.push_back(tempPuzzleMove);
				// Set board heuristics
				tempPuzzleMove->h = _ph->compute(*tempPuzzleMove->b);
				// Check if move is not in closed list
				if(closedList->find(tempPuzzleMove) == closedList->end()) {
					openList->push(tempPuzzleMove);
					_expansions++;
					closedList->insert(tempPuzzleMove);
				}
			}
		}
	}
}

std::deque<int> PuzzleSolver::getSolution()
{
	return _solution;
}


void PuzzleSolver::generateSolution(PuzzleMove* solvedPuzzle)
{
	PuzzleMove* tempPuzzleMove = solvedPuzzle;
	while(tempPuzzleMove->tileMove != -1) {
		_solution.push_front(tempPuzzleMove->tileMove);
		tempPuzzleMove = tempPuzzleMove->prev;
	}
}


int PuzzleSolver::getNumExpansions()
{
	return _expansions;
}
