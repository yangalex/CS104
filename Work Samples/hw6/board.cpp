#include <iostream>
#include <iomanip>
#include <map>
#include <cmath>
#include <cstdlib>
#include <stdexcept>
#include "board.h"
using namespace std;


Board::Board(int dim, int numInitMoves, int seed )
{
  _size = dim*dim;
  _tiles = new int[_size];
  srand(seed);
  for(int i=0; i < _size; i++){
    _tiles[i] = i;
  }
  int blankLoc = 0;
  while(numInitMoves > 0){
    int r = rand()%4;
    int randNeighbor = -1;
    if(r == 0){
      int n = blankLoc - dim;
      if(n >= 0){
	randNeighbor = n;
      }
    }
    else if(r == 1){
      int w = blankLoc - 1;
      if(blankLoc % dim != 0){
	randNeighbor = w;
      }
    }
    else if(r == 2){
      int s = blankLoc + dim;
      if(s  < _size){
	randNeighbor = s;
      }
    }
    else {
      int e = blankLoc + 1;
      if(blankLoc % dim != dim-1){
	randNeighbor = e;
      }
    }
    if(randNeighbor > -1){
      _tiles[blankLoc] = _tiles[randNeighbor];
      _tiles[randNeighbor] = 0;
      blankLoc = randNeighbor;
      numInitMoves--;
    }
  }
}

// Copy constructor
Board::Board(const Board& rhs) 
{
  this->_size = rhs._size;
  this->_tiles = new int[this->_size];

  for(int i=0; i < rhs._size; i++) {
    _tiles[i] = (rhs._tiles)[i];
  }

}

// Destructor
Board::~Board()
{
  delete[] _tiles;
}


void Board::move(int tile)
{
  int side_dim = dim();
  int tr, tc, br, bc;

  // find tile row and column
  int i=-1;
  while(_tiles[++i] != tile);

  tr = i / side_dim; 
  tc = i % side_dim;

  // find blank row and column
  int j=-1;
  while(_tiles[++j] != 0);

  br = j / side_dim;
  bc = j % side_dim;

  if( abs(static_cast<double>(tr-br)) + abs(static_cast<double>(tc-bc)) != 1){
    cout << "Invalid move of tile " << tile << " at ";
    cout << tr << "," << tc << " and blank spot at ";
    cout << br << "," << bc << endl;
    return;
  }
  // Swap tile and blank spot
  _tiles[j] = tile;
  _tiles[i] = 0;
}



// Generate new boards representing all the potential moves of tiles into 
// the current blank tile location. The returned map should have
// the key as the tile moved and the value as a new Board object with the
// configuration reflecting the move of that tile into the blank spot
map<int, Board*> Board::potentialMoves() const
{
  int blankLoc;
  int _dim = dim();
  // Find blank spot
  for(int i=0; i < _size; i++) {
    if(_tiles[i] == 0) {
      blankLoc = i;
    }
  }

  map<int, Board*> moveMap;

  // Go north
  int nNeighbor = blankLoc - _dim;
  if(nNeighbor >= 0) {
    Board* northBoard = new Board(*this);
    int nValue = (*northBoard)[nNeighbor];
    northBoard->move(nValue);
    moveMap.insert(make_pair(nValue, northBoard));
  }
  // Go West 
  int wNeighbor = blankLoc - 1;
  if(blankLoc % _dim != 0) {
    Board* westBoard = new Board(*this);
    int wValue = (*westBoard)[wNeighbor];
    westBoard->move(wValue);
    moveMap.insert(make_pair(wValue, westBoard));
  }
  // Go East
  int eNeighbor = blankLoc + 1;
  if(blankLoc % _dim != _dim - 1) {
    Board* eastBoard = new Board(*this);
    int eValue = (*eastBoard)[eNeighbor];
    eastBoard->move(eValue);
    moveMap.insert(make_pair(eValue, eastBoard));
  }
  // Go South
  int sNeighbor = blankLoc + _dim;
  if(sNeighbor < _size) {
    Board* southBoard = new Board(*this);
    int sValue = (*southBoard)[sNeighbor];
    southBoard->move(sValue);
    moveMap.insert(make_pair(sValue, southBoard));
  }

  return moveMap;
  
}


bool Board::solved() const 
{
  for(int i=0; i < _size; i++) {
    if(_tiles[i] != i) {
      return false;
    }
  }

  return true;
}

std::ostream& operator<<(std::ostream &os, const Board &b)
{
  int counter = 0;
  for(int i=0; i < b.dim(); i++) {
    b.printRowBanner(os);
    for(int j=0; j < b.dim(); j++) {
      if(b[counter] == 0) {
        os << "|  ";
        counter++;
      }
      else if(b[counter] >= 10) {
        os << "|" << b[counter];
        counter++;
      }
      else {
        os << "| " << b[counter];
        counter++;
      }
    }
    os << "|" << endl;
  }

  b.printRowBanner(os);

  return os;
}


bool Board::operator<(const Board& rhs) const
{
  for(int i=0; i < _size; i++) {
    if(this->_tiles[i] < rhs[i]) {
      return true;
    }
    else if(this->_tiles[i] > rhs[i]) {
      return false;
    }
  }

  return false;
}


const int& Board::operator[](int loc) const 
{ 
  return _tiles[loc]; 
}

int Board::size() const 
{ 
  return _size; 
}

int Board::dim() const
{
  return static_cast<int>(sqrt(_size));
}

void Board::printRowBanner(ostream& os) const
{
  int side_dim = dim();
  if(side_dim == 0) return;
  os << '+';
  for(int i=0; i < side_dim; i++){
    os << "--+";
  }
  os << endl;
}
