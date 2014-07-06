#include "Event.h"

#include "boost/format.hpp"
#include "SafeStringConversion.h"

Event::Event() {}

Event::Event(
	int actionCost,
	int developmentCost,
	Colour colour,
	int power,
	std::string name,
	std::string specialText) : FRE(actionCost, developmentCost, colour, power, name, specialText) {}

Event::~Event() {}

void Event::formatPrompt() {
	cout << "For Events, please use the following input format:" << endl;
	cout << "[Name],[Colour],[Action Cost],[Colour Cost],[Power],[Special Text]" << endl;
}

bool Event::validateInput(vector<string> input) {

	bool validityFlag = true;

	if (input.size() != NUM_PROPERTIES) {
		cout << "ERROR: Invalid number of arguments passed to Event." << endl;
		return false;
	}
	// Proper colour
	Colour prospectiveColour = COLOUR_INVALID;
	validityFlag = SafeStringConversion::checkIsInt(input[1]);

	if (validityFlag)
		prospectiveColour = Card::intToColour(SafeStringConversion::stringToInt(input[1]));
	if (prospectiveColour == COLOUR_INVALID) {
		cout << "ERROR: Invalid colour passed to Event." << endl;
		return false;
	}
	// Action Cost
	validityFlag = SafeStringConversion::checkIsInt(input[2]);

	if (!validityFlag) {
		cout << "ERROR: Invalid action cost passed to Event." << endl;
		return false;
	}
	// Colour Cost
	validityFlag = SafeStringConversion::checkIsInt(input[3]);

	if (!validityFlag) {
		cout << "ERROR: Invalid colour cost passed to Event." << endl;
		return false;
	}
	// Power
	validityFlag = SafeStringConversion::checkIsInt(input[4]);

	if (!validityFlag) {
		cout << "ERROR: Invalid Power passed to Event." << endl;
		return false;
	}

	return true;
}

void Event::buildCard(vector<string> formattedInput) {

	modifyName(formattedInput[0]);
	modifyColour(Card::intToColour(SafeStringConversion::stringToInt(formattedInput[1])));
	modifyActionCost(SafeStringConversion::stringToInt(formattedInput[2]));
	modifyDevelopmentCost(SafeStringConversion::stringToInt(formattedInput[3]));
	modifyPower(SafeStringConversion::stringToInt(formattedInput[4]));
	modifySpecialText(formattedInput[5]);

}

void Event::printStats() {
	std::cout << boost::format("%1%  Action Cost:%2% Colour:%3% Colour Cost:%4%")
		% accessName() % accessActionCost() % accessColour() % accessDevelopmentCost() << std::endl;
}