/**********************************************************************
File Name: Sprout.h
Author: Chris Wills & Ryan Allen                           Date: 6/5/07
File Purpose: Header file for the Sprout Class
Description: Defines the Sprout Class
Problems: Clicking on nodes not fully implemented
**********************************************************************/
#pragma once

#include "draw.h"
#include "SDL_ttf.h"

class Game;

//The frames per second
const int FRAMES_PER_SECOND = 10;

//The dimenstions for the node
const int NODE_WIDTH = 30;
const int NODE_HEIGHT = 30;

//status of the mouse
const int MOUSE_NORMAL = 0;
const int MOUSE_OVER = 1;
const int MOUSE_CLICK = 2;

#define SPROUT_RADIUS 12

struct SproutClips
{
  SDL_Rect clipsGreen[ 14 ];
  SDL_Rect clipsYellow[ 14 ];
  SDL_Rect clipsRed[ 14 ];
  SDL_Rect clipBlack[ 1 ];
  SDL_Surface *anime;
  SDL_Surface *click;
  TTF_Font * font;
};

class Sprout
{
    private:
    int frame;                                          //Its current frame
    int ticks;
    int color;

    int status;                                         //Its animation status

    SproutClips * clips;                                //The clips/image for the sprout

    int sproutNumber;                                   //The identifier of the sprout
    SDL_Surface * number;                               // The Surface that will hold the rendered Number

    void renderNumber(void);                            // Renders the text for the number of the node
    bool available(int x, int y, int from, int to, Sprout ** sprouts);    // Checks to see if the given (x,y) is not over another sprout
    bool willOverlap(int x, int y);                     // Checks to see if this node will overlap with a node at (x,y)

		Game *parent;

    public:
    SDL_Rect node;
    //Initializes the variables
    Sprout(SproutClips * theClips, Sprout ** sprouts, Game *game);            // Generic everything is randomized
    Sprout(int num, int x, int y, SproutClips * theClips);          // Set the (x,y) to the given and set up as a 2 connection sprout
    Sprout(int num, int from, int to, SproutClips * theClips, Sprout ** sprouts, Game *game);   // Sets the number and randoms the rest
    Sprout(Sprout * current);                                     // duplicate the currnt Sprout to the new sprout
    ~Sprout();                                                    // Generic Destructor
    //Sprout(int x, int y, int num, SproutClips * theClips);        // Set x and y coords of sprout plus its number
    //Sprout(int num, int firstNode, int secondNode, SproutClips* theClips);    // Sets the number and calculates the x and y based on its connections to the other nodes

    // State functions
    int   getState();                                   // Returns the state
    void  setState(int);                                //sets the status
    Point getPoint();                                   // Returns the location point
    void  setPoint(int x, int y);                       // Returns the location point

    //Handles input
    bool isMouseOver(int x, int y);

    // Disply Functions
    void hover(SDL_Surface * destination);              //Shows the hover
    void click(SDL_Surface * destination);              //Shows the click
    void show(SDL_Surface * destination);               //Shows the node
    void draw(SDL_Surface * destination);               // Calls the correct drawing function based on the stat
    void addConnection(void);                           // Changes the color based on the number of connections
    void removeConnection(void);                        // Changes the color based on the number of
    int  getConnections(void);                          // returns the number of connections
};
