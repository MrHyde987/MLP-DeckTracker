#include "Event.h"

#include "boost/format.hpp"
#include "StringUtility.h"

Event::Event() {}

Event::Event(string name) : FRE(name) {}

Event::Event(
	int actionCost,
	int developmentCost,
	Colour colour,
	int power,
	string name,
	vector<string> specialText) : FRE(actionCost, developmentCost, colour, power, name, specialText) {}

Event::~Event() {}

bool Event::isCardComplete() {
	return accessFieldsAdded() >= NUM_FIELDS;
}

bool Event::addFields(string inputToAdd) {
	
	Colour prospectiveColour; // Declared up here to get around C2360

	switch (accessFieldsAdded()) {
		case (0) :
			// Require the name
			modifyName(inputToAdd);
			incrementAddedFields();
			cout << "Colour: ";
			return true;
		case (1) :
			// Require a Colour next
			prospectiveColour = Card::stringToColour(inputToAdd);
			if (prospectiveColour != COLOUR_INVALID) {
				modifyColour(prospectiveColour);
				incrementAddedFields();
				// Prompt for next field:
				cout << "Action Cost: ";
				return true;
			}
			else {
				cout << "ERROR: Invalid colour passed to Event.\nColour :";
				return false;
			}
		case (2) :
			// Action Cost
			if (StringUtility::checkIsPositiveInt(inputToAdd)) {
				modifyActionCost(StringUtility::stringToInt(inputToAdd));
				incrementAddedFields();
				cout << "Colour Cost (0 if none): ";
				return true;
			}
			else {
				cout << "ERROR: Invalid Action Cost entered for Event.\nAction Cost: ";
				return false;
			}
		case (3) :
			// Colour Cost
			if (StringUtility::checkIsPositiveInt(inputToAdd)) {
				modifyDevelopmentCost(StringUtility::stringToInt(inputToAdd));
				incrementAddedFields();
				cout << "Faceoff Power: ";
				return true;
			}
			else {
				cout << "ERROR: Invalid Colour Cost entered for Event.\nColour Cost (0 if none): ";
				return false;
			}
		case (4) :
			// Faceoff Power
			if (StringUtility::checkIsPositiveInt(inputToAdd)) {
				modifyPower(StringUtility::stringToInt(inputToAdd));
				incrementAddedFields();
				cout << "Special Text: ";
				return true;
			}
			else {
				cout << "ERROR: Invalid Faceoff Power entered for Event.\nFaceoff Power: ";
				return false;
			}
		default:
			// Special Text is being added
			pushSpecialText(inputToAdd);
			return true;
	}

	// The function should not fall through to here.
	cout << "ERROR: There is a bug in addFields() in Event." << endl;
	return false;
}

void Event::printStats() {
	std::cout << boost::format("%1%\nAction Cost: %2%\nColour: %3%\nColour Cost: %4%\nSpecial Text:")
		% accessName() % accessActionCost() % Card::colourToString(accessColour()) 
		% accessDevelopmentCost() << std::endl;

	printSpecialText();
}