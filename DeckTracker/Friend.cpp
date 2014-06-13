#include "Friend.h"
#include "boost/format.hpp"

Friend::Friend(
	Species species,
	std::string typeModifiers,
	int actionCost,
	int developmentCost,
	Colour colour,
	int power,
	std::string name,
	std::string specialText) : FRE(actionCost, developmentCost, colour, power, name, specialText) {

	this->species = species;
	this->typeModifiers = typeModifiers;
}

Friend::~Friend() {}

void Friend::printStats() {

	// TODO: Test this to see if it overflows the line.
	std::cout << boost::format("%1%  Action Cost:%2% Colour:%3% Colour Cost:%4% Power:%5% Species:%6% Types:%7%") 
		% accessName() % accessActionCost() % accessColour()
		% accessDevelopmentCost() % accessPower() % species % typeModifiers << std::endl;
}