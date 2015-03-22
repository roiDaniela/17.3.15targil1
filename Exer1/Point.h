#ifndef _POINT_H
#define _POINT_H

#include<iostream>
using namespace std;

class Point
{
private:	
	unsigned int x,y; 
public:
	//Ctor
	Point(unsigned int x, unsigned int y){ this->x = x; this->y = y; }
	
	// Getter & setter
	unsigned getX(){ return x; };
	void setX(unsigned int x){ this->x = x; };
	unsigned int getY(){ return y; };
	void setY(unsigned int y){ this->y = y; };

	// Methods
	Point randomPoint(unsigned target, unsigned int start = 1){ rand() % target + start; }
};

#endif