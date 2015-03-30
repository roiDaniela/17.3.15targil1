#include "randomOutput.h"


int RandomOutput::CreateRandomValue(unsigned int range_to, unsigned int range_from){
	
	srand((unsigned int)0);
	return (range_from + (rand() % (range_to - range_from)));
}

Sign::Operator RandomOutput::CreateRandomSign(){

	return (Sign::Operator) CreateRandomValue(Sign::Operator::DIV, Sign::MINUS);
}

int RandomOutput::CreateRandomValue(ScreenData* sData, unsigned int range_to, unsigned int range_from){
	
	int temp = CreateRandomValue(range_to, range_from);
	
	while (sData->is_number_exist(temp))
		temp = CreateRandomValue(range_to, range_from);
	
	return temp;
}

Point RandomOutput::randomPointInScreen(ScreenData* sData){
	Point* p = new Point(CreateRandomPoint(LENGH_OF_LINE * LENGH_OF_PAGE, LENGH_OF_LINE * AMOUNT_OF_INSTRUCTIONS_LINE));
	bool succeded = !isPointNearOrInsideOtherPoint(sData, p);
	for (int i = 0; i < 9 && !succeded; i++)
	{
		p = new Point(CreateRandomPoint(LENGH_OF_LINE * LENGH_OF_PAGE, LENGH_OF_LINE * AMOUNT_OF_INSTRUCTIONS_LINE));
		succeded = !isPointNearOrInsideOtherPoint(sData, p);
	}

	// if succeded return p else return null
	p = (succeded ? p : NULL);
	
	return *p;
}

bool RandomOutput::isPointNearOrInsideOtherPoint(ScreenData* sData, Point* p){
	// Init pointer for all problematic locations
	Point* pUp = new Point(p->getX(), p->getY() - 1);
	Point* pDown = new Point(p->getX(), p->getY() + 1);
	Point* pLeft = new Point(p->getX() - 1, p->getY());
	Point* pRight = new Point(p->getX() + 1, p->getY());

	// return if this locations arealrdy full
	return (sData->is_point_exist(*p) ||
			sData->is_point_exist(*pUp) ||
			sData->is_point_exist(*pDown) ||
			sData->is_point_exist(*pRight) ||
			sData->is_point_exist(*pLeft));
}