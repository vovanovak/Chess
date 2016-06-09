#pragma once
#include "Point.h"

class King: public Point
{
	bool isFirst;
public:
	King(int x, int y, int team);
	bool Check(int x, int y, Point ** arr);
	bool isMate(Point ** arr);
	bool isCheck(Point ** arr);
	bool Rokirovka(int x, int y, Point ** arr);
};

King::King(int x, int y, int team)
{
	this->x = x;
	this->y = y;
	this->team = team;
	this->sym = 'K';
	this->isFirst = true;
}

bool King::Check(int x, int y, Point ** arr)
{
	if (((this->x - x >= -1 && this->x - x <= 1) && (this->y - y >= -1 && this->y - y <= 1)) && team != arr[x][y].GetTeam())
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool King::Rokirovka(int x, int y, Point ** arr)
{
	if (arr[x][y].GetSym()!='C')
	{
		return false;
	}
	if (arr[x][y].GetTeam() == 1)
	{
		if (x == 0 && y == 0)
		{
			if (arr[0][1].GetSym() == ' ' && arr[0][2].GetSym() == ' ' && arr[0][3].GetSym() == ' ')
			{
				for (int i = 0;i<8;i++)
				{
					if ((arr[i][2].GetSym() == 'C' || arr[i][2].GetSym() == 'Q') && arr[i][2].GetTeam() == 2)
					{
						return false;
					}
					if (arr[i][2].GetTeam() == 1)
					{
						break;
					}
				}
				for (int i = 0,j = 2;i < 6 && j < 7;i++,j++)
				{
					if ((arr[i][j].GetSym() == 'O' || arr[i][j].GetSym() == 'Q') && arr[i][j].GetTeam() == 2)
					{
						return false;
					}
					if (arr[i][j].GetTeam() == 1)
					{
						break;
					}
				}
				for (int i = 0,j = 2;i < 3 && j >= 0;i++,j--)
				{
					if ((arr[i][j].GetSym() == 'O' || arr[i][j].GetSym() == 'Q') && arr[i][j].GetTeam() == 2)
					{
						return false;
					}
					if (arr[i][j].GetTeam() == 1)
					{
						break;
					}
				}
				if ((arr[1][1].GetSym() == 'P' && arr[1][1].GetTeam() == 2) || (arr[1][3].GetSym() == 'P' && arr[1][3].GetTeam() == 2))
				{
					return false;
				}
				if ((arr[1][0].GetSym() == 'H' && arr[1][0].GetTeam() == 2) && (arr[2][1].GetSym() == 'H' && arr[2][1].GetTeam() == 2) && (arr[2][3].GetSym() == 'H' && arr[2][3].GetTeam() == 2) && (arr[1][4].GetSym() == 'H' && arr[1][4].GetTeam() == 2))
				{
					return false;
				}
				return true;
			}
			else
			{
				return false;
			}
		}
		else
			if (x == 0 && y == 7)
			{
				if (arr[0][5].GetSym() == ' ' && arr[0][6].GetSym() == ' ')
				{
					for (int i = 0;i<8;i++)
					{
						if ((arr[i][6].GetSym() == 'C' || arr[i][6].GetSym() == 'Q') && arr[i][6].GetTeam() == 2)
						{
							return false;
						}
						if (arr[i][5].GetTeam() == 1)
						{
							break;
						}
					}
					for (int i = 0,j = 6;i < 7 && j >= 0;i++,j--)
					{
						if ((arr[i][j].GetSym() == 'O' || arr[i][j].GetSym() == 'Q') && arr[i][j].GetTeam() == 2)
						{
							return false;
						}
						if (arr[i][j].GetTeam() == 1)
						{
							break;
						}
					}
					if (((arr[1][7].GetSym() == 'P' || arr[1][7].GetSym() == 'Q' || arr[1][7].GetSym() == 'O') && arr[1][7].GetTeam() == 2) || (arr[1][5].GetSym() == 'P' && arr[1][5].GetTeam() == 2))
					{
						return false;
					}
					if ((arr[1][3].GetSym() == 'H' && arr[1][3].GetTeam() == 2) || (arr[2][4].GetSym() == 'H' && arr[2][4].GetTeam() == 2) || (arr[1][7].GetSym() == 'H' && arr[1][7].GetTeam() == 2) || (arr[2][6].GetSym() == 'H' && arr[2][6].GetTeam() == 2))
					{
						return false;
					}
					return true;
				}
				else
				{
					return false;
				}
			}
			else
			{
				return false;
			}
	}
	if (arr[x][y].GetTeam() == 2)
	{
		if (x == 7 && y == 0)
		{
			if (arr[7][1].GetSym() == ' ' && arr[7][2].GetSym() == ' ' && arr[7][3].GetSym() == ' ')
			{
				for (int i = 7;i>=0;i++)
				{
					if ((arr[i][2].GetSym() == 'C' || arr[i][2].GetSym() == 'Q') && arr[i][2].GetTeam() == 1)
					{
						return false;
					}
					if (arr[i][2].GetTeam() == 2)
					{
						break;
					}
				}
				for (int i = 7, j = 2;i >= 2 && j < 8;i++,j++)
				{
					if ((arr[i][j].GetSym() == 'O' || arr[i][j].GetSym() == 'Q') && arr[i][j].GetTeam() == 2)
					{
						return false;
					}
					if (arr[i][j].GetTeam() == 1)
					{
						break;
					}
				}
				if ((arr[6][1].GetSym() == 'O' || arr[6][1].GetSym() == 'P' || arr[6][1].GetSym() == 'Q') && arr[6][1].GetTeam() == 2)
				{
					return false;
				}
				if ((arr[5][0].GetSym() == 'O' || arr[5][0].GetSym() == 'Q') && arr[5][0].GetTeam() == 2)
				{
					return false;
				}
				if ((arr[6][0].GetSym() == 'H' && arr[6][0].GetTeam() == 2) || (arr[5][1].GetSym() == 'H' && arr[5][1].GetTeam() == 2) || (arr[5][3].GetSym() == 'H' && arr[5][3].GetTeam() == 2) || (arr[6][4].GetSym() == 'H' && arr[6][4].GetTeam() == 2))
				{
					return false;
				}
				return true;
			}
			else
			{
				return false;
			}
		}
		else
			if (x == 7 && y == 7)
			{
				if (arr[7][5].GetSym() == ' ' && arr[7][6].GetSym() == ' ')
				{
					for (int i = 7;i>=0;i--)
					{
						if ((arr[i][6].GetSym() == 'C' || arr[i][6].GetSym() == 'Q') && arr[i][6].GetTeam() == 1)
						{
							return false;
						}
						if (arr[i][6].GetTeam() == 2)
						{
							break;
						}
					}
					for (int i = 7,j = 6;i >= 1 && j >= 0;i--,j--)
					{
						if ((arr[i][j].GetSym() == 'O' || arr[i][j].GetSym() == 'Q') && arr[i][j].GetTeam() == 2)
						{
							return false;
						}
						if (arr[i][j].GetTeam() == 1)
						{
							break;
						}
					}
					if ((arr[6][7].GetSym() == 'O' || arr[6][7].GetSym() == 'P' || arr[6][7].GetSym() == 'Q') && arr[6][7].GetTeam() == 2)
					{
						return false;
					}
					if ((arr[6][4].GetSym() == 'H' && arr[2][2].GetTeam() == 2) || (arr[5][5].GetSym() == 'H' && arr[2][2].GetTeam() == 2) || (arr[5][7].GetSym() == 'H' && arr[2][2].GetTeam() == 2))
					{
						return false;
					}
					return true;
				}
				else
				{
					return false;
				}
			}
			else
			{
				return false;
			}
	}
}