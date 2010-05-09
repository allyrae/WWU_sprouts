#include "stdafx.h"

#include "include/Sprout.h"
#include "include/bezier.h"
#include <list>


bool Game::setConnected(std::list<int> toConnect,std::list<int> canConnect)
	{
		std::list<int>::iterator iterTo;
		std::list<int>::iterator iterCan;

		for(iterTo = toConnect.begin(); iterTo!=toConnect.end(); iterTo++)
		{
			for(int i = 0; connectable[i][i]!=-1; i++)//sets the connected part of the matrix of all 'toConnect' to '0'
			{
				if(i>(*iterTo))
				{
					connectable[(*iterTo)][i] = 0;
				}
				if((*iterTo)>i)
				{
					connectable[i][(*iterTo)] = 0;
				}
			}
			for(iterCan = canConnect.begin();iterCan!=canConnect.end(); iterCan++) //this for loop will now
			{                                                                      //set all toConnect's 'connectable'
				if((*iterCan)>(*iterTo))										   //matrix to '1' where they intersect with										   //matrix to '1' where they intersect with
				{																   //the members of canConnect.
					connectable[(*iterTo)][(*iterCan)] = 1;
				}
				else if ((*iterTo)>(*iterCan))
				{
					connectable[(*iterCan)][(*iterTo)] = 1;
				}
			}
		}

		return 1;
	}


int Game::findConnected(int from, int current)
{
	//std::cout<<"Starting find Connected with"<<from<<" and "<<current<<".\n";
	while (connectable[current][current]>=0)
	{

	if (from>current)
	{
		//std::cout<<"Checking connection: "<<from<<" to "<<current<<"\n";
		if(connectable[from][current]!=0)
		{
			//std::cout<<"Connection found from "<<from<<" to "<<current<<"\n";
			return current;
		}
	}
	if (current>from)
	{
		//std::cout<<"Checking connection: "<<from<<" to "<<current<<"\n";
		if(connectable[current][from]!=0)
		{
			//std::cout<<"Connection found from "<<from<<" to "<<current<<"\n";
			return current;
		}
	}
	current+=1;

	}
	//std::cout<<"Iterated all the way through. \n";
	return -1;
}
bool Game::notEnregioned(int node, std::list<int> encapsulated)
{
	std::list<int>::iterator iterTo;
	std::list<int>::iterator iterEnd;
	iterEnd = encapsulated.end();
		for(iterTo = encapsulated.begin(); iterTo!=iterEnd; iterTo++)
		{
			if ((*iterTo)==node)
			{
				return false;
			}
		}
		return true;
}
std::list<int> Game::findBorders(int from, int to, int prev, std::list<int> encapsulated)  //fun function to find the borders of a region
	{
/*
		int nextConnected = 0;
		std::list<int>* borderNodes = new std::list<int>;

		if (from==to)
		{
			borderNodes->push_front(from);
			return borderNodes;
		}
		else
		{
		 while(nextConnected!=-1)
		 {
		  //std::cout<<"Connection found from "<<from<<" to "<<nextConnected<<"\n";
		  nextConnected = findConnected(from, nextConnected); //finds the next connection of the node
		  if ((nextConnected!=-1)&&(nextConnected!=prev)&&(notEnregioned(nextConnected,encapsulated)))
		  {
			  if (nextConnected!=-1)//if there IS another connection
				  borderNodes->merge(findBorders(nextConnected,to,from,encapsulated)); //call find borders to the next connection
			  if (!borderNodes->empty())//if, after all of that, borderNodes isn't empty (which will only occur if it is
				  borderNodes->push_front(from);//along the path to 'to'), then add 'from' to the list, and return
				//test harness
				std::list<int>::iterator iterTo;
				if (!borderNodes->empty())
				{
				iterTo = borderNodes->begin();
					while (iterTo!=borderNodes->end())
					{
						std::cout<<(*iterTo);
						iterTo++;
					}
					std::cout<<std::endl;
				}
				else std::cout <<"Empty\n";
				//test harness
			  borderNodes->sort(); //sorts borderNodes to prepare it for the 'merge' function.
			  return borderNodes;
		  }
		  else
		  {
			  //std::cout<<"Invalid connection found from "<<from<<" to "<<nextConnected<<"\n";
			  nextConnected += 1;
		  }
		}
		}


		return borderNodes;*/

		return encapsulated;
	}


