#pragma once

#include <list>
#include "Sprout.h"

class Bezier; //Prototype Bezier so we can use it here.
class Sprout; //Prototype Node.
class TextBox;
struct SproutClips;  // Prototype struct

class Game{
  private:
    int **connectable; //2D array of ints.
    bool mesier; //Mesier mode?
    bool turn; //Who's turn is it (false = left).
    SproutClips * sproutClips;
	  int gameWinState;
	  int nodeNumbers;
  public:
    int count; //Number of initial nodes in the game.
    Bezier ***connection; //2D array of pointers to Beziers.
    Sprout **nodes; //Array of Node pointers.
    TextBox * text;
    Game(bool, bool, int, SproutClips *); //Main constructor, makes a game with turn, mesier, and number of initial nodes.
    Game(Game *); //Constructor for copying games.
		int freeConnections(int); //Returns the number of connections a node has available to it.
		int parsemove(char *move, int *from, int *to, int *creates, int *near, bool *clockwise, std::list<int> *encap); //Parses a move.
    bool setConnected(std::list<int> toConnect,std::list<int> canConnect);
    int findConnected(int from, int current);
    bool notEnregioned(int node, std::list<int> encapsulated);

    std::list<int> findBorders(int from, int to, int prev,std::list<int>);
    bool applyMove(int from, int to, int creates, std::list<int> encapsulated, bool clockwise, int near);
    void output_console(void);
    void output_file(FILE *, char *);
    void move(char *);
    int get_connectable(int from, int to);
    int get_connected(int from, int to);
	  void parseerror(int error);
	  int checkWin();
    std::list<std::string> possibleMoves();
	  int checkMoveState();
	  int numberNodes();
	  int playerTurn();
	  bool checkRegion(int created, int from, int to);
    ~Game(void); //Destructor for Game.
};

