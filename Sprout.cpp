/**********************************************************************
File Name: Sprout.cpp
Author: Ryan Allen & Chris Wills                           Date: 6/5/07
File Purpose: The Sprout Class Functions
Description: The Sprout Class implementation
Problems: Clicking on nodes not fully implemented
**********************************************************************/
#include "stdafx.h"

#include <cmath>

#include "include/game.h"
#include "include/Sprout.h"
#include "SDL_ttf.h"

//Takes game and creates random node with # 0
Sprout::Sprout(SproutClips * theClips, Sprout ** sprouts, Game *game)
{
  this->parent = game;

  //Initialize movement variables
  node.x = rand()%(SCREEN_WIDTH - NODE_WIDTH) + NODE_WIDTH/2;
  node.y = rand()%(SCREEN_HEIGHT - NODE_HEIGHT-25) + NODE_HEIGHT/2+25;

  node.w = NODE_WIDTH;
  node.h = NODE_HEIGHT;

  clips = theClips;

  //Initialize animation variables
  frame = 0;
  status = MOUSE_NORMAL;
  color = 0;

  sproutNumber = 0;
  renderNumber();
}
Sprout::Sprout(int num, int x, int y, SproutClips * theClips)  // Sprout constructor for mouse moving new sprout
{
  //Initialize movement variables
  node.x = x;
  node.y = y;

  node.w = NODE_WIDTH;
  node.h = NODE_HEIGHT;

  clips = theClips;

  //Initialize animation variables
  frame = 0;
  status = MOUSE_NORMAL;
  color = 2;

  sproutNumber = num;
  renderNumber();
}

//creates node with assigned number
Sprout::Sprout(int num, int from, int to, SproutClips * theClips, Sprout ** sprouts, Game *game)
{
  sproutNumber = num;

  this->parent = game;

  do
  {
    node.x = rand()%(SCREEN_WIDTH - NODE_WIDTH) + NODE_WIDTH/2;
    node.y = rand()%(SCREEN_HEIGHT - NODE_HEIGHT-25) + NODE_HEIGHT/2+25;
  }  while (!available(node.x, node.y, from, to, sprouts));

  node.w = NODE_WIDTH;
  node.h = NODE_HEIGHT;

  clips = theClips;

  frame = 0;
  status = MOUSE_NORMAL;
  color = 0;

  renderNumber();
}

//copy of sprout for AI purposes
Sprout::Sprout(Sprout * c)
{
  // Need to be completed
  sproutNumber = c->sproutNumber;
  this->parent = c->parent;
  node.x = c->node.x;
  node.y = c->node.y;
  node.h = c->node.h;
  node.w = c->node.w;
  clips = c->clips;
  frame = 0;
  status = MOUSE_NORMAL;
  color = 0;
  number = c->number;
}

//print node's number on sprout
void Sprout::renderNumber()
{
  SDL_Color textColor = {255,255,255};
  char temp[4];
  sprintf(temp,"%d",sproutNumber+1);
  number = TTF_RenderText_Blended( clips->font, temp, textColor);
  if(number == NULL)
  {
    std::cout << "Error Not rendering text" << std::endl;
  }
}

//chose which sprout state to draw by how mouse is interacting with it
void Sprout::draw(SDL_Surface * dest)
{
  if (SDL_GetTicks()-ticks > 1000/15)
  {
    frame++;
    ticks += 1000/15;
  }

  switch (status)
  {
    case MOUSE_NORMAL:  show(dest);     break;
    case MOUSE_OVER:    hover(dest);    break;
    case MOUSE_CLICK:   click(dest);  break;
  }
  if (sproutNumber < 9)
    apply_surface(node.x-5,node.y-9,number,dest,NULL);
  else
    apply_surface(node.x-10,node.y-9,number,dest,NULL);
}

