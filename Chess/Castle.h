#pragma once

#include "Point.h"

class Castle: public Point
{
	bool isFirst;
public:
	Castle(int x, int y, int team);
	bool Check(int x, int y, Point ** arr);
	bool GetIsFirst() {return isFirst;}
};

Castle::Castle(int x, int y, int team)
{
	this->x = x;
	this->y = y;
	this->team = team;
	this->sym = 'C';
	this->isFirst = true;
}

bool Castle::Check(int x, int y, Point ** arr)
{
	if ((this->x == x || this->y == y) && team != arr[x][y].GetTeam())
	{
		if (this->x > x)
		{
			for (int i = x+1;i<=this->x-1;i++)
			{
				if (arr[i][y].GetTeam() != 0)
				{
					return false;
				}
			}
		}
		if (this->x < x)
		{
			for (int i = this->x+1;i<=x-1;i++)
			{
				if (arr[i][y].GetTeam() != 0)
				{
					return false;
				}
			}
		}
		if (this->y > y)
		{
			for (int i = y+1;i<=this->y-1;i++)
			{
				if (arr[x][i].GetTeam() != 0)
				{
					return false;
				}
			}
		}
		if (this->y < y)
		{
			for (int i = this->y+1;i<=y-1;i++)
			{
				if (arr[x][i].GetTeam() != 0)
				{
					return false;
				}
			}
		}
		return true;
	}
	else
	{
		return false;
	}
}

