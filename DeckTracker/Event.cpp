#include "Event.h"

#include "boost/format.hpp"
#include "SafeStringConversion.h"

Event::Event() {}

Event::Event(
	int actionCost,
	int developmentCost,
	Colour colour,
	int power,
	string name,
	vector<string> specialText) : FRE(actionCost, developmentCost, colour, power, name, specialText) {}

Event::~Event() {}

void Event::formatPrompt() {
	cout << "For Events, please use the following input format:" << endl;
	cout << "[Name],[Colour],[Action Cost],[Colour Cost],[Power],[Special Text]" << endl;
}

bool Event::validateInput(vector<string> input) {

	bool validityFlag = true;

	if (input.size() < NUM_PROPERTIES) {
		cout << "ERROR: Invalid number of arguments passed to Event." << endl;
		return false;
	}
	// Proper colour
	Colour prospectiveColour = Card::stringToColour(input[1]);

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
	modifyColour(Card::stringToColour(formattedInput[1]));
	modifyActionCost(SafeStringConversion::stringToInt(formattedInput[2]));
	modifyDevelopmentCost(SafeStringConversion::stringToInt(formattedInput[3]));
	modifyPower(SafeStringConversion::stringToInt(formattedInput[4]));
	// All further strings treated as special text.
	vector<string> specialText;
	for (unsigned int i = NUM_PROPERTIES - 1; i < formattedInput.size(); ++i) {
		specialText.push_back(formattedInput[i]);
	}
	modifySpecialText(specialText);

}

void Event::printStats() {
	std::cout << boost::format("%1%\nAction Cost: %2%\nColour: %3%\nColour Cost: %4%\nSpecial Text:")
		% accessName() % accessActionCost() % Card::colourToString(accessColour()) 
		% accessDevelopmentCost() << std::endl;

	printSpecialText();
}