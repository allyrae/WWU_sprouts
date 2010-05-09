#include "stdafx.h"
#include <stack>
#include <math.h>
#include "include/game.h"

/*
General idea for encapsulated node error checking algorithm
(always assume there is only one region; if multiple regions are being encircled, only check the external nodes in each internal region)
1. start at the first node
2. make sure that every node connected to it is in the list
3. go on to the next node
4. if you find that all the nodes aren't in the list, return an error
5. else, the move is fine
*/
/*bool Game::validateRegion(std::list<int>*encap)
{
	std::cout<<"Meh";
	short didFind = 0;
	bool found = 1;
	for (std::list<int>::iterator iterTo = encap->begin(); iterTo!=encap->end();iterTo++)
	{
		for (int i = 0; connectable[i][i]>-1;i++)
		{
			if ((*iterTo)>i)
			{
				std::cout<<"Gets here"<<std::endl;
				if(connectable[(*iterTo)][i])
				{
					didFind = 0;
					for(std::list<int>::iterator iterFind = encap->begin(); iterFind!=encap->end();iterFind++)
					{
					if ((*iterFind)==i)
						{
							std::cout<<"Connection found between"<<(*iterFind)<<" and "<<(*iterTo)<<"\n";
							didFind = 1;
						}
					}
					std::cout<<didFind<<"\n";
					if(!didFind)
					{
						return false;
					}
				}
			}
			if ((*iterTo)<i)
			{
				std::cout<<"Gets here"<<std::endl;
				if(connectable[i][(*iterTo)])
				{
					didFind = 0;
					for(std::list<int>::iterator iterFind = encap->begin(); iterFind!=encap->end();iterFind++)
					{
					if ((*iterFind)!=i)
						{
							std::cout<<"Connection found between"<<(*iterFind)<<" and "<<(*iterTo)<<"\n";
							didFind = 1;
						}
					}
					std::cout<<didFind<<"\n";
					if(!didFind)
					{
						return false;
					}
				}
			}
		}
	}
	return found;
}*/
//Parsemove: Accepts a move (character array) and references to variables to be filled.
int Game::parsemove(char *move, int *from, int *to, int *creates, int *near, bool *clockwise, std::list<int> *encap){
	std::stack<int> stk; //A temporary stack of ints for parsing purposes.
	int z = 0, c = 0, error = 0, prev = 0; //Temporary ints.

	for(int i = 0; move[i] != '\0'; i++) //Loop until we find a null character.
	{
    //Ok, we want to enstack numbers or, if we are inside the [] that denote enregioned nodes, - and ,
		if((move[i] >= '0' && move[i] <= '9') || ((*from) != -1 && (*to) != -1 && (*creates) != -1 && (move[i] == '-' || move[i] == ',')))
		{
			if(move[i] == '-') //If it is a - we put -1 on the stack (it is an int stack).
				stk.push(-1);
			else if(move[i] == ',') //If it is a , we put -2.
				stk.push(-2);
			else //If it is a number we put that.
				stk.push(move[i] - '0'); //Subtracting '0' will turn a char of a digit into its int equivalent.
		}else{ //Now we check for control characters ( ()@![] ).
			c = z = 0; //Set out temp variables to 0.
			if(move[i] == '(') //If we find a ( then we know the digits on the stack are the "from" number.
			{
				while(stk.size() > 0) //Loop until stack is empty.
				{
					z += int(stk.top() * (pow(10.0, c))); //Take the number on the stack and add it * 10^c to z (this maintains digit position).
					stk.pop(); //Remove from stack.
					c++; //Increase place holder.
				}
				(*from) = z-1; //When we are done we set the from variable to the resultant number.
			}else if(move[i] == ')'){ //If we encounter ) then we know the last number if either creates or near.
				while(stk.size() > 0)
				{
					z += int(stk.top() * (pow(10.0, c)));
					stk.pop();
					c++;
				}

        //If we already have a creates then it must be near.
				if((*creates) != -1)
					(*near) = z-1;
				else //Guess it was creates.
					(*creates) = z-1;

			}else if(move[i] == '@'){ //If we have a @ we need to set creates.
				while(stk.size() > 0)
				{
					z += int(stk.top() * (pow(10.0, c)));
					stk.pop();
					c++;
				}
				(*creates) = z; //Set creates.
			}else if(move[i] == '[' && (*to) == -1){ //If we find a [ we need to set to.
				while(stk.size() > 0)
				{
					z += int(stk.top() * (pow(10.0, c)));
					stk.pop();
					c++;
				}
				(*to) = z-1; //Set to.
			}else if(move[i] == ']'){ //If we have a ] then we need to deal with listing the encapsulated nodes.
				while(stk.size() > 0) //Loop until the stack is empty.
				{
					z = c = 0; //Set temps to 0.
					while(stk.size() > 0 && stk.top() != -1 && stk.top() != -2) //Ok, we need to pop off digits but not -1 or -2 because those are our control codes.
					{
						z += int(stk.top() * (pow(10.0, c)));
						stk.pop();
						c++;
					}
					if(stk.size() > 0) //If we emptied the stack we can't use stk.top().
					{
						if(stk.top() == -2){ //See if a -2 (a comma) exists.
							if(prev == 0) //See if we had a range before the comma
							{
								(*encap).push_front(z-1); //If we didn't then we just put z into the list.
							}else{ //If we had a range before the comma.
								for(int j = z; j <= prev; j++) //Loop through the range...
								{
									(*encap).push_back(j-1); //Place each on the list.
								}
								prev = 0; //Get rid of prev to prevent false positives.
							}
							stk.pop(); //Remove the -2 from the stack when we are done.
						}else if(stk.top() == -1){ //Ok we found a -1 (hypen -)
							prev = z; //Set prev to be the current number.
							stk.pop(); //Remove the -1.
						}
					}
				}
				if(prev != 0 && z != 0) //Ok, we got out without any commas but there was a hyphen (or the last argument was a range [7, 1-4]).
				{
					for(int j = z; j <= prev; j++)
					{
							(*encap).push_back(j-1); //Put the range on the list.
					}
					prev = z = 0;
				}else if(z != 0){ //Ok, there was a digit at the end of the list [1-4,7] or such.
					(*encap).push_back(z-1); //Put it on the list.
				}
			}else if(move[i] == '!' && (*from) != -1 && (*creates) != -1){ //Check if we found a ! AFTER to (from and creates are already set)
				(*clockwise) = false; //Set clockwise to false (we are making this move counter clockwise)
				while(stk.size() > 0) //This also means that to has not been recorded yet.
				{
					z += int(stk.top() * (pow(10.0, c)));
					stk.pop();
					c++;
				}
				(*to) = z-1; //Record to.
			}
		}
	}
  z = c = 0; //Now we are out of the stack loop, this is necessary if there is no control code after to...
  while(stk.size() > 0)
  {
		z += int(stk.top() * (pow(10.0, c)));
		stk.pop();
		c++;
  }
	if(z > 0) //If we had something on the stack it MUST be to.
		(*to) = z-1; //Set to.

  encap->sort();
  encap->unique();

  //Below is error checking, this is to be completed later.
  error = 0;

	if((*from) == -1 || (*to) == -1 || (*creates) == -1)
		return(128); //Fatal Error, get out.

  if(connectable[(*from)][(*from)] == -1)
	{
		error += 1 << 0;
    std::cout << std::endl << "From: " << (*from) << std::endl;
	}

	if(connectable[(*to)][(*to)] > 2)
	{
		error += 1 << 1;
    std::cout << std::endl << "To: " << (*to) << " with free connections: " << (3 - connectable[(*to)][(*to)]) << std::endl;
	}

	if(connectable[(*from)][(*from)] > 2)
	{
		error += 1 << 2;
    std::cout << std::endl << "From: " << (*from) << " with free connections: " << (3 - connectable[(*from)][(*from)]) << std::endl;
	}

	if(((*from) != (*to) && get_connected((*from), (*to)) == 0) || ((*from) == (*to) && connectable[(*from)][(*from)] > 1))
	{
		error += 1 << 3;
    std::cout << std::endl << "From to To: " << get_connected((*from), (*to)) << std::endl;
	}

  if((*near) != -1)
  {
	  if((get_connected((*from), (*to)) == 0) || (get_connected((*from), (*to)) == 0) )
	  {
		  error += 1 << 4;
	  }
    std::cout << std::endl << "Near: " << (*near) << std::endl;
  }

  if(connectable[(*creates)][(*creates)] != -1 || connectable[(*creates) - 1][(*creates) - 1] == -1)
  {
    error += 1 << 5;
    std::cout << "Creates: " << (*creates) << " invalid!" << std::endl;
  }

	if((*from) == (*creates) || (*to) == (*creates) || (*near) == (*creates))
	{
		error += 1 << 6;
		std::cout << "Cannot connect a node to created node." << std::endl;
	}


	/*if(!validateRegion(encap))//checks to see if the regions are valid.
	{
		error += 1 << 7;
		std::cout<<"All nodes connected to a region must be in the region."<< std::endl;
	}*/
  //Return error number (0 is success).
	return (error);
}

//when there is an error
void Game::parseerror(int error){
	char errors[8][128]= {
		"From node does not exist!",
		"To node does not exist!",
		"From node has no free connections!",
		"From cannot connect to To!",
		"From and To not connected!",
		"Creates already exists or not next contiguous node!",
		"Trying to connect to a created node in same turn!",
		"Fatal error! From, To, or Creates improperly parsed."
	};

	int j = 0;
	for(int i = 1; i <= 64; i = (i << 1))
	{
		if((i & error) != 0)
			std::cout << errors[j] << std::endl;
		j++;
	}
}
