#pragma once

#include "draw.h"
//#include "../SDL/SDL.h"
#include <string>

//#include "../SDL/SDL_timer.h"



//header for the loading screen
//declaration of the class
class LoadingScreen
{
  private:
    int frame;//declarations of variables
    int ticksStart;
    std::string folder;
    std::string screenname;
    std::string waitname;
    bool isWait, isStart;
    SDL_Surface *loadingScreen[30];
    SDL_Surface *loadingWait[10];
  public:
    LoadingScreen();//constructor
    void PlayWait();//music
    void PlayStart();//music
    bool draw(SDL_Surface* destination);//draws the loading screen

};

