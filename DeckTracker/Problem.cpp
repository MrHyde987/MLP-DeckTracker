
#include "Problem.h"
#include "StringUtility.h"
#include "boost/format.hpp"

Problem::Problem() {}
Problem::Problem(string name) : Card(name) {}
Problem::Problem(
	int pointBonus,
	int neutralConfrontCost,
	Colour primaryColour,
	Colour secondaryColour,
	int primaryColourConfrontCost,
	int secondaryColourConfrontCost,
	bool isStarting,
	string name,
	vector<string> specialText) : Card(name, specialText) {

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
	std::cout << boost::format("%1%\nPrimary Colour/Cost: %2%/%3%\nSecondary Colour/Cost: %4%/%5%\nNeutral Cost: %6%\nBonus: %7%\nStarting: %8%\nSpecial Text:") 
		% accessName() % Card::colourToString(primaryColour) % primaryColourConfrontCost 
		% Card::colourToString(secondaryColour) % secondaryColourConfrontCost % neutralConfrontCost % pointBonus 
		% (isStarting ? "True" : "False") << std::endl;
	printSpecialText();
}

bool Problem::addFields(string inputToAdd) {
	
	Colour prospectiveColour;

	switch (accessFieldsAdded()) {

		case(0) :
			// Require the name
			modifyName(inputToAdd);
			incrementAddedFields();
			cout << "Bonus Value: ";
			return true;
		case(1) :
			// Bonus Value
			if (StringUtility::checkIsPositiveInt(inputToAdd)) {
				pointBonus = StringUtility::stringToInt(inputToAdd);
				incrementAddedFields();
				cout << "Starting: ";
				return true;
			}
			else {
				cout << "ERROR: Invalid Bonus Value entered for Problem.\nBonus Value: ";
				return false;
			}
		case(2) :
			// Is Starting Problem?
			if (StringUtility::checkIsBool(inputToAdd)) {
				isStarting = StringUtility::stringToBool(inputToAdd);
				incrementAddedFields();
				cout << "Primary Colour: ";
				return true;
			}
			else {
				cout << "ERROR: Invalid is Starting value entered for Problem.\nStarting? ";
				return false;
			}
		case(3) :
			// Primary Colour
			prospectiveColour = Card::stringToColour(inputToAdd);
			if (prospectiveColour != COLOUR_INVALID) {
				primaryColour = prospectiveColour;
				incrementAddedFields();
				// Prompt for next field:
				cout << "Primary Colour Confront Cost: ";
				return true;
			}
			else {
				cout << "ERROR: Invalid colour passed to Problem.\nPrimary Colour :";
				return false;
			}
		case(4) :
			// Primary Colour Confront Cost
			if (StringUtility::checkIsPositiveInt(inputToAdd)) {
				primaryColourConfrontCost = StringUtility::stringToInt(inputToAdd);
				incrementAddedFields();
				cout << "Secondary Colour (\"None\" if any): ";
				return true;
			}
			else {
				cout << "ERROR: Invalid Primary Confront Cost entered for Problem.\nPrimary Colour Confront Cost: ";
				return false;
			}
		case(5) :
			// Primary Colour
			prospectiveColour = Card::stringToColour(inputToAdd);
			if (prospectiveColour != COLOUR_INVALID) {
				secondaryColour = prospectiveColour;
				incrementAddedFields();
				// Prompt for next field:
				cout << "Secondary Colour Confront Cost: ";
				return true;
			}
			else {
				cout << "ERROR: Invalid colour passed to Problem.\nSecondary Colour (\"None\" if any):";
				return false;
			}
		case(6) :
			// Secondary Colour Confront Cost
			if (StringUtility::checkIsPositiveInt(inputToAdd)) {
				secondaryColourConfrontCost = StringUtility::stringToInt(inputToAdd);
				incrementAddedFields();
				cout << "Opponent's Confront Cost: ";
				return true;
			}
			else {
				cout << "ERROR: Invalid Secondary Confront Cost entered for Problem.\nSecondary Colour Confront Cost: ";
				return false;
			}
		case(7) :
			// Opponent's Confront Cost
			if (StringUtility::checkIsPositiveInt(inputToAdd)) {
				neutralConfrontCost = StringUtility::stringToInt(inputToAdd);
				incrementAddedFields();
				cout << "Special Text: ";
				return true;
			}
			else {
				cout << "ERROR: Invalid Opponent's Confront Cost entered for Problem.\nOpponent's Confront Cost: ";
				return false;
			}
		default :
			// Special Text is being added
			pushSpecialText(inputToAdd);
			return true;
	}

	// Execution should not fall through to here.
	cout << "ERROR: There is a bug in Problem::addFields" << endl;
	return false;
}

bool Problem::isCardComplete() {
	return accessFieldsAdded() >= NUM_FIELDS;
}