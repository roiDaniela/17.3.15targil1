#include "randomOutput.h"
// Methods


int RandomOutput::CreateRandomValue(unsigned int range_from, unsigned int range_to){
	
	srand((unsigned int)0);

	return (range_from + rand() % range_to);
}
Sign::Operator RandomOutput::CreateRandomSign(){

	return (Sign::Operator) CreateRandomValue(Sign::Operator::MINUS, Sign::DIV);
}

int RandomOutput::CreateRandomValue(ScreenData* sData, unsigned int range_from, unsigned int range_to){
	
	int temp = CreateRandomValue(range_from, range_to);
	
	while (sData->is_number_exist(temp))
		temp = CreateRandomValue(range_from, range_to);
	
	return temp;
}