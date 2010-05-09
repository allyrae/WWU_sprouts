#include "stdafx.h"
#include "include/bezier.h"
#include "include/draw.h"
#include "include/textbox.h"
#include <SDL.h>
#include <iostream>
#include <cstdlib>
#include <stdio.h>

//Main Constructor.  Sets up a game by allocating memory.
Game::Game(bool initial_turn, bool mesier_game, int num_nodes, SproutClips * clips){
  this->gameWinState = 0; //Sets the game to no victory
  this->mesier = mesier_game; //Set Mesier.
  this->turn = initial_turn; //Set initial turn.
  this->count = num_nodes; //Set number of nodes.
  nodeNumbers = count; //Tell it how many nodes the game has

  // create the TextBox
  SDL_Color color = {0,0,0};
  Point boxPlace = {205,4};
  text = new TextBox(clips->font, color, TEXTBOX_TYPE_MOVE, boxPlace, this);

  this->sproutClips = clips;

  this->nodes = NULL; //Initialize Node pointer to NULL.
  this->nodes = (Sprout **)malloc(4 * count * sizeof(Sprout*)); //Allocate 4*count Node pointers.

  this->connectable = NULL; //Initialize Connectable.
  this->connectable = (int **)malloc(4 * count * sizeof(int *)); //Allocate 4*count int pointers (first dimension).
  if(this->connectable == NULL) //If it didn't work...
  {
    std::cout << "Out of memory!" << std::endl; //We are out of memory and must quit.
    system("PAUSE");
    exit(0);
  }else{ //It worked...
    for(int i = 0; i < 4 * count; i++) //Now we allocate memory to each pointer allocated before.
    {
      this->connectable[i] = NULL; //Initialize.
      this->connectable[i] = (int *)malloc(4 * count * sizeof(int)); //Allocate 4*count ints to each pointer established before.
      if(this->connectable[i] == NULL) //If one failes we have to quit.
      {
        std::cout << "Out of memory!" << std::endl;
        system("PAUSE");
        exit(0);
      }
    }
  }

  //This is identical to the above, it just allocates Bezier pointers instead of ints.
  this->connection = NULL;
  this->connection = (Bezier ***)malloc(4 * count * sizeof(Bezier **));
  if(this->connection == NULL)
  {
    std::cout << "Out of memory!" << std::endl;
    system("PAUSE");
    exit(0);
  }else{
    for(int i = 0; i < 4 * count; i++)
    {
      this->connection[i] = NULL;
      this->connection[i] = (Bezier **)malloc(4 * count * sizeof(Bezier *));
      if(this->connection[i] == NULL)
      {
        std::cout << "Out of memory!" << std::endl;
        system("PAUSE");
        exit(0);
      }
    }
  }

  //Initialization loop for all allocated arrays.
  for(int i = 0; i < 4 * count; i++) //Loop through rows.
  {
    for(int j = 0; j < 4 * count; j++) //Loop through columns.
    {
      this->connectable[i][j] = -1; //Initialize everything in Connectable to -1.
      this->connection[i][j] = NULL; //Initialize all Bezier pointers to NULL.
    }
    this->nodes[i] = NULL; //Initialize all Node pointers to Null;
  }

  for(int i = 0; i < count; i++)
  {
    for(int j = 0; j < count; j++)
    {
      if(j <= i)
        this->connectable[i][j] = 0;
      else
        this->connectable[i][j] = 1;
    }
    this->nodes[i] = new Sprout(i, -1, -1, sproutClips, nodes, this);
  }
}

//Game copy constructor.  Exactly the same as the main constructor except it copies data from a game reference passed to it.
Game::Game(Game *current){
  this->mesier = current->mesier;
  this->turn = current->turn;
  this->count = current->count;

  text = current->text;

  this->gameWinState = current->gameWinState;
  this->nodes = NULL;
  this->nodes = (Sprout **)malloc(4 * count * sizeof(Sprout *));

  this->connectable = NULL;
  this->connectable = (int **)malloc(4 * count * sizeof(int *));
  if(this->connectable == NULL)
  {
    std::cout << "Out of memory!" << std::endl;
    system("PAUSE");
    exit(0);
  }else{
    for(int i = 0; i < 4 * count; i++)
    {
      this->connectable[i] = NULL;
      this->connectable[i] = (int *)malloc(4 * count * sizeof(int *));
      if(this->connectable[i] == NULL)
      {
        std::cout << "Out of memory!" << std::endl;
        system("PAUSE");
        exit(0);
      }
    }
  }

  this->connection = NULL;
  this->connection = (Bezier ***)malloc(4 * count * sizeof(Bezier *));
  if(this->connection == NULL)
  {
    std::cout << "Out of memory!" << std::endl;
    system("PAUSE");
    exit(0);
  }else{
    for(int i = 0; i < 4 * count; i++)
    {
      this->connection[i] = NULL;
      this->connection[i] = (Bezier **)malloc(4 * count * sizeof(Bezier *));
      if(this->connection[i] == NULL)
      {
        std::cout << "Out of memory!" << std::endl;
        system("PAUSE");
        exit(0);
      }
    }
  }

  for(int i = 0; i < 4 * count; i++)
  {
    for(int j = 0; j < 4 * count; j++)
    {
      this->connectable[i][j] = current->connectable[i][j];
      if(current->connection[i][j] != NULL)
        this->connection[i][j] = new Bezier(current->connection[i][j]);
      else
        this->connection[i][j] = NULL;
    }
    if(current->nodes[i] != NULL)
      //this->nodes[i] = new Sprout(NULL);
      this->nodes[i] = new Sprout(current->nodes[i]);
    else
      this->nodes[i] = NULL;
  }
}

