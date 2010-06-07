// Sprouts2.cpp : Defines the entry point for the console application.

#include <time.h>
#include "stdafx.h"
#include "include/bezier.h"
#include "include/button.h"
#include "include/LoadingScreen.h"
#include "include/Sprout.h"
#include "include/textbox.h"
#include "SDL_ttf.h"

// Define Game States
enum{ GAME_STATE_LOADING = 0,
      GAME_STATE_START,
      GAME_STATE_PLAY,
      GAME_STATE_QUIT};

struct Move
{
  int from;
  int to;
  int creates;
  Sprout * newSprout;
  Bezier * toCurve;
  Bezier * fromCurve;
};

// Temp include here
#include "include/bezier.h"
#include "SDL_ttf.h"
#include "include/textbox.h"
#include "include/Sprout.h"
#include "include/LoadingScreen.h"
#include "include/button.h"

using namespace std;

// Global items needed
// Surfaces
SDL_Surface * screen = NULL;
// The Game State
int gameState;

Game * g; // Main Game object

// Clips for the Sprouts
SproutClips sproutClips;

// Font Stuff
//The font that's going to be used
TTF_Font *font = NULL;

//The event structure that will be used
SDL_Event event;

// End For Sure Globals needed

// More Globals May need may not need
SDL_Surface * temp = NULL;
SDL_Surface * testButton    = NULL;
SDL_Surface * background    = NULL;
SDL_Surface * textPlayer    = NULL;
SDL_Surface * textMesier    = NULL;
SDL_Surface * textStandard  = NULL;
SDL_Surface * textError     = NULL;
SDL_Surface * text1         = NULL;
SDL_Surface * text2         = NULL;

LoadingScreen * loading;
Button * startButton;

Move * move;
// End more globals

