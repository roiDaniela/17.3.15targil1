
#include "ScreenData.h"


bool ScreenData::is_point_exist(const Point& ptPoint)
{
	unsigned int x, y;

	for (std::list<Point>::iterator curr_point = Data.begin(); curr_point != Data.end(); ++curr_point)
		if (true)
			return true;
	return false;
}

void ScreenData::insert_point(const Point & ptPoint)
{
	Data.push_back(ptPoint);
}

void ScreenData::clear_data(){
	Data.clear();
}
