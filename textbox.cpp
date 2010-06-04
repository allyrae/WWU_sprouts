#include "stdafx.h"
#include "include/textbox.h"
#include "SDL_gfxPrimitives.h"

#define BUFFER 5      // The extra edge for the box

//Constructor
TextBox::TextBox(TTF_Font * theFont, SDL_Color color, TextboxType theType, Point placement, Game * theGame)
{
  game = theGame;
  point.x = placement.x;
  point.y = placement.y;
  cursor = 0;
  state = TEXTBOX_FOCUS;
  ticksStart = SDL_GetTicks();
  font = theFont;
  textString = "Enter move here";
  textColor.r = color.r;
  textColor.g = color.g;
  textColor.b = color.b;
  type = theType;
  changed = true;
  textRender = NULL;
}

//identify presence and value of keypress
bool TextBox::processKeyDown(SDL_Event * event)
{
  if (state == TEXTBOX_FOCUS)
  {
    if (event->type == SDL_KEYDOWN)
    {
      // Return Sends the string to the function
      // and Then clears the string
      if (event->key.keysym.sym == SDLK_RETURN)
      {
        // Send the string to the function
        switch(type)
        {
          case TEXTBOX_TYPE_NUM: // function call here
            break;
          case TEXTBOX_TYPE_MOVE: // function call here
            game->move((char *)textString.c_str());
            break;
        }
        // clear the string
        textString.clear();
        changed = true;
        return true;
      }

      // Backspace - Deletes one char from the end of the string
      if (event->key.keysym.sym == SDLK_BACKSPACE)
      {
        if (textString.length() > 0)
        {
          textString.erase(textString.length()-1,1);
          changed = true;
        }
        return true;
      }

      // Check for SHIFT ones
      if (event->key.keysym.mod & KMOD_SHIFT)
      {
        // Exclamation Point - !
        if (event->key.keysym.sym == SDLK_1)
        {
          textString += SDLK_EXCLAIM;
          changed = true;
          return true;
        }

        // At symbol - @
        if (event->key.keysym.sym == SDLK_2)
        {
          textString += SDLK_AT;
          changed = true;
          return true;
        }

        // Opening Parenthesis - (
        if (event->key.keysym.sym == SDLK_9)
        {
          textString += SDLK_LEFTPAREN;
          changed = true;
          return true;
        }

        // Closing Parenthesis - )
        if (event->key.keysym.sym == SDLK_0)
        {
          textString += SDLK_RIGHTPAREN;
          changed = true;
          return true;
        }

        return false;
      }

      switch (event->key.keysym.sym)
      {
        case SDLK_0:
        case SDLK_1:
        case SDLK_2:
        case SDLK_3:
        case SDLK_4:
        case SDLK_5:
        case SDLK_6:
        case SDLK_7:
        case SDLK_8:
        case SDLK_9:
        case SDLK_LEFTBRACKET:
        case SDLK_RIGHTBRACKET:
        case SDLK_MINUS:
        case SDLK_COMMA:
          textString += event->key.keysym.sym;
          changed = true;
          return true;
          break;
        // Have to do something special for these
        case SDLK_KP0:
        case SDLK_KP1:
        case SDLK_KP2:
        case SDLK_KP3:
        case SDLK_KP4:
        case SDLK_KP5:
        case SDLK_KP6:
        case SDLK_KP7:
        case SDLK_KP8:
        case SDLK_KP9:
          textString += event->key.keysym.sym-208;
          changed = true;
          return true;
          break;
        case SDLK_KP_MINUS:
          textString += SDLK_MINUS;
          changed = true;
          return true;
          break;
      }
    }
  }

  // That should be it will see
  return false;
}

//set state determined by mouse interaction
bool TextBox::setState(TextboxFocus theState)
{
  if (state != theState)
  {
    if (state == TEXTBOX_NO_FOCUS && theState == TEXTBOX_FOCUS)
    {
      textString = "";
      changed = true;
      state = theState;
      ticksStart = SDL_GetTicks();
      return true;
    }
    else if (state == TEXTBOX_FOCUS && theState == TEXTBOX_NO_FOCUS)
    {
      textString = "Enter move here";
      changed = true;
      state = theState;
      return true;
    }
    else
      return false;
  }
  else
    return false;
}

//get mouse state
TextboxFocus TextBox::getState(void)
{
  return state;
}

//draw the textbox
bool TextBox::draw(SDL_Surface * dest)
{
  if (changed)
  {
    //Render the text
    if (textString.length() < 1)
      textRender = TTF_RenderText_Blended( font, " ", textColor);
    else
      textRender = TTF_RenderText_Blended( font, textString.c_str(), textColor);
    changed = false;
  }

  if (textRender == NULL)
  {
    return false;
  }

  /*Sint16 x1 = point.x-BUFFER;
  Sint16 x2 = point.x + textRender->clip_rect.w+BUFFER;
  Sint16 y1 = point.y-BUFFER;
  Sint16 y2 = point.y + textRender->clip_rect.h+BUFFER;

  boxRGBA(destination, x1, y1, x2, y2, 255,255,255,150);
  rectangleRGBA(destination, x1, y1, x2, y2, 0,0,0,255);*/

  apply_surface( point.x, point.y, textRender, dest, NULL);

  if (state == TEXTBOX_FOCUS)
  {
    if (cursor == 1)
    {
      vlineRGBA(dest, point.x + textRender->clip_rect.w, point.y, point.y + textRender->clip_rect.h, 0,0,0,255);
      if (SDL_GetTicks()-ticksStart > 1000/10) // Slow the motion down to 10 fps
      {
        cursor = 0;
        ticksStart += 1000/10;
      }
    }
    else
    {
      if (SDL_GetTicks()-ticksStart > 1000/10) // Slow the motion down to 10 fps
      {
        cursor = 1;
        ticksStart += 1000/10;
      }
    }
  }

  return true;
}

//determine space that is sensitive to mouse
bool TextBox::isMouseover(int x, int y)
{
  if (x < point.x - BUFFER)
   return false;

  if (x > point.x + textRender->clip_rect.w + BUFFER)
    return false;

  if (y < point.y - BUFFER)
    return false;

  if (y > point.y + textRender->clip_rect.h + BUFFER)
    return false;

  // if still here it is over the box
  return true;
}

TextBox::~TextBox()
{
  // Free the memory
  SDL_FreeSurface(textRender);
}
