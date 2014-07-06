#include "Resource.h"
#include "SafeStringConversion.h"
#include "boost/format.hpp"

Resource::Resource() {};

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

void Resource::formatPrompt() {
	cout << "For Resources, please use the following input format:" << endl;
	cout << "[Name],[Colour],[Action Cost],[Colour Cost],[Power],[Location],[Special Text]" << endl;
}

bool Resource::validateInput(vector<string> input) {

	bool validityFlag = false;

	if (input.size() != NUM_PROPERTIES) {
		cout << "ERROR: Invalid number of arguments passed to Resource." << endl;
		return false;
	}

	// Proper colour
	Colour prospectiveColour = COLOUR_INVALID;
	validityFlag = SafeStringConversion::checkIsInt(input[1]);

	if (validityFlag)
		prospectiveColour = Card::intToColour(SafeStringConversion::stringToInt(input[1]));
	if (prospectiveColour == COLOUR_INVALID) {
		cout << "ERROR: Invalid colour passed to Resource." << endl;
		return false;
	}

	// Action Cost
	validityFlag = SafeStringConversion::checkIsInt(input[2]);

	if (!validityFlag) {
		cout << "ERROR: Invalid action cost passed to Resource." << endl;
		return false;
	}

	// Colour Cost
	validityFlag = SafeStringConversion::checkIsInt(input[3]);

	if (!validityFlag) {
		cout << "ERROR: Invalid development cost passed to Resource." << endl;
		return false;
	}

	// Power
	validityFlag = SafeStringConversion::checkIsInt(input[4]);

	if (!validityFlag) {
		cout << "ERROR: Invalid power passed to Resource." << endl;
		return false;
	}

	// Location
	Location prospectiveLocation = LOCATION_INVALID;
	validityFlag = SafeStringConversion::checkIsInt(input[5]);

	if (validityFlag)
		prospectiveLocation = intToLocation(SafeStringConversion::stringToInt(input[5]));
	if (prospectiveLocation == LOCATION_INVALID) {
		cout << "ERROR: Invalid location passed to Resource." << endl;
		return false;
	}

	return validityFlag;
}

void Resource::buildCard(vector<string> formattedInput) {

	modifyName(formattedInput[0]);
	modifyColour(Card::intToColour(SafeStringConversion::stringToInt(formattedInput[1])));
	modifyActionCost(SafeStringConversion::stringToInt(formattedInput[2]));
	modifyDevelopmentCost(SafeStringConversion::stringToInt(formattedInput[3]));
	modifyPower(SafeStringConversion::stringToInt(formattedInput[4]));
	location = intToLocation(SafeStringConversion::stringToInt(formattedInput[5]));
	modifySpecialText(formattedInput[6]);
}

Location Resource::intToLocation(int toConvert) {

	Location newLocation;

	switch (toConvert) {
		case(0) :
			newLocation = LOCATION_HOME;
			break;
		case(1) :
			newLocation = LOCATION_FRIEND;
			break;
		case(2) :
			newLocation = LOCATION_OPPOSING_FRIEND;
			break;
		case(3) :
			newLocation = LOCATION_TM;
			break;
		case(4) :
			newLocation = LOCATION_PROBLEM;
			break;
		default:
			newLocation = LOCATION_INVALID;
			break;
	}

	return newLocation;
}