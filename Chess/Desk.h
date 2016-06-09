#include "Pawn.h"
#include "Castle.h"
#include "Horse.h"
#include "King.h"
#include "Queen.h"
#include "Officer.h"
#include <Windows.h>
#include <fstream>
#include <io.h>
#include <string>

#pragma once
#ifndef DESK_H

class Desk
{
	Point ** arr;
public:
	Desk();
	Desk(Point ** arr);
	void PawnToQueen();
	void Move(HWND& hWnd, int x, int y, int x1 , int y1);
	bool Check(string , string);
	bool Shah(int , int, int);
	bool Mate(int , int, int);
	void Print(HDC hdc, CImage arr1[12]);
	void FindKingsCoords(int &x_king_1, int &y_king_1,int &x_king_2,int &y_king_2);
	void Rokirovka(int x, int y, int x1, int y1);
	void Open(string& player11, string& player22, int& team_go);
	void Save(wchar_t * player1, wchar_t * player2, int team_go);
	bool CheckTeam(int x, int y,int team);
	void SetPosition(int x , int y , int x1, int y1);
	void ToNull();
	~Desk();
};

Desk::Desk()
{
	arr = new Point *[8];
	for (int i = 0;i<8;i++)
	{
		arr[i] = new Point [8];
		for (int j = 0;j<8;j++)
		{
			arr[i][j](i,j,' ', 0);
		}
	}
	for (int i = 0;i<8;i++)
	{
		arr[1][i] = (Point&)(Pawn(1,i,1));
	}
	for (int i = 0;i<8;i++)
	{
		arr[6][i] = (Point&)(Pawn(6,i,2));
	}
	arr[0][0] = (Point&)(Castle(0,0,1));
	arr[0][7] = (Point&)(Castle(0,7,1));
	arr[7][0] = (Point&)(Castle(7,0,2));
	arr[7][7] = (Point&)(Castle(7,7,2));
	arr[0][1] = (Point&)(Horse(0,1,1));
	arr[0][6] = (Point&)(Horse(0,6,1));
	arr[7][1] = (Point&)(Horse(7,1,2));
	arr[7][6] = (Point&)(Horse(7,6,2));
	arr[0][2] = (Point&)(Officer(0,2,1));
	arr[0][5] = (Point&)(Officer(0,5,1));
	arr[7][2] = (Point&)(Officer(7,2,2));
	arr[7][5] = (Point&)(Officer(7,5,2));
	arr[0][4] = (Point&)(King(0,4,1));
	arr[0][3] = (Point&)(Queen(0,3,1));
	arr[7][4] = (Point&)(King(7,4,2));
	arr[7][3] = (Point&)(Queen(7,3,2));
}
void Desk::ToNull()
{
	if (arr)
		delete []arr;
	arr = new Point *[8];
	for (int i = 0;i<8;i++)
	{
		arr[i] = new Point [8];
		for (int j = 0;j<8;j++)
		{
			arr[i][j](i,j,' ', 0);
		}
	}
	for (int i = 0;i<8;i++)
	{
		arr[1][i] = (Point&)(Pawn(1,i,1));
	}
	for (int i = 0;i<8;i++)
	{
		arr[6][i] = (Point&)(Pawn(6,i,2));
	}
	arr[0][0] = (Point&)(Castle(0,0,1));
	arr[0][7] = (Point&)(Castle(0,7,1));
	arr[7][0] = (Point&)(Castle(7,0,2));
	arr[7][7] = (Point&)(Castle(7,7,2));
	arr[0][1] = (Point&)(Horse(0,1,1));
	arr[0][6] = (Point&)(Horse(0,6,1));
	arr[7][1] = (Point&)(Horse(7,1,2));
	arr[7][6] = (Point&)(Horse(7,6,2));
	arr[0][2] = (Point&)(Officer(0,2,1));
	arr[0][5] = (Point&)(Officer(0,5,1));
	arr[7][2] = (Point&)(Officer(7,2,2));
	arr[7][5] = (Point&)(Officer(7,5,2));
	arr[0][4] = (Point&)(King(0,4,1));
	arr[0][3] = (Point&)(Queen(0,3,1));
	arr[7][4] = (Point&)(King(7,4,2));
	arr[7][3] = (Point&)(Queen(7,3,2));
}
void Desk::FindKingsCoords(int &x_king_1, int &y_king_1,int &x_king_2,int &y_king_2)
{

	for (int i = 0;i<8;i++)
	{
		for (int j = 0;j<8;j++)
		{
			if (arr[i][j].GetTeam() == 1 && arr[i][j].GetSym() == 'K')
			{
				x_king_1 = i;
				y_king_1 = j;
			}
			if (arr[i][j].GetTeam() == 2 && arr[i][j].GetSym() == 'K')
			{
				x_king_2 = i;
				y_king_2 = j;
			}
		}
	}
}
bool Desk::CheckTeam(int x, int y,int team)
{
	if (arr[x][y].GetTeam() == team)
	{
		return true;
	}
	else
	{
		return false;
	}
}
void Desk::Print(HDC hdc, CImage arr1[12])
{
	int x = 16, y = 16;
	for (int i = 0;i<8;i++)
	{
		for (int j = 0;j<8;j++)
		{
			SetBkMode(hdc, TRANSPARENT);
			switch(arr[i][j].GetSym())
			{
			case 'P':
				if (arr[i][j].GetTeam() == 1)
				{
					arr1[0].SetTransparentColor(RGB(255, 255, 255));
					arr1[0].Draw(hdc, x, y);
				}
				else
				{
					arr1[1].SetTransparentColor(RGB(255, 255, 255));
					arr1[1].Draw(hdc, x, y);
				}
				break;
			case 'C':
				if (arr[i][j].GetTeam() == 1)
				{
					arr1[2].SetTransparentColor(RGB(255, 255, 255));
					arr1[2].Draw(hdc, x, y);
				}
				else
				{
					arr1[3].SetTransparentColor(RGB(255, 255, 255));
					arr1[3].Draw(hdc, x, y);
				}
				break;
			case 'H':
				if (arr[i][j].GetTeam() == 1)
				{
					arr1[4].SetTransparentColor(RGB(255, 255, 255));
					arr1[4].Draw(hdc, x, y);
				}
				else
				{
					arr1[5].SetTransparentColor(RGB(255, 255, 255));
					arr1[5].Draw(hdc, x, y);
				}
				break;
			case 'O':
				if (arr[i][j].GetTeam() == 1)
				{
					arr1[6].SetTransparentColor(RGB(255, 255, 255));
					arr1[6].Draw(hdc, x, y);
				}
				else
				{
					arr1[7].SetTransparentColor(RGB(255, 255, 255));
					arr1[7].Draw(hdc, x, y);
				}
				break;
			case 'Q':
				if (arr[i][j].GetTeam() == 1)
				{
					arr1[8].SetTransparentColor(RGB(255, 255, 255));
					arr1[8].Draw(hdc, x, y);
				}
				else
				{
					arr1[9].SetTransparentColor(RGB(255, 255, 255));
					arr1[9].Draw(hdc, x, y);
				}
				break;
			case 'K':
				if (arr[i][j].GetTeam() == 1)
				{
					arr1[10].SetTransparentColor(RGB(255, 255, 255));
					arr1[10].Draw(hdc, x, y);
				}
				else
				{
					arr1[11].SetTransparentColor(RGB(255, 255, 255));
					arr1[11].Draw(hdc, x, y);
				}
				break;
			}
			x+=32;
		}
		x=16;
		y+=32;
	}
}
bool Desk::Check(string str1, string str2)
{
	int x_king_1,y_king_1,x_king_2,y_king_2;
	FindKingsCoords(x_king_1,y_king_1,x_king_2,y_king_2);
	if (Mate(x_king_1,y_king_1,1))
	{
		str1.append(" wins!!!");
		str2.append(" loses:(");
		return true;
	}
	else
		if (Mate(x_king_2,y_king_2,2))
		{
			str1.append(" loses:(");
			str2.append(" wins!!!");
			return true;
		}
		else
		{
			return false;
		}
}
bool Desk::Shah(int x1, int y1, int team)
{
	int enemy;
	if (team == 1)
	{
		enemy = 2;
	}
	if (team == 2)
	{
		enemy = 1;
	}
	for (int i = x1+1;i<8;i++)
	{
		if (arr[i][y1].GetTeam() == enemy && (arr[i][y1].GetSym() == 'C' || arr[i][y1].GetSym() == 'Q'))
		{
			return true;
		}
		if (arr[i][y1].GetTeam() == team)
		{
			break;
		}
	}
	for (int i = x1-1;i>=0;i--)
	{
		if (arr[i][y1].GetTeam() == enemy && (arr[i][y1].GetSym() == 'C' || arr[i][y1].GetSym() == 'Q'))
		{
			return true;
		}
		if (arr[i][y1].GetTeam() == team)
		{
			break;
		}
	}
	for (int i = y1+1;i<8;i++)
	{
		if (arr[x1][i].GetTeam() == enemy && (arr[x1][i].GetSym() == 'C' || arr[x1][i].GetSym() == 'Q'))
		{
			return true;
		}
		if (arr[x1][i].GetTeam() == team)
		{
			break;
		}
	}
	for (int i = y1-1;i>=0;i--)
	{
		if (arr[x1][i].GetTeam() == enemy && (arr[x1][i].GetSym() == 'C' || arr[x1][i].GetSym() == 'Q'))
		{
			return true;
		}
		if (arr[x1][i].GetTeam() == team)
		{
			break;
		}
	}
	if (x1 - 1 > 0 && y1-1 > 0)
	{
		for (int i = x1-1, j = y1-1; i>0 || j>0;i--,j--)
		{
			if (arr[i][j].GetTeam() == enemy && (arr[i][j].GetSym() == 'O' || arr[i][j].GetSym() == 'Q'))
			{
				return true;
			}
			if (arr[i][j].GetTeam() == team)
			{
				break;
			}
		}
	}
	if (x1 + 1 < 7 && y1 + 1 < 7)
	{
		for (int i = x1+1, j = y1+1; i<7 || j<7;i++,j++)
		{
			if (arr[i][j].GetTeam() == enemy && (arr[i][j].GetSym() == 'O' || arr[i][j].GetSym() == 'Q'))
			{
				return true;
			}
			if (arr[i][j].GetTeam() == team)
			{
				break;
			}
		}
	}
	if (x1 - 1 > 0 && y1 + 1 < 7)
	{
		for (int i = x1-1, j = y1+1; i>0 || j<7;i--,j++)
		{
			if (arr[i][j].GetTeam() == enemy && (arr[i][j].GetSym() == 'O' || arr[i][j].GetSym() == 'Q'))
			{
				return true;
			}
			if (arr[i][j].GetTeam() == team)
			{
				break;
			}
		}
	}
	if (x1 + 1 < 7 && y1 - 1 > 0)
	{
		for (int i = x1+1, j = y1-1; i<7 || j>0;i++,j--)
		{
			if (arr[i][j].GetTeam() == enemy && (arr[i][j].GetSym() == 'O' || arr[i][j].GetSym() == 'Q'))
			{
				return true;
			}
			if (arr[i][j].GetTeam() == team)
			{
				break;
			}
		}
	}
	if (team == 1)
	{
		if (x1 + 1 < 8 && y1 + 1 < 8)
		{
			if (arr[x1+1][y1+1].GetSym() == 'P' && arr[x1+1][y1+1].GetTeam() == enemy)
			{
				return true;
			}
		}
		if (x1 + 1 < 8 && y1 - 1 >= 0)
		{
			if (arr[x1+1][y1-1].GetSym() == 'P' && arr[x1+1][y1-1].GetTeam() == enemy)
			{
				return true;
			}
		}
	}
	if (team == 2)
	{
		if (x1 - 1 >= 0 && y1 + 1 < 8)
		{
			if (arr[x1-1][y1+1].GetSym() == 'P' && arr[x1-1][y1+1].GetTeam() == enemy)
			{
				return true;
			}
		}
		if (x1 - 1 >= 0 && y1 - 1 >= 0)
		{
			if (arr[x1-1][y1-1].GetSym() == 'P' && arr[x1-1][y1-1].GetTeam() == enemy)
			{
				return true;
			}
		}
	}
		
	if (x1 + 1 < 8 && y1 + 2 < 8)
	{
		if (arr[x1+1][y1+2].GetSym() == 'H' && arr[x1+1][y1+2].GetTeam() == enemy)
		{
			return true;
		}
	}
	if (x1 + 2 < 8 && y1 + 1 < 8)
	{
		if (arr[x1+2][y1+1].GetSym() == 'H' && arr[x1+2][y1+1].GetTeam() == enemy)
		{
			return true;
		}
	}
	if (y1-1 >= 0)
	{
		if (x1 + 2 < 8)
		{
			if (arr[x1+2][y1-1].GetSym() == 'H' && arr[x1+2][y1-1].GetTeam() == enemy)
			{
				return true;
			}
		}
		if (y1-2 >= 0)
		{
			if (x1 + 1 < 8)
			{
				if (arr[x1+1][y1-2].GetSym() == 'H' && arr[x1+1][y1-2].GetTeam() == enemy)
				{
					return true;
				}
			}
		}
	}
	if (x1-1 >= 0)
	{
		if (y1 + 2 < 8)
		{
			if (arr[x1-1][y1+2].GetSym() == 'H' && arr[x1-1][y1+2].GetTeam() == enemy)
			{
				return true;
			}
		}
		if (x1-2 >= 0)
		{
			if (y1 + 1 < 8)
			{
				if (arr[x1-2][y1+1].GetSym() == 'H' && arr[x1-2][y1+1].GetTeam() == enemy)
				{
					return true;
				}
			}
		}
	}
	if (x1-1 >= 0 && y1-2 >= 0)
	{
		if (arr[x1-1][y1-2].GetSym() == 'H' && arr[x1-1][y1-2].GetTeam() == enemy)
		{
			return true;
		}
	}
	if (x1-2 >= 0 && y1+1 < 8)
	{
		if (arr[x1-2][y1+1].GetSym() == 'H' && arr[x1-2][y1+1].GetTeam() == enemy)
		{
			return true;
		}
	}
	return false;
}
void Desk::Rokirovka(int x, int y, int x1, int y1)
{
	King k(x,y,arr[x][y].GetTeam());
	if (k.Rokirovka(x1,y1,arr))
	{
		if (x1 == 0 && y1 == 0)
		{
			arr[0][3](0,3,' ',0);
			arr[0][0](0,0,' ',0);
			arr[0][1](0,1,'K',1);
			arr[0][2](0,2,'C',1);
		}
		if (x1 == 0 && y1 == 7)
		{
			arr[0][4](0,3,' ',0);
			arr[0][7](0,7,' ',0);
			arr[0][6](0,6,'K',1);
			arr[0][5](0,5,'C',1);
		}
		if (x1 == 7 && y1 == 0)
		{
			arr[7][3](7,3,' ',0);
			arr[7][0](7,0,' ',0);
			arr[7][1](7,2,'K',2);
			arr[7][2](7,3,'C',2);
		}
		if (x1 == 7 && y1 == 7)
		{
			arr[7][4](7,3,' ',0);
			arr[7][7](7,7,' ',0);
			arr[7][6](7,6,'K',2);
			arr[7][5](7,5,'C',2);
		}
	}
	else
	{
		MessageBox(NULL, L"Invalid move !!! Rokirovka is unavailible", L"Chess", MB_OK | MB_ICONERROR);
	}
}
void Desk::Move(HWND& hWnd, int x, int y, int x1 , int y1)
{
	int x_king_1 = 0, y_king_1 = 0, x_king_2 = 0,y_king_2 = 0; 
	FindKingsCoords(x_king_1, y_king_1, x_king_2,y_king_2);
	if (arr[x1][y1].GetSym() != 'K')
	{
		if (arr[x][y].GetSym() == 'P')
		{
			Pawn p(x,y,arr[x][y].GetTeam());
			if (p.Check(x1,y1,arr))
			{
				if (arr[x][y].GetTeam() == 1)
				{
					if (!Shah(x_king_1,y_king_1,1))
					{
						this->arr[x1][y1](x1,y1,'P',1);
						this->arr[x][y](x,y,' ',0);
					}
					else
					{
						SetWindowText(hWnd, L"Invalid move!!! King is under shah");
						InvalidateRect(hWnd, NULL, 1);
						Sleep(1000);
					}
				}
				if (arr[x][y].GetTeam() == 2)
				{
					if (!Shah(x_king_2,y_king_2,2))
					{
						this->arr[x1][y1](x1,y1,'P',2);
						this->arr[x][y](x,y,' ',0);
					}
					else
					{
						SetWindowText(hWnd, L"Invalid move!!! King is under shah");
						InvalidateRect(hWnd, NULL, 1);
						Sleep(1000);
					}
				}	
			}
			else
			{
				SetWindowText(hWnd, L"Invalid move !!! ");
				InvalidateRect(hWnd, NULL, 1);
				Sleep(1000);
			}
			PawnToQueen();
		}
		else
			if (arr[x][y].GetSym() == 'O')
			{
				Officer o(x,y,arr[x][y].GetTeam());
				if (o.Check(x1,y1,arr))
				{
					if (arr[x][y].GetTeam() == 1)
					{
						if (!Shah(x_king_1,y_king_1,1))
						{
							this->arr[x1][y1](x1,y1,'O',1);
							this->arr[x][y](x,y,' ',0);
						}
						else
						{
							SetWindowText(hWnd, L"Invalid move!!! King is under shah");
							InvalidateRect(hWnd, NULL, 1);
							Sleep(1000);
						}
					}
					
					if (arr[x][y].GetTeam() == 2)
					{
						if (!Shah(x_king_2,y_king_2,2))
						{
							this->arr[x1][y1](x1,y1,'O',2);
							this->arr[x][y](x,y,' ',0);
						}
						else
						{
							SetWindowText(hWnd, L"Invalid move!!! King is under shah");
							InvalidateRect(hWnd, NULL, 1);
							Sleep(1000);
						}
					}
					
				}
				else
				{
					SetWindowText(hWnd, L"Invalid move !!! ");
					InvalidateRect(hWnd, NULL, 1);
					Sleep(1000);
				}
			}
			else
				if (arr[x][y].GetSym() == 'C')
				{
					Castle c(x,y,arr[x][y].GetTeam());
					if (c.Check(x1,y1,arr))
					{
						if (arr[x][y].GetTeam() == 1)
						{
							if (!Shah(x_king_1,y_king_1,1))
							{
								this->arr[x1][y1](x1,y1,'C',1);
								this->arr[x][y](x,y,' ',0);
							}
							else
							{
								SetWindowText(hWnd, L"Invalid move!!! King is under shah");
								InvalidateRect(hWnd, NULL, 1);
								Sleep(1000);
							}
						}
						if (arr[x][y].GetTeam() == 2)
						{
							if (!Shah(x_king_2,y_king_2,2))
							{
								this->arr[x1][y1](x1,y1,'C',2);
								this->arr[x][y](x,y,' ',0);
							}
							else
							{
								SetWindowText(hWnd, L"Invalid move!!! King is under shah");
								InvalidateRect(hWnd, NULL, 1);
								Sleep(1000);
							}
						}	
					}
					else
					{
						SetWindowText(hWnd, L"Invalid move !!! ");
						InvalidateRect(hWnd, NULL, 1);
						Sleep(1000);
					}
				}
				else
					if (arr[x][y].GetSym() == 'H')
					{
						Horse h(x,y,arr[x][y].GetTeam());
						if (h.Check(x1,y1,arr))
						{
							if (arr[x][y].GetTeam() == 1)
							{
								if (!Shah(x_king_1,y_king_1,1))
								{
									this->arr[x1][y1](x1,y1,'H',1);
									this->arr[x][y](x,y,' ',0);
								}
								else
								{
									SetWindowText(hWnd, L"Invalid move!!! King is under shah");
									InvalidateRect(hWnd, NULL, 1);
									Sleep(1000);
								}
							}
							if (arr[x][y].GetTeam() == 2)
							{
								if (!Shah(x_king_2,y_king_2,2))
								{
									this->arr[x1][y1](x1,y1,'H',2);
									this->arr[x][y](x,y,' ',0);
								}
								else
								{
									SetWindowText(hWnd, L"Invalid move!!! King is under shah");
									InvalidateRect(hWnd, NULL, 1);
									Sleep(1000);
								}
							}	
						}
						else
						{
							SetWindowText(hWnd, L"Invalid move !!! ");
							InvalidateRect(hWnd, NULL, 1);
							Sleep(1000);
						}
					}
					else
						if (arr[x][y].GetSym() == 'Q')
						{
							Queen q(x,y,arr[x][y].GetTeam());
							if (q.Check(x1,y1,arr))
							{
								if (arr[x][y].GetTeam() == 1)
								{
									if (!Shah(x_king_1,y_king_1,1))
									{
										this->arr[x1][y1](x1,y1,'Q',1);
										this->arr[x][y](x,y,' ',0);
									}
									else
									{
										SetWindowText(hWnd, L"Invalid move!!! King is under shah");
										InvalidateRect(hWnd, NULL, 1);
										Sleep(1000);
									}
								}
								if (arr[x][y].GetTeam() == 2)
								{
									if (!Shah(x_king_2,y_king_2,2))
									{
										this->arr[x1][y1](x1,y1,'Q',2);
										this->arr[x][y](x,y,' ',0);
									}
									else
									{
										SetWindowText(hWnd, L"Invalid move!!! King is under shah");
										InvalidateRect(hWnd, NULL, 1);
										Sleep(1000);
									}
								}	
							}
							else
							{
								SetWindowText(hWnd, L"Invalid move !!! ");
								InvalidateRect(hWnd, NULL, 1);
								Sleep(1000);
							}
						}
						else
							if (arr[x][y].GetSym() == 'K')
							{
								King k(x,y,arr[x][y].GetTeam());
								if (k.Check(x1,y1,arr) && !Shah(x1,y1,arr[x][y].GetTeam()))
								{
									this->arr[x1][y1](x1,y1,'K',arr[x][y].GetTeam());
									this->arr[x][y](x,y,' ',0);
								}
								else
								{
									SetWindowText(hWnd, L"Invalid move!!! King is under shah");
									InvalidateRect(hWnd, NULL, 1);
									Sleep(1000);
								}
							}
							else
							{
								SetWindowText(hWnd, L"Invalid move !!! ");
								InvalidateRect(hWnd, NULL, 1);
								Sleep(1000);
							}
	}
	if (Shah(x_king_1,y_king_1,1))
	{
		SetWindowText(hWnd, L"Shah!!!");
		if (Mate(x_king_1,y_king_1,1))
		{
			SetWindowText(hWnd, L"Mate!!!");
			Sleep(5000);
			PostQuitMessage(0);
		}

	}
	if (Shah(x_king_2,y_king_2,2))
	{
		SetWindowText(hWnd, L"Shah!!!");
		if (Mate(x_king_2,y_king_2,2))
		{
			SetWindowText(hWnd, L"Mate!!!");
			Sleep(5000);
			PostQuitMessage(0);
		}
	}
}
Desk::~Desk()
{
	delete []arr;
}

