#ifndef _SCREENDATA_H_
#define _SCREENDATA_H_
#include <list>
#include "Point.h"

class ScreenData
{

private:
	std::list< Point > Data;
	
public:
	bool is_point_exist(const Point& ptPoint);
	void insert_point(const Point& ptPoint);
	void clear_data();

};

#endif