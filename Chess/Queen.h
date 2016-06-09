#pragma once

#include "Point.h"

class Queen: public Point
{
public:
	Queen(int x, int y, int team);
	bool Check(int x, int y, Point ** arr);
};

Queen::Queen(int x, int y, int team)
{
	this->x = x;
	this->y = y;
	this->team = team;
	this->sym = 'Q';
}

bool Queen::Check(int x, int y, Point ** arr)
{
	if ((this->x == x || this->y == y || this->x + this->y == x + y || this->x - this->y == x - y) && team != arr[x][y].GetTeam())
	{
		if ((this->x == x || this->y == y) && team != arr[x][y].GetTeam())
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
	}
	else
	{
		return false;
	}
}