//draw standard sprout
void Sprout::show(SDL_Surface * dest)
{
     if (color==0)
        apply_surface(node.x-NODE_WIDTH/2, node.y-NODE_HEIGHT/2, clips->anime, dest, &clips->clipsGreen[0]);
     else if (color==1)
        apply_surface(node.x-NODE_WIDTH/2, node.y-NODE_HEIGHT/2, clips->anime, dest, &clips->clipsYellow[0]);
     else if (color==2)
        apply_surface(node.x-NODE_WIDTH/2, node.y-NODE_HEIGHT/2, clips->anime, dest, &clips->clipsRed[0]);
     else
        apply_surface(node.x-NODE_WIDTH/2, node.y-NODE_HEIGHT/2, clips->anime, dest, &clips->clipBlack[0]);
}

//draw sprout for when mouse hovers over it
void Sprout::hover(SDL_Surface * dest)
{
  //Loop the animation
  if( frame >= 7 )
  {
    frame = 1;
  }
  //Show the function
  if( color==0 )
    apply_surface(node.x-NODE_WIDTH/2, node.y-NODE_HEIGHT/2, clips->anime, dest, &clips->clipsGreen[frame]);
  else if( color==1 )
    apply_surface(node.x-NODE_WIDTH/2, node.y-NODE_HEIGHT/2, clips->anime, dest, &clips->clipsYellow[ frame ] );
  else if( color==2 )
    apply_surface(node.x-NODE_WIDTH/2, node.y-NODE_HEIGHT/2, clips->anime, dest, &clips->clipsRed[ frame ] );
  else
    apply_surface(node.x-NODE_WIDTH/2, node.y-NODE_HEIGHT/2, clips->anime, dest, &clips->clipBlack[0]);
}

//draw sprout for when mouse clicks on it
void Sprout::click(SDL_Surface * dest)
{
  if( frame >= 8 )
  {
    frame = 1;
    color++;
    setState(MOUSE_OVER);
  }
  if( color==0 )
    apply_surface(node.x-NODE_WIDTH/2, node.y-NODE_HEIGHT/2, clips->click, dest, &clips->clipsGreen[frame]);
  if( color==1 )
    apply_surface(node.x-NODE_WIDTH/2, node.y-NODE_HEIGHT/2, clips->click, dest, &clips->clipsYellow[frame] );
  if( color==2 )
    apply_surface(node.x-NODE_WIDTH/2, node.y-NODE_HEIGHT/2, clips->click, dest, &clips->clipsRed[frame] );
  if( color == 3 )
    apply_surface(node.x-NODE_WIDTH/2, node.y-NODE_HEIGHT/2, clips->click, dest, &clips->clipBlack[0]);
 }

//makes sure status is valid, and sets to given (mouse states)
void Sprout::setState(int newState)
{
  if (status == MOUSE_NORMAL && newState == MOUSE_OVER)
  {
    ticks = SDL_GetTicks();
  }
  if (newState == MOUSE_CLICK)
  {
    frame = 1;
    if (color < 3)
      status = MOUSE_CLICK;
  }
  else
    if (newState < 0 || newState > 2)
      status = MOUSE_NORMAL;
    else
      status = newState;
}

//returns mouse status
int Sprout::getState()
{
  return status;
}
// Returns the point where the node is located
Point Sprout::getPoint()
{
  Point temp;
  temp.x = node.x;
  temp.y = node.y;
  return temp;
}
// Sets the (x,y) of the node
void Sprout::setPoint(int x, int y)
{
  node.x = x;
  node.y = y;
}
//checks if mouse is hovering over a sprout
bool Sprout::isMouseOver(int x, int y)
{
  double dist = sqrt((pow(double(x-node.x),2)+pow(double(y-node.y),2)));
  if (dist >= SPROUT_RADIUS)
    return false;
  else
    return true;
}