void Desk::PawnToQueen()
{
	for (int i = 0;i<8;i++)
	{
		if (arr[0][i].GetSym() == 'P')
		{
			arr[0][i](0,i,'Q',arr[0][i].GetTeam());
		}
		if (arr[7][i].GetSym() == 'P')
		{
			arr[7][i](7,i,'Q',arr[7][i].GetTeam());
		}
	}
}
bool Desk::Mate(int x, int y, int team)
{
	int enemy;
	if (team == 1)
	{
		enemy = 2;
	}
	if (team == 2)
	{
		enemy = 1;
	}
	if (x + 1 < 8 && y + 1 < 8 && arr[x+1][y+1].GetTeam() != team && !Shah(x+1,y+1,team))
	{
		return false;
	}
	if (x + 1 < 8 && arr[x+1][y].GetTeam() != team && !Shah(x+1,y,team))
	{
		return false;
	}
	if (x + 1 < 8 && y - 1 >= 0 && arr[x+1][y-1].GetTeam() != team && !Shah(x+1,y-1,team))
	{
		return false;
	}
	if (y - 1 >= 0 && arr[x][y-1].GetTeam() != team && !Shah(x,y-1,team))
	{
		return false;
	}
	if (y + 1 >= 0 && arr[x][y+1].GetTeam() != team && !Shah(x,y+1,team))
	{
		return false;
	}
	if (x - 1 >= 0 && y - 1 >= 0 && arr[x-1][y-1].GetTeam() != team && !Shah(x-1,y-1,team))
	{
		return false;
	}
	if (x - 1 >= 0 && arr[x-1][y].GetTeam() != team && !Shah(x-1,y,team))
	{
		return false;
	}
	if (x - 1 >= 0 && y + 1 < 8 && arr[x-1][y+1].GetTeam() != team && !Shah(x-1,y+1,team))
	{
		return false;
	}
	return true;
}

