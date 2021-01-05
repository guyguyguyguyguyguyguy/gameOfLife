#ifndef VISUAL_H
#define VISUAL_H


#include "Game.h"
#include <vector> 
#include <SDL2/SDL.h>


class Visual {
  public:
    Game *lifeGame;
    SDL_Renderer* rend;
    SDL_Window* win;
    Visual(bool randStart = true);
    ~Visual() { delete lifeGame; };
    bool alterGame(); 
    mymap mousePress(int x, int y);
    void run();
};


#endif