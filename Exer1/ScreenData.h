#ifndef _SCREENDATA_H_
#define _SCREENDATA_H_
#include <list>
#include "Point.h"
class ScreenData
{
	std::list< int > Data;
	


	bool is_point_exist(Point& ptPoint);
	bool insert_point(Point & ptPoint);
	void clear_data();
};

#endif