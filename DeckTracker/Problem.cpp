
#include "Problem.h"
#include "boost/format.hpp"

Problem::Problem(
	int pointBonus,
	int neutralConfrontCost,
	Colour primaryColour,
	Colour secondaryColour,
	int primaryColourConfrontCost,
	int secondaryColourConfrontCost,
	bool isStarting,
	std::string name,
	std::string specialText) : Card(name, specialText) {

	this->pointBonus = pointBonus;
	this->neutralConfrontCost = neutralConfrontCost;
	this->primaryColour = primaryColour;
	this->secondaryColour = secondaryColour;
	this->primaryColourConfrontCost = primaryColourConfrontCost;
	this->secondaryColourConfrontCost = secondaryColourConfrontCost;
	this->isStarting = isStarting;
}

Problem::~Problem() {}

void Problem::printStats() {

	std::cout << "Card Details: " << std::endl;
	// TODO: Nicely formatted output
	//		 I need the colours to print out as letters rather than numbers...

	std::cout << boost::format("%1%   %2%/%3% %4%/%5% %6% %7% %8%") 
		% accessName() % primaryColour % primaryColourConfrontCost 
		% secondaryColour % secondaryColourConfrontCost % neutralConfrontCost % pointBonus 
		% isStarting << std::endl;
}