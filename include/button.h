#pragma once

#include "../stdafx.h"

#include "draw.h"
#include <string>
#include "../SDL/SDL_ttf.h"


// Base Class for buttons
// Should include all basic button functionality which can be easliy derived from for specialty buttons
enum ButtonState{B_STATE_NORMAL,
      B_STATE_HOVER,
      B_STATE_PRESSED};

class Button
{
private:
  SDL_Surface * text;              // Where the image is that will need to be clipped

  TTF_Font * font;

  Point point;             // (x,y) location and (w,h) of button

  ButtonState state;              // The current state of the button

public:
  Button(Point placement, std::string textString, TTF_Font * theFont);
  ~Button(void);
  bool setState(ButtonState newState);     // update the state of the button
  ButtonState  getState();                  // Returns the state of the button
  bool isMouseover(int x, int y);   // Tells if the given xy buttons are over the button
  bool draw(SDL_Surface* destination);    // Draws the button based on the state given at the x,y value given
  // Moves the button to the requested (x,y) coordinates
  bool moveTo(int x, int y);
};

