#ifndef _POINT_H
#define _POINT_H

#include<iostream>
using namespace std;

class Point
{
private:	
	int x,y; 
public:
	Point(int x, int y){ this->x = x; this->y = y; }
	int getX(){ return x; };
	void setX(int x){ this->x = x; };
	int getY(){ return y; };
	void setY(int y){ this->y = y; };
};

#endif