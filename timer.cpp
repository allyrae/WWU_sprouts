#include "stdafx.h"
#include "SDL.h"
#include "include/timer.h"

//Constructor
Timer::Timer()
{
    //Initialize the variables
    startTicks = 0;
    pausedTicks = 0;
    paused = false;
    started = false;
}

//start timer
void Timer::start()
{
    //Start the timer
    started = true;

    //Unpause the timer
    paused = false;

    //Get the current clock time
    startTicks = SDL_GetTicks();
}

//stop timer
void Timer::stop()
{
    //Stop the timer
    started = false;

    //Unpause the timer
    paused = false;
}

//pause timer
void Timer::pause()
{
    //If the timer is running and isn't already paused
    if( ( started == true ) && ( paused == false ) )
    {
        //Pause the timer
        paused = true;

        //Calculate the paused ticks
        pausedTicks = SDL_GetTicks() - startTicks;
    }
}

//unpause timer
void Timer::unpause()
{
  //If the timer is paused
  if( paused == true )
  {
    //Unpause the timer
    paused = false;

    //Reset the starting ticks
    startTicks = SDL_GetTicks() - pausedTicks;

    //Reset the paused ticks
    pausedTicks = 0;
  }
}

//get ticks if time for timer
int Timer::get_ticks()
{
  //If the timer is running
  if( started == true )
  {
    //If the timer is paused
    if( paused == true )
    {
      //Return the number of ticks when the the timer was paused
      return pausedTicks;
    }
    else
    {
      //Return the current time minus the start time
      return SDL_GetTicks() - startTicks;
    }
  }

  //If the timer isn't running
  return 0;
}

//state: timer is started
bool Timer::is_started()
{
    return started;
}

//state: timer is paused
bool Timer::is_paused()
{
    return paused;
}
