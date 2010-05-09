#include "stdafx.h"
#include "include/draw.h"
#include "include/LoadingScreen.h"

//Constructor for Loading screen
LoadingScreen::LoadingScreen(void)
{
  folder = "images/loadingscreen/";
  screenname = "loadingscreen000";
  waitname = "loadingwait000";
  ticksStart = SDL_GetTicks();
   frame = 0;
   isWait = true;
   isStart = false;
      char buffer[3];
   for (int i = 0; i < 30; i++)
   {
      if (i >= 9)
         screenname = "loadingscreen00";

      sprintf(buffer, "%d", i+1);
      std::string filename = folder + screenname + buffer +".jpg";
      //std::cout << "Filename String: " << filename << std::endl;
      loadingScreen[i] = load_image(filename);
   }

   for (int i = 20; i < 30; i++)
   {
      if (i >= 9)
         waitname = "loadingwait00";

      sprintf(buffer, "%d", i);
      loadingWait[i-20] = load_image(folder + waitname + buffer + ".jpg");
   }
}

//loading screen while waiting for play to start
void LoadingScreen::PlayWait()
{
   frame = 0;
   isWait = true;
   isStart = false;
   ticksStart = SDL_GetTicks();
}

//loading screen when play starts
void LoadingScreen::PlayStart()
{
   frame = 0;
   isWait = false;
   isStart = true;
   ticksStart = SDL_GetTicks();
}

//draw the loading screen
bool LoadingScreen::draw(SDL_Surface* dest)
{
  int ticks = SDL_GetTicks();
  if (ticks - ticksStart > 1000/30)
  {
    frame++;
    ticksStart += 1000/30;
  }

  if (frame >= 30)
  {
    frame = 0;
    if (!isWait)
    {
      return false;
    }
  }

  if (!isWait)  //while waiting to start
  {
    apply_surface(0,0,loadingScreen[frame],dest,NULL);
  }
  else		//when you press 'begin'
  {
    if (frame >= 10)
    {
      frame = frame % 10;
    }
    apply_surface(0,0,loadingWait[frame],dest,NULL);
  }
  return true;
}
