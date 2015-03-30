#include "randomOutput.h"
// Methods


int RandomOutput::CreateRandomValue(unsigned int range_to, unsigned int range_from){
	
	srand((unsigned int)0);
	return (range_from + (rand() % (range_to - range_from)));
}
Sign::Operator RandomOutput::CreateRandomSign(){

	return (Sign::Operator) CreateRandomValue(Sign::Operator::DIV, Sign::MINUS);
}

int RandomOutput::CreateRandomValue(ScreenData* sData, unsigned int range_to, unsigned int range_from){
	
	int temp = CreateRandomValue(range_from, range_to);
	
	while (sData->is_number_exist(temp))
		temp = CreateRandomValue(range_from, range_to);
	
	return temp;
}

Point RandomOutput::CreateRandomPoint(ScreenData* sData){
	Point* p = new Point(CreateRandomPoint(LENGH_OF_LINE * LENGH_OF_PAGE, LENGH_OF_LINE * AMOUNT_OF_INSTRUCTIONS_LINE));
	bool succeded = !sData->isPointNearOrInsideOtherPoint( p );
	for (int i = 0; i < 9 && !succeded; i++)
	{
		p = new Point(CreateRandomPoint(LENGH_OF_LINE * LENGH_OF_PAGE, LENGH_OF_LINE * AMOUNT_OF_INSTRUCTIONS_LINE));
		succeded = !sData->isPointNearOrInsideOtherPoint( p );
	}

	// if succeded return p else return null
	p = (succeded ? p : NULL);
	
	return *p;
}
