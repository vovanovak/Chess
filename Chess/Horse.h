#pragma once
#include "Point.h"

class Horse: public Point
{
public:
	Horse(int x, int y, int team);
	bool Check(int x, int y, Point ** arr);
};

Horse::Horse(int x, int y, int team)
{
	this->x = x;
	this->y = y;
	this->team = team;
	this->sym = 'H';
}

bool Horse::Check(int x, int y, Point ** arr)
{
	if (((this->x == x+1 && this->y == y+2) || (this->x == x+2 && this->y == y+1) || (this->x == x+2 && this->y == y-1) || (this->x == x+1 && this->y == y-2) || (this->x == x-1 && this->y == y-2) || (this->x == x-2 && this->y == y-1) || (this->x == x-2 && this->y == y+1) || (this->x == x-1 && this->y+2)) && team != arr[x][y].GetTeam())
	{
		return true;
	}
	else
	{
		return false;
	}
}
