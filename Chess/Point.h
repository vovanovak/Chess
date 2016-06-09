#pragma once
#ifndef POINT_H
#include <iostream>
#include <Windows.h>
#include <iomanip>
using namespace std;
class Point
{
protected:
	int x;
	int y;
	int team;
	char sym;
public:
	Point();
	Point(int x, int y, char sym, int team);
	void operator () (int x, int y, char sym, int team);
	void Print();
	char GetSym() {return sym;}
	int GetTeam() {return team;}
	int GetX()	  {return x;}
	int GetY()	  {return y;}
};
Point::Point()
{
	x = 0;
	y = 0;
	sym = ' ';
	team = 0;
}
Point::Point(int x, int y, char sym, int team)
{
	this->x = x;
	this->y = y;
	this->sym = sym;
	this->team = team;
}
void Point::operator () (int x, int y, char sym, int team)
{
	this->x = x;
	this->y = y;
	this->sym = sym;
	this->team = team;
}
void SetColor(int text, int background)
{
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text));
}
void SetPosition(int x,int y)
{
	COORD position = {x,y}; //позиция x и y
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsole, position);
}
void Point::Print()
{
	cout << setw(2) << sym;
}
#endif