void setSproutClips()
{
     //green hover
    sproutClips.clipsGreen[ 0 ].x = 0;
    sproutClips.clipsGreen[ 0 ].y = 0;
    sproutClips.clipsGreen[ 0 ].w = NODE_WIDTH;
    sproutClips.clipsGreen[ 0 ].h = NODE_HEIGHT;

    sproutClips.clipsGreen[ 1 ].x = 30;
    sproutClips.clipsGreen[ 1 ].y = 0;
    sproutClips.clipsGreen[ 1 ].w = NODE_WIDTH;
    sproutClips.clipsGreen[ 1 ].h = NODE_HEIGHT;

    sproutClips.clipsGreen[ 2 ].x = 60;
    sproutClips.clipsGreen[ 2 ].y = 0;
    sproutClips.clipsGreen[ 2 ].w = NODE_WIDTH;
    sproutClips.clipsGreen[ 2 ].h = NODE_HEIGHT;

    sproutClips.clipsGreen[ 3 ].x = 90;
    sproutClips.clipsGreen[ 3 ].y = 0;
    sproutClips.clipsGreen[ 3 ].w = NODE_WIDTH;
    sproutClips.clipsGreen[ 3 ].h = NODE_HEIGHT;

    sproutClips.clipsGreen[ 4 ].x = 120;
    sproutClips.clipsGreen[ 4 ].y = 0;
    sproutClips.clipsGreen[ 4 ].w = NODE_WIDTH;
    sproutClips.clipsGreen[ 4 ].h = NODE_HEIGHT;

    sproutClips.clipsGreen[ 5 ].x = 150;
    sproutClips.clipsGreen[ 5 ].y = 0;
    sproutClips.clipsGreen[ 5 ].w = NODE_WIDTH;
    sproutClips.clipsGreen[ 5 ].h = NODE_HEIGHT;

    sproutClips.clipsGreen[ 6 ].x = 180;
    sproutClips.clipsGreen[ 6 ].y = 0;
    sproutClips.clipsGreen[ 6 ].w = NODE_WIDTH;
    sproutClips.clipsGreen[ 6 ].h = NODE_HEIGHT;

    sproutClips.clipsGreen[ 7 ].x = 210;
    sproutClips.clipsGreen[ 7 ].y = 0;
    sproutClips.clipsGreen[ 7 ].w = NODE_WIDTH;
    sproutClips.clipsGreen[ 7 ].h = NODE_HEIGHT;

    //yellow
    sproutClips.clipsYellow[ 0 ].x = 0;
    sproutClips.clipsYellow[ 0 ].y = 30;
    sproutClips.clipsYellow[ 0 ].w = NODE_WIDTH;
    sproutClips.clipsYellow[ 0 ].h = NODE_HEIGHT;

    sproutClips.clipsYellow[ 1 ].x = 30;
    sproutClips.clipsYellow[ 1 ].y = 30;
    sproutClips.clipsYellow[ 1 ].w = NODE_WIDTH;
    sproutClips.clipsYellow[ 1 ].h = NODE_HEIGHT;

    sproutClips.clipsYellow[ 2 ].x = 60;
    sproutClips.clipsYellow[ 2 ].y = 30;
    sproutClips.clipsYellow[ 2 ].w = NODE_WIDTH;
    sproutClips.clipsYellow[ 2 ].h = NODE_HEIGHT;

    sproutClips.clipsYellow[ 3 ].x = 90;
    sproutClips.clipsYellow[ 3 ].y = 30;
    sproutClips.clipsYellow[ 3 ].w = NODE_WIDTH;
    sproutClips.clipsYellow[ 3 ].h = NODE_HEIGHT;

    sproutClips.clipsYellow[ 4 ].x = 120;
    sproutClips.clipsYellow[ 4 ].y = 30;
    sproutClips.clipsYellow[ 4 ].w = NODE_WIDTH;
    sproutClips.clipsYellow[ 4 ].h = NODE_HEIGHT;

    sproutClips.clipsYellow[ 5 ].x = 150;
    sproutClips.clipsYellow[ 5 ].y = 30;
    sproutClips.clipsYellow[ 5 ].w = NODE_WIDTH;
    sproutClips.clipsYellow[ 5 ].h = NODE_HEIGHT;

    sproutClips.clipsYellow[ 6 ].x = 180;
    sproutClips.clipsYellow[ 6 ].y = 30;
    sproutClips.clipsYellow[ 6 ].w = NODE_WIDTH;
    sproutClips.clipsYellow[ 6 ].h = NODE_HEIGHT;

    sproutClips.clipsYellow[ 7 ].x = 210;
    sproutClips.clipsYellow[ 7 ].y = 30;
    sproutClips.clipsYellow[ 7 ].w = NODE_WIDTH;
    sproutClips.clipsYellow[ 7 ].h = NODE_HEIGHT;

    //red
    sproutClips.clipsRed[ 0 ].x = 0;
    sproutClips.clipsRed[ 0 ].y = 60;
    sproutClips.clipsRed[ 0 ].w = NODE_WIDTH;
    sproutClips.clipsRed[ 0 ].h = NODE_HEIGHT;

    sproutClips.clipsRed[ 1 ].x = 30;
    sproutClips.clipsRed[ 1 ].y = 60;
    sproutClips.clipsRed[ 1 ].w = NODE_WIDTH;
    sproutClips.clipsRed[ 1 ].h = NODE_HEIGHT;

    sproutClips.clipsRed[ 2 ].x = 60;
    sproutClips.clipsRed[ 2 ].y = 60;
    sproutClips.clipsRed[ 2 ].w = NODE_WIDTH;
    sproutClips.clipsRed[ 2 ].h = NODE_HEIGHT;

    sproutClips.clipsRed[ 3 ].x = 90;
    sproutClips.clipsRed[ 3 ].y = 60;
    sproutClips.clipsRed[ 3 ].w = NODE_WIDTH;
    sproutClips.clipsRed[ 3 ].h = NODE_HEIGHT;

    sproutClips.clipsRed[ 4 ].x = 120;
    sproutClips.clipsRed[ 4 ].y = 60;
    sproutClips.clipsRed[ 4 ].w = NODE_WIDTH;
    sproutClips.clipsRed[ 4 ].h = NODE_HEIGHT;

    sproutClips.clipsRed[ 5 ].x = 150;
    sproutClips.clipsRed[ 5 ].y = 60;
    sproutClips.clipsRed[ 5 ].w = NODE_WIDTH;
    sproutClips.clipsRed[ 5 ].h = NODE_HEIGHT;

    sproutClips.clipsRed[ 6 ].x = 180;
    sproutClips.clipsRed[ 6 ].y = 60;
    sproutClips.clipsRed[ 6 ].w = NODE_WIDTH;
    sproutClips.clipsRed[ 6 ].h = NODE_HEIGHT;

    sproutClips.clipsRed[ 7 ].x = 210;
    sproutClips.clipsRed[ 7 ].y = 60;
    sproutClips.clipsRed[ 7 ].w = NODE_WIDTH;
    sproutClips.clipsRed[ 7 ].h = NODE_HEIGHT;

    sproutClips.clipBlack[ 0 ].x = 0;
    sproutClips.clipBlack[ 0 ].y = 90;
    sproutClips.clipBlack[ 0 ].w = NODE_WIDTH;
    sproutClips.clipBlack[ 0 ].h = NODE_HEIGHT;

    sproutClips.font = font;
}

