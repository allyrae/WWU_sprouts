#include "stdafx.h"

#include "include/Sprout.h"
#include "include/bezier.h"


int Game::checkMoveState()
{
	return gameWinState;
}

int Game::numberNodes()
{
	return nodeNumbers;
}

int Game::playerTurn()
{
	return turn;
}

int Game::checkWin()
{
	int win = 1;  //initializes 'win' to player one
	std::list<std::string>moveable;
	moveable = possibleMoves();
		if (moveable.empty())
		{
			if (!mesier)
			{
			if (turn)//if the second player won
				win++;//increment win to reflect that
			}
			if (mesier)
			{
			if (!turn)//if the second player won
				win++;//increment win to reflect that
			}
			return win;
		}
	else return 0;
}
std::list<std::string> Game::possibleMoves()
{
	std::string moves;
	std::list<std::string> possmoves;
	for (int i = 0; connectable[i][i]>-1;i++)
	{
		if(connectable[i][i]!=3)
		{
			for (int j = 0; connectable[j][j]>-1; j++)
			{
				if (j>i)
				{
					if (connectable[i][j]!=0)
					{
						if (connectable[j][j]<3)
						{
						moves+= j;
						moves+="(";
						moves+=(nodeNumbers+1);
						moves+=")";
						moves+=i;
						}

					}
				}
				else if (i>j)
				{
					if (connectable[j][i]!=0)
					{
						if (connectable[j][j]<3)
						{
						moves+= j;
						moves+="(";
						moves+=(nodeNumbers+1);
						moves+=")";
						moves+=i;
						}
					}
				}
			}
		possmoves.push_front(moves);
		}
	}

	return possmoves;
}
