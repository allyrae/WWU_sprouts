#include "stdafx.h"
#include "include/button.h"
#include "include/draw.h"
#include "SDL_gfxPrimitives.h"

#define BUFFER 5      // The extra edge for the box

//Constructor
Button::Button(Point placement, std::string textString, TTF_Font * theFont)
{
  // Probably should verify these before applying them
  point.x = placement.x;
  point.y = placement.y;

  state = B_STATE_NORMAL;  // Set the intial state to be normal

  SDL_Color textColor = {0,0,0};

  font = theFont;

  text = TTF_RenderText_Blended( font, textString.c_str(), textColor);

  // Everything initialized
}

//Destructor
Button::~Button(void)
{
	SDL_FreeSurface(text);
}

// Sets the state of the button to the new state
bool Button::setState(ButtonState newState)
{
  if (state != newState)
  {
    state = newState;
    return true;
  }
  else
  {
    return false;
  }
}

// Gets the current button state
ButtonState Button::getState()
{
  return state;
}

// Tells if the given xy buttons are over the button
bool Button::isMouseover(int x, int y)
{
  // Check that the x is over the button
  if (x >= point.x-BUFFER && x <= point.x + text->clip_rect.w+BUFFER)
    if (y >= point.y-BUFFER && y <= point.y + text->clip_rect.h+BUFFER)    // Check that y is also
      return true;  // It is between both so return true;
    else
      return false;   // Y is not between
  else
    return false;     // x is not between
}

// Draws the button based on the state given
bool Button::draw(SDL_Surface* dest)
{
  // Ouput a box with text in the middle
  Sint16 x1 = point.x-BUFFER;
  Sint16 x2 = point.x + text->clip_rect.w+BUFFER;
  Sint16 y1 = point.y-BUFFER;
  Sint16 y2 = point.y + text->clip_rect.h+BUFFER;

  boxRGBA(dest, x1, y1, x2, y2, 255,255,255,150);
  rectangleRGBA(dest, x1, y1, x2, y2, 0,0,0,255);

  apply_surface( point.x, point.y, text, dest, NULL);

  // Might want to check if destination is valid
  //apply_surface(location.x, location.y, image, destination, &clips[state]);

  // It was succesful
  return true;
}

// Moves the button to the requested (x,y) coordinates
bool Button::moveTo(int x, int y)
{
  if (x >= 0 && x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT)
  {
    point.x = x;
    point.y = y;
    return true;
  }
  else
  {
    return false;
  }
}