bool init()
{
  // nullify the surfaces
  screen = NULL;
  temp = NULL;
  // initialize the sdl here
  //Initialize all SDL subsystems
  if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
  {
    //return false;
    cout << "Unable to init SDL" << endl;
    return 0;
  }

  //Set up the screen
  screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_HWSURFACE|SDL_DOUBLEBUF );

  //If there was in error in setting up the screen
  if( screen == NULL )
  {
    screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE );
    if (screen == NULL)
    {
      //return false;
      cout << "Unable to setup the Screen" << endl;
      return 0;
    }
  }

  //Initialize SDL_ttf
  if( TTF_Init() == -1 )
  {
    cout << "Unable to Setup Font" << endl;
    return false;
  }

  //Set the window caption
  SDL_WM_SetCaption( "Sprouts", NULL );

  //Load the images
  background = load_image( "images/background.jpg" );

  //Open the font
  font = TTF_OpenFont( "images/cour.ttf", 14 );

  //If there was an error in loading the font
  if( font == NULL )
  {
    cout << "Error loading the font" << endl;
    return false;
  }

  // Set sproutClips
  setSproutClips();   // Must be after the font is set
//  sproutClips.anime = load_image( "images/hover.png" );
//  sproutClips.click = load_image( "images/click.png" );
  sproutClips.anime = IMG_Load( "images/hover.png" );
  sproutClips.click = IMG_Load( "images/click.png" );
sproutClips.font = font;
  if (sproutClips.font == NULL)
  {
    cout << "ERROR:  Invlaid font" << endl;
  }

    if(!sproutClips.anime) {
        printf("IMG_Load: %s\n", IMG_GetError());
        // handle error
    }
    if(!sproutClips.click) {
        printf("IMG_Load2: %s\n", IMG_GetError());
        // handle error
    }

  SDL_SetColorKey( sproutClips.anime, SDL_SRCCOLORKEY, SDL_MapRGB(sproutClips.anime->format, 255,255,255));
  SDL_SetColorKey( sproutClips.click, SDL_SRCCOLORKEY, SDL_MapRGB(sproutClips.click->format, 255,255,255));


  // Render basic Texts Strings
  SDL_Color textColor = {0,0,0};
  textMesier    = TTF_RenderText_Blended( font, "Mesier Game", textColor);
  textStandard  = TTF_RenderText_Blended( font, "Standard Game", textColor);
  textPlayer    = TTF_RenderText_Blended( font, "Player: ", textColor);
  textError     = TTF_RenderText_Blended( font, " ", textColor);
  text1         = TTF_RenderText_Blended( font, "1", textColor);
  text2         = TTF_RenderText_Blended( font, "2", textColor);

  //If everything initialized fine
  //return true;
  cout << "Ready to GO!!" << endl;
  return 1;
}


