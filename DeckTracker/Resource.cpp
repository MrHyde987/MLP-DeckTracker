#include "Resource.h"
#include "boost/format.hpp"

Resource::Resource(
	Location location,
	int actionCost,
	int developmentCost,
	Colour colour,
	int power,
	std::string name,
	std::string specialText) : FRE(actionCost, developmentCost, colour, power, name, specialText) {

	this->location = location;
}

Resource::~Resource() {}

void Resource::printStats() {

	std::cout << boost::format("%1%  Action Cost:%2% Colour:%3% Colour Cost:%4% Power:%5% Location:%6%")
		% accessName() % accessActionCost() % accessColour() % accessDevelopmentCost() 
		% accessPower() % location << std::endl;
}