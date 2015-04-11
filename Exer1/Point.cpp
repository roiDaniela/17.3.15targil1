#include "Point.h"
#include <math.h>
bool Point::IsPointsAdjacent(const Point& pointToCompare) {
	return ( abs((*this - pointToCompare).getX() + (*this - pointToCompare).getY()) == 1 );
}