int drawPlay()  // Draws the GAME_STATE_PLAY stuff
{
  // Draw the background first
  apply_surface(0,0,background,screen,NULL);

  // Draw the box
  boxRGBA(screen,0,0,SCREEN_WIDTH-1,textPlayer->clip_rect.h+8,255,255,255,200);
  rectangleRGBA(screen,0,0,SCREEN_WIDTH-1,textPlayer->clip_rect.h+8,0,0,0,255);

  // Draw player info
  apply_surface(5,4,textPlayer,screen,NULL);
  if (g->playerTurn() == 0)
    apply_surface(5+textPlayer->clip_rect.w,4,text1,screen,NULL);
  else
    apply_surface(5+textPlayer->clip_rect.w,4,text2,screen,NULL);

  // Draw the separator
  vlineRGBA(screen,85,0,textPlayer->clip_rect.h+8,0,0,0,255);

  // Draw the Game state
  if(g->checkMoveState() == 0)
    apply_surface(90,4,textStandard,screen,NULL);
  else
    apply_surface(100,4,textMesier, screen, NULL);

  // Draw the Separator
  vlineRGBA(screen,200,0,textPlayer->clip_rect.h+8,0,0,0,255);

  // Draw the Text input Box
  g->text->draw(screen);  // Draw the Text input box

  // Draw beziers
  int i = 0;
  for (i=0; g->nodes[i] != NULL; i++)
  {
    // do nothing finding the
  }

  if (move != NULL)
  {
    if (move->fromCurve != NULL)
      move->fromCurve->draw(screen);
    if (move->toCurve != NULL)
      move->toCurve->draw(screen);
  }

  for (int j = 0; j <= i; j++)
    for (int k = 0; k <= i; k++)
      if (g->connection[j][k] != NULL)
        g->connection[j][k]->draw(screen);

  // Draw the Sprouts
  i = 0;
  while (g->nodes[i] != NULL)
  {
    g->nodes[i]->draw(screen);
    i++;
  }

  if (move != NULL)
    if (move->newSprout != NULL)
      move->newSprout->draw(screen);

  return 1;
}
int Draw()
{
  // Draw code here

  // Temp drawing code to test it
  //boxRGBA(screen,0,0,SCREEN_WIDTH,SCREEN_HEIGHT,0,200,0,255);

  if (gameState == GAME_STATE_START)
  {
    loading->draw(screen);
    startButton->draw(screen);
  }

  if (gameState == GAME_STATE_LOADING)
  {
    if (!loading->draw(screen))
    {
      gameState = GAME_STATE_PLAY;
    }
  }

  if (gameState == GAME_STATE_PLAY)
  {
    drawPlay();
  }

  //Update the screen
  if( SDL_Flip( screen ) == -1 )
  {
    cout << "unable to flip the screen" << endl;
    return 0;
  }
  return 1;
}

void clearMove(void)
{
  if (move != NULL)
  {
    // set the colors back to normal for the nodes
    if (move->to != -1)
      g->nodes[move->to]->removeConnection();
    if (move->from != -1)
      g->nodes[move->from]->removeConnection();

    // Delete the new objects created
    if (move->toCurve != NULL)
      delete move->toCurve;
    if (move->fromCurve != NULL)
      delete move->fromCurve;
    if (move->newSprout != NULL)
      delete move->newSprout;

    // Set values back to base values
    move->to        = -1;
    move->from      = -1;
    move->toCurve   = NULL;
    move->fromCurve = NULL;
    move->newSprout = NULL;

    for (move->creates = 0; g->nodes[move->creates] != NULL; move->creates++)
    {
      // find the first null node
    }
  }
}

void newGame(bool player, bool mesier, int nodes)
{
  delete g;
  g = new Game(player,mesier,nodes,&sproutClips);
  clearMove();
  if (g == NULL)
  {
    cout << "Error game not created completly" << endl;
  }
}