bool Game::checkRegion(int created, int from, int to)
{
for (int i = 0; connectable[i][i]>-1; i++)
	{
		if (from>i)
		{
			if(!connectable[i][from])
			{
				if (created>i)
				{
					std::cout<<"Set"<<created<<","<<i<<"to 0.";
					connectable[i][created] = 0;
				}
				else if (i>created)
				{
					std::cout<<"Set"<<created<<","<<i<<"to 0.";
					connectable[created][i] = 0;
				}
			}
		}
		else if (i>from)
		{
			if(!connectable[from][i])
			{
				if (created>i)
				{
					std::cout<<"Set"<<created<<","<<i<<"to 0.";
					connectable[i][created] = 0;
				}
				else if (i>created)
				{
					std::cout<<"Set"<<created<<","<<i<<"to 0.";
					connectable[created][i] = 0;
				}
			}
		}


		if (to>i)
		{
			if(!connectable[i][to])
			{
				if (created>i)
				{
					std::cout<<"Set"<<created<<","<<i<<"to 0.";
					connectable[i][created] = 0;
				}
				else if (i>created)
				{
					std::cout<<"Set"<<created<<","<<i<<"to 0.";
					connectable[created][i] = 0;
				}
			}
		}
		else if (i>to)
		{
			if(!connectable[to][i])
			{
				if (created>i)
				{
					std::cout<<"Set"<<created<<","<<i<<"to 0.";
					connectable[i][created] = 0;
				}
				else if (i>created)
				{
					std::cout<<"Set"<<created<<","<<i<<"to 0.";
					connectable[created][i] = 0;
				}
			}
		}


	}

return 0;
}

bool Game::applyMove(int from, int to, int creates, std::list<int> encapsulated, bool clockwise, int near)
{
	turn = (turn+1)%2;
	output_console();
	this->nodes[creates] = new Sprout(creates, from, to, sproutClips,nodes, this);//creates a new node in the node array
	nodeNumbers++;

  // lets the sprouts know of the additional connections
  this->nodes[creates]->addConnection();
  this->nodes[creates]->addConnection();
  this->nodes[to]->addConnection();
  this->nodes[from]->addConnection();




	if(connection[creates][from]<0)//this section handles creating bezier curves in the 4n connection matrix
		connection[creates][from] = new Bezier(creates,from,this);
	else connection[from][creates] = new Bezier(creates,from,this);
	if(connection[to][creates]<0)
		connection[to][creates] = new Bezier(to,creates,this);
	else connection[creates][to]= new Bezier(to,creates,this);



	std::list<int> enregioning;
	int enregioned = 0;

		for(int i = 0; connectable[i][i]!=-1; i++)//initializes the 'connected' side of the array to zero for the new node?
	{
		if(i>creates)
		{
			connectable[i][creates] = 0;
		}
		else if (creates>i)
		{
			connectable[creates][i] = 0;
		}
	}

	//this section handles the 'connected' side of the array.
	if (from>creates)  //creating the connection from the 'from' node to the created node
	{
		connectable[from][creates] = 1;
	}
  else
  {
		connectable[creates][from] = 1;
	}
	connectable[from][from]+=1;
	if (to>creates)  //creating the connection from the 'to' node to the created node.
	{
		connectable[to][creates] = 1;
	}
  else
	{
		connectable[creates][to] = 1;
	}
	connectable[to][to]+=1;
	connectable[creates][creates]=2;



for (int i = 0;connectable[i][i]!=-1;i++) //this handles the initialization of the 'connectable' side of the array
  {											//for the created node, taking into consideration the 'near' node.
	if(near>i)                              //Note, however, that everything else related to enregioning is performed
	{										//At the bottom of the function
		if (connectable[i][near])
		{
			if(creates>i)
			{
			  connectable[i][creates]=1;
			}
			else if (creates<i)
			{
			  connectable[creates][i]=1;
			}
		}
	}
	if(i>near)
	{
		if (connectable[i][near])
		{
			if(i<creates)
			{
			  connectable[i][creates]=1;
			}
			else if (creates<i)
			{
			  connectable[creates][i]=1;
			}
		}
	 }
  }


	if (!encapsulated.empty())//if the list of encapsulated nodes is not empty, start figuring out the regions
	{
		enregioning = encapsulated;
		enregioning.sort();
		if (to!=from)
		{
			//enregioning.merge(findBorders(creates, to, to, encapsulated));//adds the borders to the enregioning list
		}
		else
		{
			enregioning.push_front(to);
			enregioning.push_front(creates);
		}
		setConnected(encapsulated, enregioning);
	}

	checkRegion(creates,from,to); //checks to see if the created node is inside a region, and, if so, adjusts the connectable matrix accordingly.
	gameWinState = checkWin();
	std::cout<<"Player "<<gameWinState<<" has won.";

	return 0;

}
