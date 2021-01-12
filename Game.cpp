#include "Game.h"
#include <vector>
#include <string>
#include <map>
#include <algorithm>


Game::Game(int y, int x, char entropic): size(x*y) {
      height = y;
      width = x;
      entropicLiving = entropic;
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
    if (entropicLiving == 'n') {
      this->sMatrix[pos] = 1;
    } else {
      this->sMatrix[pos] = rand() % 21 - 9;
    }
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


// Look at moore neighbourhood of each alive cell and choose whether it lives or not
mymap Game::currentLive() {
  mymap nextGen;
  mymap noNeighs;

  if (entropicLiving == 'n') {
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
    // Here we can add some sort of entropic destabalisation, instead of dying due to overcrowding (overcrowding assumes limited resources)
      if (this->sMatrix.find(key) != this->sMatrix.end() && (val > 1 && val < 4)) {
        nextGen[key] = 1;
      }
      if (this->sMatrix.find(key) == this->sMatrix.end() && val == 3) {
        nextGen[key] = 1;
      }
    }
  } else {
    // After 13 cycles coordinates seem to be automatically removed from smatrix?? WHY?!
    // It is because val increases exponentially, and not enough bits to encode it eventually
    // Need a better way of doing this
    for (auto const &[key, val] : this->sMatrix) {
    
      if(noNeighs.find(key) == noNeighs.end()) {
        noNeighs[key] = val;
      }
    
      std::vector<coor> myNeighs = mooreNieghbourhood(key, this->width, this->height);
      for (coor n : myNeighs) {
        if(noNeighs.find(n) == noNeighs.end()) {
          noNeighs[n] = val;
        } else {
          noNeighs[n] += val;
        }
      }
    }
  
    for (auto const &[key, val] : noNeighs) {
      // Here we filter cells based on the added stability of its neighbours. If this is high enough it overcomes entropic destability. There is no 'too stable' individual
      if (this->sMatrix.find(key) != this->sMatrix.end() && (val > 4)) {
        nextGen[key] = val;
      }
      //Birth occurs when above entropic destability too
      if (this->sMatrix.find(key) == this->sMatrix.end() && val > 15) {
        nextGen[key] = rand() % 21 - 10;
      }
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


  sMatrix = nextGen;
  coor c = {0, 0}; 
  std::cout << "(0,0)" << "has value of" << sMatrix.find(c)->second << std::endl;
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
