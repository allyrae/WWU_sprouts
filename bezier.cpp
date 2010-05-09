#include "stdafx.h"
#include "include/draw.h"
#include "include/bezier.h"
#include "SDL_gfxPrimitives.h"

//Constructor, sets xy via array
Bezier::Bezier(Point coord[4])
{
  for(int i=0; i < 4; i++)
  {
    points[i].x = coord[i].x;
    points[i].y = coord[i].y;
  }
}

// constructor for bezier at a point to the mouse which will be changing
Bezier::Bezier(Point start)
{
  for (int i = 0; i < 4; i++)
  {
    points[i].x = start.x;
    points[i].y = start.y;
  }
}
//constructor, if no beginning coordinates are set.
Bezier::Bezier()
{
  for (int i = 0; i < 4; i++)
  {
    points[i].x = 0;
    points[i].y = 0;
  }

}

//constructor, if beginning coordinates are set.
Bezier::Bezier(int a, int b, int a1, int b1, int a2, int b2, int a3, int b3)
{
  points[0].x = a;
  points[0].y = b;
  points[1].x = a1;
  points[1].y = b1;
  points[2].x = a2;
  points[2].y = b2;
  points[3].x = a3;
  points[3].y = b3;
}

//Constructor, takes points to create curve
Bezier::Bezier(int from, int to, Game * g)
{
  int x1;
  int x2;
  int y1;
  int y2;
  x1 = points[0].x = g->nodes[from]->node.x;
  y1 = points[0].y = g->nodes[from]->node.y;
  x2 = points[3].x = g->nodes[to]->node.x;
  y2 = points[3].y = g->nodes[to]->node.y;
  // Calculate control points to make curves
  int rise = (y1-y2);   // the rise of the line between the nodes
  int run = (x1-x2);    // The run of the line between the nodes

  if (abs(rise) > abs(run)) // is the y value farther then the x values
  {
    points[1].x = x1 - run/2;
    points[1].y = y1;
    points[2].x = x2 + run/2;
    points[2].y = y2;
  }
  else
  {
    points[1].x = x1;
    points[1].y = y1 - rise/2;
    points[2].x = x2;
    points[2].y = y2 + rise/2;
  }
}

//Constructor, copies values from old curve
Bezier::Bezier(Bezier * oldCurve)
{
  // Copy the values into this curve from the old curve
  for (int i = 0; i < 4; i++)
  {
    points[i].x = oldCurve->points[i].x;
    points[i].y = oldCurve->points[i].y;
  }
}

//gets the coordinates of the selected point
Point Bezier::getcoord(int point)
{
  Point temp = {0,0};

  if (point < 1 || point > 4)
    return temp;

  return points[point-1];
}

//returns all of the coordinates
Point * Bezier::getcoord(void)
{
  return points;
}

//sets the coordinates of the selected point to the sent coordinates
bool Bezier::setcoord(int point,Point coord)
{
  if (point < 1 || point > 4)
    return 0;

  points[point-1].x = coord.x;
  points[point-1].y = coord.y;

  return 1;
}

//sets the coordinates of the selected point to sent x and y
bool Bezier::setcoord(int point,int x, int y)
{
  if (point < 1 || point > 4)
    return 0;

  points[point-1].x = x;
  points[point-1].y = y;

  return 1;
}

//sets the coordinates of the selected point via array
bool Bezier::setcoord(Point coord[4])
{
  for (int i=0; i < 4; i++)
  {
    points[i].x = coord[i].x;
    points[i].y = coord[i].y;
  }

  return 1;
}

void Bezier::setCurve(int x, int y) // Set the curve up with the new x,y for the second point
{
  // First thing lets set the second end point
  points[3].x = x;
  points[3].y = y;

  // Lets just create a straight line for now
  points[2].x = x;
  points[2].y = y;
}
//sets the coordinates of the selected point to sent x and y
bool Bezier::adjustCoord(int point,int x, int y)
{
  switch (point)
  {
  case CURVE_START:
    points[0].x = x;
    points[0].y = y;
    // set the 1st control point to match
    break;
  case CURVE_END:
    points[3].x = x;
    points[3].y = y;
    //set the 2nd control point to match
    break;
  }

  int x1 = points[0].x;
  int y1 = points[0].y;
  int x2 = points[3].x;
  int y2 = points[3].y;

  // Calculate control points to make curves
  int rise = (y1-y2);   // the rise of the line between the nodes
  int run = (x1-x2);    // The run of the line between the nodes

  if (abs(rise) > abs(run)) // is the y value farther then the x values
  {
    points[1].x = x1 - run/2;
    points[1].y = y1;
    points[2].x = x2 + run/2;
    points[2].y = y2;
  }
  else
  {
    points[1].x = x1;
    points[1].y = y1 - rise/2;
    points[2].x = x2;
    points[2].y = y2 + rise/2;
  }
  return 1;
}


//draw actual curve
void Bezier::draw(SDL_Surface * mysurface)
{
  Sint16 vx[4];
  Sint16 vy[4];

  Uint8 r = 0;
  Uint8 g = 255;
  Uint8 b = 0;

  // Center line
  for (int i=0; i < 4; i++)
  {
    vx[i] = points[i].x;
    vy[i] = points[i].y;
  }
  //bezierRGBA (surfacetype, x-vertex, y-vertex, #ofvetecies, #ofsteps, red,blue,green,alpha)
  bezierRGBA (mysurface, vx, vy, 4, 100, r,g,b,255);

  // Up line
  for (int i=0; i < 4; i++)
  {
    vx[i] = points[i].x;
    vy[i] = points[i].y-1;
  }
  //bezierRGBA (surfacetype, x-vertex, y-vertex, #ofvetecies, #ofsteps, red,blue,green,alpha)
  bezierRGBA (mysurface, vx, vy, 4, 100, r,g,b,127);

  // Left line
  for (int i=0; i < 4; i++)
  {
    vx[i] = points[i].x-1;
    vy[i] = points[i].y;
  }
  //bezierRGBA (surfacetype, x-vertex, y-vertex, #ofvetecies, #ofsteps, red,blue,green,alpha)
  bezierRGBA (mysurface, vx, vy, 4, 100, r,g,b,127);

  // bottom line
  for (int i=0; i < 4; i++)
  {
    vx[i] = points[i].x;
    vy[i] = points[i].y+1;
  }
  //bezierRGBA (surfacetype, x-vertex, y-vertex, #ofvetecies, #ofsteps, red,blue,green,alpha)
  bezierRGBA (mysurface, vx, vy, 4, 100,  r,g,b,127);

  // Right line
  for (int i=0; i < 4; i++)
  {
    vx[i] = points[i].x+1;
    vy[i] = points[i].y;
  }
    //bezierRGBA (surfacetype, x-vertex, y-vertex, #ofvetecies, #ofsteps, red,blue,green,alpha)
    bezierRGBA (mysurface, vx, vy, 4, 100,  r,g,b,127);
}

// destructor
Bezier::~Bezier()
{
  // Free the memory
  // Shouldnt be anything additional
}