void sendMove()
{
  // Make sure its a valid move
  if (move != NULL && move->newSprout != NULL)
  {
    char temp[50];
    sprintf(temp,"%d(%d)%d",move->to+1,move->creates+1,move->from+1);
    g->move(temp);
  }
  if (g->nodes[move->creates] != NULL)
  {
    Point temp = move->newSprout->getPoint();
    g->nodes[move->creates]->setPoint(temp.x, temp.y);
    if(g->connection[move->to][move->creates] != NULL)
      g->connection[move->to][move->creates]->adjustCoord(CURVE_START,temp.x,temp.y);
    if(g->connection[move->creates][move->from] != NULL)
      g->connection[move->creates][move->from]->adjustCoord(CURVE_END,temp.x,temp.y);
    clearMove();
  }
}
int main(int argc, char* argv[])
{
  // Seed the Random Generator
  srand((int)time(NULL));

  bool found = false;

  //Set the Program state
  gameState = GAME_STATE_START;  // Menu for now

  // initialize the SDL
  if (init())
  {
    cout << "SDL Started Succesfully" << endl;
  }
  else
  {
    cout << "Failure to Start SDL - Now Quiting" << endl;
    gameState = GAME_STATE_QUIT; // Set the Game state to Quit
  }


  // Temp test SDL Commands
  //sprout = new Sprout(1, &sproutClips);


  loading = new LoadingScreen();
  loading->PlayWait();

  Point startPlace = {355, 375};
  startButton = new Button(startPlace,"Start Game",font);

  g = new Game(false,true,4,&sproutClips);

  move = new Move;
  for (move->creates = 0; g->nodes[move->creates] != NULL; move->creates++)
  {
    // find the first null node
  }
  move->to        = -1;
  move->from      = -1;
  move->toCurve   = NULL;
  move->fromCurve = NULL;
  move->newSprout = NULL;

  if (Draw())
  {
    cout << "Drawing Succesful" << endl;
  }
  else
  {
    cout << "Failure to draw - Now Quiting" << endl;
    gameState = GAME_STATE_QUIT;
  }

  // End Test SDL Commands

  // Main game loop Code
  while(gameState!=GAME_STATE_QUIT)
  {
    Draw();  // In Draw worry about which draw to call  - Depending on state

    //While there's an event to handle
    while( SDL_PollEvent( &event ) )
    {
      //If the user has Xed out the window
      if( event.type == SDL_QUIT )
      {
        //Quit the program
        gameState = GAME_STATE_QUIT;
      }

      if (event.type == SDL_KEYDOWN)
      {
        if (event.key.keysym.sym == SDLK_ESCAPE)
        {
          gameState = GAME_STATE_QUIT;
        }
        if (event.key.keysym.sym == SDLK_F2)
        {
          if (gameState == GAME_STATE_PLAY)
          {
            newGame(true,true,4);
          }
        }
        else
        {
          if (gameState == GAME_STATE_PLAY)
            g->text->processKeyDown(&event);
        }
      }

      if (event.type == SDL_MOUSEMOTION)
      {
        switch(gameState)
        {
          case GAME_STATE_PLAY:
            if (move->toCurve != NULL)
              move->toCurve->setCurve(event.button.x,event.button.y);
            if (move->fromCurve != NULL)
              move->fromCurve->setCurve(event.button.x,event.button.y);
            if (move->newSprout != NULL)
              move->newSprout->setPoint(event.button.x,event.button.y);

            int i = 0;
            while (g->nodes[i] != NULL)
            {
              if (g->nodes[i]->getState() != MOUSE_CLICK)
                if (g->nodes[i]->isMouseOver(event.button.x,event.button.y))
                  g->nodes[i]->setState(MOUSE_OVER);
                else
                  g->nodes[i]->setState(MOUSE_NORMAL);
              i++;
            }
        }
      }

      if (event.type == SDL_MOUSEBUTTONDOWN)
      {
        if (event.button.button == SDL_BUTTON_RIGHT)
        {
          clearMove();
        }
        if (event.button.button == SDL_BUTTON_LEFT)
        {
          int i = 0;
          switch(gameState)
          {
            // We are playing a game
            case GAME_STATE_PLAY:
              found = false;
              if (g->text->isMouseover(event.button.x,event.button.y))
              {
                g->text->setState(TEXTBOX_FOCUS);
                break;
              }
              else
                g->text->setState(TEXTBOX_NO_FOCUS);

              while (g->nodes[i] != NULL)
              {
                if (g->nodes[i]->isMouseOver(event.button.x,event.button.y))
                {
                  if (move->to == -1)
                  {
                    if (g->nodes[i]->getConnections() < 3)
                    {
                      move->to = i;
                      g->nodes[i]->setState(MOUSE_CLICK);
                      move->toCurve = new Bezier(g->nodes[i]->getPoint());
                    }
                  }
                  else if (move->from == -1)
                  {
                    if (g->nodes[i]->getConnections() < 3)
                    {
                      for (move->creates = 0; g->nodes[move->creates] != NULL; move->creates++)
                      {
                        // find the first null node
                      }
                      move->from = i;
                      g->nodes[i]->setState(MOUSE_CLICK);
                      move->fromCurve = new Bezier(g->nodes[i]->getPoint());
                      move->newSprout = new Sprout(move->creates, event.button.x, event.button.y, &sproutClips);
                    }
                  }
                  found = true;
                  break;
                }
                i++;
              }

              // The click is not over any sprouts or the text box
              if (move->newSprout != NULL && !found)
              {
                // Make sure its not on the top bar
                if (event.button.y < 30)
                  break;

                // Should be good to try to create a new move
                sendMove();
              }
              break;
            // It is the start screen
            case GAME_STATE_START:
              if (startButton->isMouseover(event.button.x,event.button.y))
              {
                loading->PlayStart();
                gameState = GAME_STATE_LOADING;
              }
              break;
          }
        }
      }
    }
  }

  return EXIT_SUCCESS;
}

