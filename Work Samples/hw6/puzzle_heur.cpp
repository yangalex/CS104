#include "puzzle_heur.h"
#include <stdlib.h> // for abs()

using namespace std;

int PuzzleManhattanHeuristic::compute(const Board& b)
{
	int h = 0;

	for(int i=0; i < b.size(); i++) {
		if(b[i] != 0) {
			if(b[i] != i){
				int currentRow = i / b.dim();
				int currentCol = i % b.dim();
				int targetRow = b[i] / b.dim();
				int targetCol = b[i] % b.dim();
				h += abs(targetRow - currentRow);
				h += abs(targetCol - currentCol);
			}
		}
	}

	return h;	
}

int PuzzleOutOfPlaceHeuristic::compute(const Board& b)
{
	int outOfPlace = 0;

	for(int i=0; i < b.size(); i++) {
		if(b[i] != 0) {
			if(b[i] != i) {
				outOfPlace++;
			}
		}
	}

	return outOfPlace;
}

int PuzzleBFSHeuristic::compute(const Board& b)
{
	return 0;
}