#pragma once

#include "draw.h"
#include "game.h"
#include "SDL_gfxPrimitives.h"
//header for drawing the curves

enum Curve{CURVE_START,
      CURVE_END};

//class declaratio
class Bezier{
	private:
		Point points[4];
	public:
		Bezier(int,int,int,int,int,int,int,int);//constructor, if beginning coordinates are set.
		Bezier(Point coord[4]);//constructor
    Bezier(Point start);
    Bezier(Bezier *);
		Bezier(void);//constructor, if no beginning coordinates are set.
		Bezier(Point,Point,Point,Point);
    Bezier(int from, int to, Game * game);
		Point getcoord(int point);//gets the coordinates of the selected point
		Point * getcoord(void);//returns all coordinates
    void setCurve(int x, int y);    // Sets the curve up with the second end point at (x,y)
		bool setcoord(int point, Point coord);//sets the coordinates of the selected point to the sent coordinates
		bool setcoord(int point, int x, int y);//sets the coordinates of the selected point to sent x and y
		bool setcoord(Point coords[4]);//sets the coordinates of the selected point by array
		bool adjustCoord(int point, int x, int y);//sets the coordinates of the selected point to sent x and y
    void draw(SDL_Surface *);//draws the curve
    ~Bezier();
};


