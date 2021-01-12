#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_ttf.h>
#include <algorithm>
#include "Visual.h"

//allow user to change this
const int WIDTH_OF_GAME = 100;
const int HEIGHT_OF_GAME = 100;


SDL_Color fColor = {255, 0, 255};
SDL_Rect textureRect = {WIDTH_OF_GAME - 7, 0, 6, 6};


Visual::Visual(bool randStart, char entropicLiving) {

  //Allow user to change how dense starting board is
  this->lifeGame = new Game(WIDTH_OF_GAME, HEIGHT_OF_GAME, entropicLiving);
  

  if(randStart)
    this->lifeGame->randomiseBoardSM();
  
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    std::cout << "error initalising SDL: " << SDL_GetError() << '\n';
  }
  win = SDL_CreateWindow("Let life live",
                                      SDL_WINDOWPOS_CENTERED,
                                      SDL_WINDOWPOS_CENTERED,
                                      WIDTH_OF_GAME*10, HEIGHT_OF_GAME*10, 0);

  Uint32 render_flags = SDL_RENDERER_ACCELERATED;
  rend = SDL_CreateRenderer(win, -1, render_flags);
  SDL_RenderSetScale(rend, 10, 10); 

  if (TTF_Init() < 0) {
    std::cout << "error with ttf" << SDL_GetError() << '\n';
  }

}


void Visual::run() {

  TTF_Font *font = TTF_OpenFont("/usr/share/fonts/truetype/ubuntu/UbuntuMono-R.ttf", 28);
  bool pause = false;
  SDL_Event event;
  while (event.type != SDL_QUIT) {
    SDL_Surface *frameTxt = TTF_RenderText_Solid(font, std::to_string(frameNo).c_str(), fColor);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(rend, frameTxt);
    while (SDL_PollEvent(&event)) {
      // Here we will check if user has clicked on a cell, if there is a cell there remove, if not then add (also let user hold down click and draw 
      // Need to pause the run allow user to draw, space bar pauses run, user draws and it is rendered then space to play
      if (event.type == SDL_KEYDOWN) {
        if (event.key.keysym.scancode == SDL_SCANCODE_SPACE) {
          pause = true;
          while(pause) {
          //print pause on screen
          pause = alterGame();
          SDL_SetWindowTitle(win, "Let life live");
          }
        }
      }
    }
    
    int noLiving = this->lifeGame->sMatrix.size();
    SDL_Rect rect[noLiving];
    
    int i = 0;
    for (auto const &[key, val] : this->lifeGame->sMatrix) {
      rect[i].w = 1;
      rect[i].h = 1;
      rect[i].x = key.rowPos;
      rect[i].y = key.colPos;
      ++i;
    }
    SDL_SetRenderDrawColor(rend, 255, 255, 0, 255);
    SDL_RenderClear(this->rend);
    
    SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);
    SDL_RenderDrawRects(this->rend, rect, noLiving);
    SDL_RenderFillRects(this->rend, rect, noLiving);
    SDL_RenderCopy(rend, texture, NULL, &textureRect);

    this->lifeGame->currentLive();

    SDL_RenderPresent(rend);
    SDL_Delay(80000/100);
    ++frameNo;
  }

  TTF_Quit();
  SDL_DestroyRenderer(this->rend);
  SDL_DestroyWindow(this->win);
}


//Allow user to set up own starting board
//And allow user to add cells during current runs
bool Visual::alterGame() {

  TTF_Font *font = TTF_OpenFont("/usr/share/fonts/truetype/ubuntu/UbuntuMono-R.ttf", 28);
  SDL_SetWindowTitle(win, "Paused");
  SDL_Event event;
  bool draw = false;
  mymap newCells, removedCells;
  while (event.key.keysym.scancode != SDL_SCANCODE_RETURN) {
    SDL_Surface *frameTxt = TTF_RenderText_Solid(font, std::to_string(frameNo).c_str(), fColor);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(rend, frameTxt);
    while (SDL_PollEvent(&event)) {
      coor newCell;
      if (event.type == SDL_MOUSEBUTTONDOWN || draw) {
        draw = true;
        int x, y;
        SDL_GetMouseState(&x, &y);
        newCell.rowPos = x/10;
        newCell.colPos = y/10;
      }
      if (event.button.button == SDL_BUTTON_LEFT)
        newCells[newCell] = rand() % 21 - 10;
      else if (event.button.button == SDL_BUTTON_RIGHT)
        removedCells[newCell] = 0;
      
      if (event.type == SDL_MOUSEBUTTONUP) 
        draw = false;

      if (event.key.keysym.scancode == SDL_SCANCODE_C) {
        this->lifeGame->sMatrix.clear();
        frameNo = 1;
      }
    }

    this->lifeGame->sMatrix.merge(newCells);
    //Here we want to remove intersection between sMatrix and removedCells

    int noLiving = this->lifeGame->sMatrix.size();
    SDL_Rect rect[noLiving];
    
    int i = 0;
    for (auto const &[key, val] : this->lifeGame->sMatrix) {
      rect[i].w = 1;
      rect[i].h = 1;
      rect[i].x = key.rowPos;
      rect[i].y = key.colPos;
      ++i;
    }
    SDL_SetRenderDrawColor(rend, 255, 255, 0, 255);
    SDL_RenderClear(this->rend);
    
    SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);
    SDL_RenderDrawRects(this->rend, rect, noLiving);
    SDL_RenderFillRects(this->rend, rect, noLiving);

    SDL_RenderPresent(rend);
    SDL_Delay(800/100);
  }

  return false;
}


