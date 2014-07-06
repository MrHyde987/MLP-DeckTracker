
#include "Problem.h"
#include "SafeStringConversion.h"
#include "boost/format.hpp"

Problem::Problem() {}

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

void Problem::formatPrompt() {
	cout << "For Problems, please use the following input format:" << endl;
	cout << "[Name],[Point Value],[Starting?],[Colour #1],[Confront Cost #1],[Colour #2],[Confront Cost#2],[Neutral Confront Cost],[Special Text]" << endl;
}

bool Problem::validateInput(vector<string> input) {

	bool validityFlag = true;

	if (input.size() != NUM_PROPERTIES) {
		cout << "ERROR: Invalid number of arguments passed to Problem." << endl;
		return false;
	}

	// Point Value
	validityFlag = SafeStringConversion::checkIsInt(input[1]);

	if (!validityFlag) {
		cout << "ERROR: Invalid point value passed to Problem." << endl;
		return false;
	}

	// Is starting Problem?
	validityFlag = SafeStringConversion::checkIsBool(input[2]);

	if (!validityFlag) {
		cout << "ERROR: Invalid isStarting value passed to Problem." << endl;
		return false;
	}

	// Primary Colour
	Colour prospectiveColour = COLOUR_INVALID;
	validityFlag = SafeStringConversion::checkIsInt(input[3]);

	if (validityFlag)
		prospectiveColour = Card::intToColour(SafeStringConversion::stringToInt(input[3]));
	if (prospectiveColour == COLOUR_INVALID) {
		cout << "ERROR: Invalid primary colour passed to Problem." << endl;
		return false;
	}

	// Primary Colour Confront Cost
	validityFlag = SafeStringConversion::checkIsInt(input[4]);

	if (!validityFlag) {
		cout << "ERROR: Invalid primary colour confront cost passed to Problem." << endl;
		return false;
	}

	// Secondary Colour
	prospectiveColour = COLOUR_INVALID;
	validityFlag = SafeStringConversion::checkIsInt(input[5]);

	if (validityFlag)
		prospectiveColour = Card::intToColour(SafeStringConversion::stringToInt(input[5]));
	if (prospectiveColour == COLOUR_INVALID) {
		cout << "ERROR: Invalid secondary colour passed to Problem." << endl;
		return false;
	}

	// Secondary Colour Confront Cost
	validityFlag = SafeStringConversion::checkIsInt(input[6]);

	if (!validityFlag) {
		cout << "ERROR: Invalid secondary colour confront cost passed to Problem." << endl;
		return false;
	}

	// Neutral Confront Cost
	validityFlag = SafeStringConversion::checkIsInt(input[7]);

	if (!validityFlag) {
		cout << "ERROR: Invalid neutral confront cost passed to Problem." << endl;
		return false;
	}

	return validityFlag;
}

void Problem::buildCard(vector<string> formattedInput) {

	modifyName(formattedInput[0]);
	pointBonus = SafeStringConversion::stringToInt(formattedInput[1]);
	isStarting = SafeStringConversion::stringToBool(formattedInput[2]);
	primaryColour = Card::intToColour(SafeStringConversion::stringToInt(formattedInput[3]));
	primaryColourConfrontCost = SafeStringConversion::stringToInt(formattedInput[4]);
	secondaryColour = Card::intToColour(SafeStringConversion::stringToInt(formattedInput[5]));
	secondaryColourConfrontCost = SafeStringConversion::stringToInt(formattedInput[6]);
	neutralConfrontCost = SafeStringConversion::stringToInt(formattedInput[7]);
	modifySpecialText(formattedInput[8]);
}