#include "TroubleMaker.h"
#include "boost/format.hpp"

TroubleMaker::TroubleMaker(
	int pointValue,
	bool isVillain,
	Colour colour,
	int power,
	std::string name,
	std::string specialText) : PlayableCard(colour, power, name, specialText) {

	this->pointValue = pointValue;
	this->isVillain = isVillain;
}

TroubleMaker::~TroubleMaker() {}

void TroubleMaker::printStats() {

	std::cout << boost::format("%1%  V:%2% P:%3% Pts:%4%") 
		% accessName() % (isVillain ? "True " : "False") % accessPower() % pointValue << std::endl;
}