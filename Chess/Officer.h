#pragma once
#include "Point.h"

class Officer: public Point
{
public:
	Officer(int x, int y, int team);
	bool Check(int x, int y, Point ** arr);
};

Officer::Officer(int x, int y, int team)
{
	this->x = x;
	this->y = y;
	this->team = team;
	this->sym = 'O';
}

bool Officer::Check(int x, int y, Point ** arr)
{
	if ((this->x + this->y == x + y || this->x - this->y == x - y) && team != arr[x][y].GetTeam())
	{
		if (this->x < x && this->y < y)
		{
			for (int i = this->x+1, j = this->y+1;i<=x-1 && j<=y-1;i++,j++)
			{
				if (arr[i][j].GetTeam() != 0)
				{
					return false;
				}
			}
		}
		if (x < this->x && y < this->y)
		{
			for (int i = x+1, j = y+1;i<=this->x-1 && j<=this->y-1;i++,j++)
			{
				if (arr[i][j].GetTeam() != 0)
				{
					return false;
				}
			}
		}
		if (this->x < x && this->y > y)
		{
			for (int i = this->x+1, j = this->y-1;i<=x-1 && j>=y+1;i++,j--)
			{
				if (arr[i][j].GetTeam() != 0)
				{
					return false;
				}
			}
		}
		if (this->x > x && this->y < y)
		{
			for (int i = this->x-1, j = this->y+1;i>=x+1 && j<=y-1;i--,j++)
			{
				if (arr[i][j].GetTeam() != 0)
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