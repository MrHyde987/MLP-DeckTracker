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
	string name,
	vector<string> specialText) : FRE(actionCost, developmentCost, colour, power, name, specialText) {

	this->location = location;
}

Resource::~Resource() {}

void Resource::printStats() {

	std::cout << boost::format("%1%\nAction Cost: %2%\nColour: %3%\nColour Cost: %4%\nPower: %5%\nLocation: %6%\nSpecial Text:")
		% accessName() % accessActionCost() % Card::colourToString(accessColour()) % accessDevelopmentCost() 
		% accessPower() % locationToString(location) << std::endl;
	printSpecialText();
}

void Resource::formatPrompt() {
	cout << "For Resources, please use the following input format:" << endl;
	cout << "[Name],[Colour],[Action Cost],[Colour Cost],[Power],[Location],[Special Text]" << endl;
}

bool Resource::validateInput(vector<string> input) {

	bool validityFlag = false;

	if (input.size() < NUM_PROPERTIES) {
		cout << "ERROR: Invalid number of arguments passed to Resource." << endl;
		return false;
	}

	// Proper colour
	Colour prospectiveColour = Card::stringToColour(input[1]);

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
	Location prospectiveLocation = stringToLocation(input[5]);

	if (prospectiveLocation == LOCATION_INVALID) {
		cout << "ERROR: Invalid location passed to Resource." << endl;
		return false;
	}

	return validityFlag;
}

void Resource::buildCard(vector<string> formattedInput) {

	modifyName(formattedInput[0]);
	modifyColour(Card::stringToColour(formattedInput[1]));
	modifyActionCost(SafeStringConversion::stringToInt(formattedInput[2]));
	modifyDevelopmentCost(SafeStringConversion::stringToInt(formattedInput[3]));
	modifyPower(SafeStringConversion::stringToInt(formattedInput[4]));
	location = stringToLocation(formattedInput[5]);
	// All further strings treated as special text.
	vector<string> specialText;
	for (unsigned int i = NUM_PROPERTIES - 1; i < formattedInput.size(); ++i) {
		specialText.push_back(formattedInput[i]);
	}
	modifySpecialText(specialText);
}

Location Resource::stringToLocation(string toConvert) {

	Location newLocation;
	SafeStringConversion::toLowerCase(toConvert);
	
	if (toConvert.compare("home") == 0)
		newLocation = LOCATION_HOME;
	else if (toConvert.compare("friend") == 0)
		newLocation = LOCATION_FRIEND;
	else if (toConvert.compare("opposing friend") == 0)
		newLocation = LOCATION_OPPOSING_FRIEND;
	else if (toConvert.compare("trouble maker") == 0)
		newLocation = LOCATION_TM;
	else if (toConvert.compare("problem") == 0)
		newLocation = LOCATION_PROBLEM;
	else if (toConvert.compare("mane character") == 0)
		newLocation = LOCATION_MC;
	else if (toConvert.compare("opposing mane character") == 0)
		newLocation = LOCATION_OPPOSING_MC;
	else
		newLocation = LOCATION_INVALID;

	return newLocation;
}

string Resource::locationToString(Location toConvert) {

	string toRet;
	switch (toConvert) {
		case (LOCATION_HOME) :
			toRet = "Played at Home";
			break;
		case (LOCATION_FRIEND) :
			toRet = "Played on a Friend";
			break;
		case (LOCATION_OPPOSING_FRIEND) :
			toRet = "Played on opponent's Friend";
			break;
		case (LOCATION_TM) :
			toRet = "Played on a Trouble Maker";
			break;
		case (LOCATION_PROBLEM) :
			toRet = "Played on a Problem";
			break;
		case (LOCATION_MC) :
			toRet = "Played on a Mane Character";
			break;
		case (LOCATION_OPPOSING_MC) :
			toRet = "Played on opponent's Mane Character";
			break;
		default :
			toRet = "ERROR: Attempted to convert invalid Resource location.";
	}

	return toRet;
}