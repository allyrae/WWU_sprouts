#include "stdafx.h"
#include "include/draw.h"
#include "include/LoadingScreen.h"

//Constructor for Loading screen
LoadingScreen::LoadingScreen(void)
{
   folder = "images/loadingscreen/";
   screenname = "";
   waitname = "loadingwait000";
   ticksStart = SDL_GetTicks();
   frame = 0;
   isWait = true;
   isStart = false;
   char buffer[3];
   int pic;

   initing = true;

   std::string filename;
   for (int i = 0; i <= 123; i++)
       {
          /*pic=i;
          if (i >= 9)
             pic = i*9;
             /*screenname = "";*/
          sprintf(buffer, "%d", i);
          filename = folder + screenname + buffer +".jpg";
          //std::cout << "Filename String: " << filename << std::endl;
          loadingScreen[i] = load_image(filename);
       }

//   for (int i = 121; i >= 0; i--)
    for (int i = 0; i <= 121; i++)
       {
          sprintf(buffer, "%d", i);
          filename = folder + screenname + buffer +".jpg";
          loadingLoad[121-i] = load_image(filename);
       }

   //waitname = "front";
   //loadingWait[0] = IMG_Load( "images/loadingscreen/front.png" );  /*i-20] = load_image(folder + waitname + buffer + ".jpg");*/
  //sprintf(buffer, "%d", i);
  loadingWait = IMG_Load( "images/loadingscreen/front.png" );
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

    if (frame >= 123)
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
        if( initing )
        {
            apply_surface(0,0,loadingLoad[frame],dest,NULL);
            if( frame == 121 )
                initing = false;
        }
        else
        {
            if (frame >= 10)
            {
                frame = frame % 10;
            }

            apply_surface(0,0,loadingWait,dest,NULL);
        }
    }
  return true;
}
