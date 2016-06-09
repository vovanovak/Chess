#pragma once

#include "Point.h"

class Pawn: public Point
{
	bool isFirst;
public:
	Pawn(int x, int y, int team);
	bool Check(int x, int y, Point ** arr);
};

Pawn::Pawn(int x, int y, int team)
{
	this->x = x;
	this->y = y;
	this->team = team;
	this->sym = 'P';
	this->isFirst = 1;
}

bool Pawn::Check(int x, int y, Point ** arr)
{
 	if (team == 1)
	{
		if (isFirst)
		{
			if (x - this->x <= 2 && x - this->x >= 1 && arr[x][y].GetSym() == ' '  && y != this->y-1 && y != this->y+1 && team != arr[x][y].GetTeam())
			{
				return true;
			}
			else
				if (arr[x][y].GetSym() != ' ' && x == this->x+1 && (y == this->y+1 || y == this->y-1) && team != arr[x][y].GetTeam())
				{
					return true;
				}
				else
				{
					return false;
				}
		}
		else
		{
			if (x - this->x <= 1 && this->x - x >= 1 && arr[x][y].GetSym() == ' '  && y != this->y-1 && y != this->y+1 && team != arr[x][y].GetTeam())
			{
				return true;
			}
			else
				if (arr[x][y].GetSym() != ' ' && x == this->x+1 && (y == this->y+1 || y == this->y-1) && team != arr[x][y].GetTeam())
				{
					return true;
				}
				else
				{
					return false;
				}
		}
	}
	if (team == 2)
	{
		if (isFirst)
		{
			if (this->x - x <= 2 && this->x - x >= 1 && arr[x][y].GetSym() == ' '  && y != this->y-1 && y != this->y+1 && team != arr[x][y].GetTeam())
			{
				return true;
			}
			else
				if (arr[x][y].GetSym() != ' ' && x == this->x-1 && (y == this->y-1 || y == this->y+1) && team != arr[x][y].GetTeam())
				{
					return true;
				}
				else
				{
					return false;
				}
		}
		else
		{
			if (this->x - x <= 1 && x - this->x >= 1 && arr[x][y].GetSym() == ' ' && y != this->y-1 && y != this->y+1 && team != arr[x][y].GetTeam())
			{
				return true;
			}
			else
				if (arr[x][y].GetSym() != ' ' && x == this->x-1 && (y == this->y-1 || y == this->y+1) && team != arr[x][y].GetTeam())
				{
					return true;
				}
				else
				{
					return false;
				}
		}
	}
}