void Desk::SetPosition(int x , int y , int x1, int y1)
{
	if (arr[x][y].GetSym() == 'P')
	{
		this->arr[x1][y1](x1,y1,'P',arr[x][y].GetTeam());
		this->arr[x][y](x,y,' ',0);
	}
	if (arr[x][y].GetSym() == 'O')
	{
		this->arr[x1][y1](x1,y1,'O',arr[x][y].GetTeam());
		this->arr[x][y](x,y,' ',0);
	}
	if (arr[x][y].GetSym() == 'C')
	{
		this->arr[x1][y1](x1,y1,'C',arr[x][y].GetTeam());
		this->arr[x][y](x,y,' ',0);		
	}
	if (arr[x][y].GetSym() == 'H')
	{
		this->arr[x1][y1](x1,y1,'H',arr[x][y].GetTeam());
		this->arr[x][y](x,y,' ',0);
	}
	if (arr[x][y].GetSym() == 'Q')
	{

		this->arr[x1][y1](x1,y1,'Q',arr[x][y].GetTeam());
		this->arr[x][y](x,y,' ',0);	
	}
	if (arr[x][y].GetSym() == 'K')
	{
		this->arr[x1][y1](x1,y1,'K',arr[x][y].GetTeam());
		this->arr[x][y](x,y,' ',0);
	}
}
void CharToWchar(const char * str, wchar_t * wstr)
{
	if (wstr)
		delete []wstr;
	wstr = new wchar_t [strlen(str)+1];
	for (int i = 0;i<strlen(str)+1;i++)
	{
		wstr[i] = wchar_t(str[i]);
	}
}
void WcharToChar(char * str1, const wchar_t * wstr)
{
	if (str1)
		delete []str1;
	str1 = new char [wcslen(wstr)+1];
	for (int i = 0;i<wcslen(wstr)+1;i++)
	{
		str1[i] = char(wstr[i]);
	}
}
void Desk::Save(wchar_t * player1, wchar_t * player2, int team_go)
{
	ofstream fout;
	fout.open("chess.dat", ios::binary | ios::out);

	for (int i = 0;i<8;i++)
	{
		for (int j = 0;j<8;j++)
		{
			int x = arr[i][j].GetX();
			int y = arr[i][j].GetY();
			int team = arr[i][j].GetTeam();
			char sym = arr[i][j].GetSym();
			fout.write((char*)&x,sizeof(int));
			fout.write((char*)&y,sizeof(int));
			fout.write((char*)&team,sizeof(int));
			fout.write((char*)&sym,sizeof(char));
		}
	}
	int string_length_player1 = wcslen(player1);
	fout.write((char*)&string_length_player1,sizeof(int));
	int string_length_player2 = wcslen(player2);
	fout.write((char*)&string_length_player2,sizeof(int));
	char * buffer_for_player1 = new char [string_length_player1+1];
	WcharToChar(buffer_for_player1, player1);
	char * buffer_for_player2 = new char [string_length_player2+1];
	WcharToChar(buffer_for_player2, player2);
	fout.write((char*)buffer_for_player1,string_length_player1);
	fout.write((char*)buffer_for_player2,string_length_player2);
	fout.write((char*)&team_go,sizeof(int));
	fout.close();
}
void Desk::Open(string& player11, string& player22, int& team_go)
{
	
	FILE * file = fopen("chess.dat", "rb");
	int length = filelength(_fileno(file));
	fclose(file);
	ifstream fin;
	fin.open("chess.dat",ios::binary | ios::in);
	for (int i = 0;i<8;i++)
	{
		for (int j = 0;j<8;j++)
		{
			int x,y,team;
			char sym;
			int length;
			fin.read((char*)&x, sizeof(int));
			fin.read((char*)&y, sizeof(int));
			fin.read((char*)&team, sizeof(int));
			fin.read((char*)&sym, sizeof(char));
			arr[i][j](x,y,sym,team);
		}
	}
	int string_length_player1, string_length_player2;
	fin.read((char*)&string_length_player1, sizeof(int));
	fin.read((char*)&string_length_player2, sizeof(int));
	char * player1, * player2;
	player1 = new char [string_length_player1+1];
	fin.read(player1,string_length_player1);
	player1[string_length_player1] = '\0';
	player2 = new char  [string_length_player2+1];
	fin.read((char*)player2,string_length_player2);
	player2[string_length_player2] = '\0';
	player11.append(player1);
	player22.append(player2);
	fin.read((char*)&team_go,sizeof(int));
	fin.close();
}


#endif