#ifndef GAME_H
#define GAME_H

#include "datastructs.h"
#include <map>

using mymap = std::map<coor, int>;


class Game {
  public:
    int height, width;
    const int size;
    char entropicLiving;
    LinkedList *llist = new LinkedList();
    mymap sMatrix;
    std::vector<coor> aliveCoors;
    Game (int y, int x, char entropic); 
    ~Game() {delete llist;}
    void randomiseBoardLL();
    void randomiseBoardSM();
    std::vector<coor> neighbours(coor c);
    mymap currentLive();
    bool inField (int x, int y, int w, int h);
    std::vector<coor> mooreNieghbourhood(coor c, unsigned int width, unsigned int height) ;
};

#endif
