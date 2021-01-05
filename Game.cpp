#include "Game.h"
#include <vector>
#include <string>
#include <map>
#include <algorithm>


Game::Game(int y, int x): size(x*y) {
      height = y;
      width = x;
}


bool Game::inField (int x, int y, int w, int h) {
  if ( x < 0 || x >= w ) return false;
  if ( y < 0 || y >= h ) return false;
  
  return true;
}


void Game::randomiseBoardLL() {
  int r = rand() %30; 
  node* tmp = nullptr;
  node* tmp2;
  for (int i = 0; i < r; ++i) {
    bool x = rand() % 2;
    int row = rand() % this-> width;
    int col = rand() % this-> height;

    llist->add_node(x, row, col); 
    std::cout << "This node value is " << x << '\n';
  }
}


void Game::randomiseBoardSM() {
  int r = rand() %9000;
  coor pos;
  for (int i = 0; i < r; ++i) {
    pos.rowPos = rand() % this-> width;
    pos.colPos = rand() % this-> height;
    this->sMatrix[pos] = 1;
    this->aliveCoors.push_back(pos);
  }
}


//loop over mooreNeighbours of each alive cell and see how many alive neighbours she has
std::vector<coor> Game::neighbours(coor c) {
  std::vector<coor> neighVec { };
  std::vector<coor> mooreNeigh = mooreNieghbourhood(c, this->width, this->height);
  std::sort(this->aliveCoors.begin(), this->aliveCoors.end());
  std::sort(mooreNeigh.begin(), mooreNeigh.end());

  std::set_intersection(this->aliveCoors.begin(), this->aliveCoors.end(), mooreNeigh.begin(), mooreNeigh.end(), std::back_inserter(neighVec));

  return neighVec;
}


// Look at sMatrix and find 'dead' cells that are now alive (have 3 neighbours)
// This should be done in a way that the same sMatrix is used for newLive and currentLive, then merge the new matricies after a generational step to get next steps sMatrix
mymap Game::newLive() {
  mymap nextGen2;
  coor pos;
  


  return nextGen2;
}


// Look at moore neighbourhood of each alive cell and choose whether it lives or not
mymap Game::currentLive() {
  mymap nextGen;
  mymap noNeighs;
  for (auto const &[key, val] : this->sMatrix) {
    
    if(noNeighs.find(key) == noNeighs.end()) {
      noNeighs[key] = 0;
    }
    
    std::vector<coor> myNeighs = mooreNieghbourhood(key, this->width, this->height);
    for (coor n : myNeighs) {
      if(noNeighs.find(n) == noNeighs.end()) {
        noNeighs[n] = 1;
      } else {
        noNeighs[n] += 1;
      }
    }
  }
  
  for (auto const &[key, val] : noNeighs) {
    if (this->sMatrix.find(key) != this->sMatrix.end() && (val == 2 or val == 3)) {
      nextGen[key] = 1;
    }
    if (this->sMatrix.find(key) == this->sMatrix.end() && val == 3) {
      nextGen[key] = 1;
    }
  }

    

    //int mooreN = neighbours(key).size();
    //std::cout << "number of neighbours for " << key << "is " << mooreN << std::endl;
    //if (mooreN == 2 || mooreN == 3)
    //{
    //  nextGen[key] = val;
    //} else {
      //such that its a new map with non-new cells that are alive in the next generation
    //  continue;
    //}
  //}


  this->sMatrix = nextGen;
  return nextGen;
}



std::vector<coor> Game::mooreNieghbourhood(coor c, unsigned int width, unsigned int height) {
  std::vector<coor> neighs;
  int x = c.rowPos;
  int y = c.colPos;
  const int ys[] = { -1, -1, -1, 1, 1, 1, 0, 0 };
  const int xs[] = { -1, 0, 1, -1, 0, 1, -1, 1 };

  for (int i = 0; i <8; ++i) {
    coor tmp;
    if (inField(x + xs[i], y + ys[i], width, height)) {
      tmp.rowPos = x + xs[i];
      tmp.colPos = y + ys[i];
      neighs.push_back(tmp); 
    }
  }
  return neighs;  
}