//freeConnections: Count the number of free connections a Node has.
//Input: Node number
//Output: Number of free connections.
int Game::freeConnections(int node){
	int free = 3; //Start with 3 and decrement when we find something.

	for(int i = 0; i < node; i++) //Loop until row = column (divides our half matrix).
	{
		if(connectable[node][i] != -1) //If it is a useable node...
			free -= connectable[node][i]; //Subtract what we find (0, 1, 2, 3).
	}
	for(int i = node + 1; i < 4 * count; i++) //Now loop from row = column + 1 to the end of the matrix.
	{
		if(connectable[i][node] != -1)
			free -= connectable[node][i]; //Subtract what we find.
	}
	return free; //Return the number of free connections.
}

void Game::output_console(void){
  std::cout << "  ";
  int z = 0;

  if(4 * this->count < 10)
    z = 4 * this->count;
  else
    z = 10;

  for(int j = 0; j < z; j++)
    std::cout << j;
  std::cout << std::endl << std::endl;

  for(int i = 0; i < z; i++)
  {
    std::cout << i << " ";
    for(int j = 0; j < z; j++)
    {
      if(this->connectable[i][j] != -1)
        std::cout << this->connectable[i][j];
      else
        std::cout << " ";
    }
    std::cout << std::endl;
  }
}

void Game::output_file(FILE *fle, char *move){
  char buffer[32];
  fputs(move, fle);
  fputs(",", fle);
  for(int j = 0; j < 4 * count; j++)
  {
    sprintf(buffer, "%d", j);
    fputs(buffer, fle);
    fputs(",", fle);
  }

  fputs("\n", fle);

  for(int i = 0; i < 4 * count; i++)
  {
    sprintf(buffer,"%d", i);
    fputs(buffer,fle);
    fputs(",", fle);
    for(int j = 0; j < 4 * count; j++)
    {
      if(this->connectable[i][j] != -1)
      {
        sprintf(buffer, "%d", this->connectable[i][j]);
        fputs(buffer, fle);
      }
      fputs(",", fle);
    }
    fputs("\n", fle);
  }
  fputs("\n", fle);
}

void Game::move(char *move){
  int to = -1, from = -1, creates = -1, near = -1, error = 0;
  bool clockwise = true;
  std::list<int> encap;

  error = this->parsemove(move, &from, &to, &creates, &near, &clockwise, &encap);
	this->parseerror(error);

	std::cout << "Move: " << move << std::endl;
	std::cout << from << " Creates " << creates << " To " << to;
	if(near != -1)
		std::cout << " Near " << near;
	std::cout << std::endl;

	if(error == 0)
    this->applyMove(from, to, creates, encap, clockwise, near);
  else
    std::cout << "Error: " << error << std::endl;
}

int Game::get_connected(int from, int to){
  return connectable[std::min(from, to)][std::max(from, to)];
}

int Game::get_connectable(int from, int to){
  return connectable[std::max(from, to)][std::min(from, to)];
}

//Game destructor.
Game::~Game(void){
  int i = 0;
  // Free the nodes memory
  for (i = 0; nodes[i] != NULL; i++)
    delete nodes[i];

  // Free the bezier memory
  for (int j = 0; j < i; j++)
    for (int k = 0; k < i; k++)
      if (connection[j][k] != NULL)
        delete connection[j][k];

  free(nodes); //Free nodes memory.

  // loop through and free the 2nd dimension memory
  for (i = 0; i < 4*count-1; i++)
  {
    free(connectable[i]);
    free(connection[i]);
  }

  free(connectable); //Free connectable memory.
  free(connection); //Free connection memory.
  delete text; // Free the textbox
}
