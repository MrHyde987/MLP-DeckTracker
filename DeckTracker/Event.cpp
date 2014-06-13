#include "Event.h"
#include "boost/format.hpp"

Event::Event(
	int actionCost,
	int developmentCost,
	Colour colour,
	int power,
	std::string name,
	std::string specialText) : FRE(actionCost, developmentCost, colour, power, name, specialText) {}

Event::~Event() {}

void Event::printStats() {
	std::cout << boost::format("%1%  Action Cost:%2% Colour:%3% Colour Cost:%4%")
		% accessName() % accessActionCost() % accessColour() % accessDevelopmentCost() << std::endl;
}