//Checks to see if the given xy is not over another sprout
bool Sprout::available(int x, int y, int from, int to, Sprout ** sprouts)
{
  //std::cout << "checking for ("<<x<<","<<y<<")"<< std::endl;
  // Loop over all the sprouts and check if the (x,y) given is covered
  int i = 0;
  while (sprouts[i] != NULL)
  {
    //std::cout << "Checking sprout #"<<i<< std::endl;
    if (sprouts[i]->willOverlap(x,y))
    {
      return false; // The (x,y) is not available
    }else if(from != -1 && to != -1){ //The point isn't on top of another, but we want to check if lines collide.
      // Following Code till end of if written by Brian
      double from_slope = 0; //Temp variables.
      double to_slope = 0;
      double from_intercept = 0;
      double to_intercept = 0;
      double temp_slope = 0; //More temp variables.
      double temp_intercept = 0;
      double poi_x_from = 0; //Temp variables for point of intersection (poi)
      double poi_y_from = 0;
      double poi_x_to = 0;
      double poi_y_to = 0;

      if(sprouts[from]->node.x - x == 0) //If we have division by zero we want to just set it to a small number.
        from_slope = .00001;
      else //No division by zero.
        from_slope = (sprouts[from]->node.y - y) / (sprouts[from]->node.x - x); //Calculate slope for the line to the initial node.

      from_intercept = (from_slope * (x * -1)) + y; //Calculate intercept using point-slope form.

      if(sprouts[to]->node.x - x == 0) //Division by zero check.
        to_slope = .00001;
      else
        to_slope = (sprouts[to]->node.y - y) / (sprouts[to]->node.x - x); //Calculate slope for line to the To node.

      to_intercept = (to_slope * (x * -1)) + y; //Calculcate intercept.

      for(int j = 0; j < 4 * this->parent->count; j++) //Now we check all the Beziers...
      {
        for(int k = 0; k < 4 * this->parent->count; k++)
        {
          temp_slope = 0; //Reset variables.
          temp_intercept = 0;
          poi_x_from = 0;
          poi_y_from = 0;
          poi_x_to = 0;
          poi_y_to = 0;

          if(this->parent->connection[j][k] != NULL) //If we found a bezier then we need to see if there is a collision.
          {
            if(sprouts[j]->node.x - sprouts[k]->node.x == 0) //Division by zero check.
              temp_slope = .00001;
            else
              temp_slope = (sprouts[j]->node.y - sprouts[k]->node.y) / (sprouts[j]->node.x - sprouts[k]->node.x); //Calculate slope of bezier.

            temp_intercept = (temp_slope * (sprouts[j]->node.x * -1)) + sprouts[j]->node.y; //Calculate intercept.

            if(temp_slope - from_slope == 0) //Another division by zero check.
              poi_x_from = .00001;
            else
              poi_x_from = (from_intercept - temp_intercept) / (temp_slope - from_slope); //POI x is line1 intercept - line2 intercept / line2 slope - line1 slope.

            poi_y_from = (from_slope * poi_x_from) + from_intercept; //POI y is line1 slope * POI x + line1 intercept.

            if(temp_slope - to_slope == 0) //Repeat for line to To.
              poi_x_to = .00001;
            else
              poi_x_to = (to_intercept - temp_intercept) / (temp_slope - to_slope);

            poi_y_to = (to_slope * poi_x_to) + to_intercept;

            //Now we have coordinates for point of intersection of the Bezier and both To and From lines.  We just need to see if the endpoints overlap the POI and we can say that space isn't available.
            //std::cout << "From(" << from << ") to Bezier(" << j << "," << k << ") intercepts at (" << poi_x_from << "," << poi_y_from << ")" << std::endl;
            //std::cout << "To(" << to << ") to Bezier(" << j << "," << k << ") intercepts at (" << poi_x_to << "," << poi_y_to << ")" << std::endl;
          }
        }
      }
    }
    i++;
  }
  return true; // The (x,y) is available
}

//what to do if new sprout overlaps a previous one
bool Sprout::willOverlap(int x, int y)
{
  double dist = sqrt((pow(double(x-node.x),2)+pow(double(y-node.y),2)));
  if (dist >= SPROUT_RADIUS*2)
    return false;
  else
    return true;
}

//change colors by number of connections
void Sprout::addConnection(void)
{
  color++;
}

//change colors by number of connections
void Sprout::removeConnection(void)
{
  if (color > 0)
    color--;
}
// Returns the number of connections
int Sprout::getConnections(void)
{
  return color;
}
// Destructer
Sprout::~Sprout()
{
  // Free memory
  SDL_FreeSurface(number);
}
