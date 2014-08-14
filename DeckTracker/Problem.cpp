
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
	Rarity rarity,
	vector<string> specialText) : Card(name, rarity, specialText) {

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
	std::cout << boost::format("%1%\nRarity: %2%\nPrimary Colour/Cost: %3%/%4%\nSecondary Colour/Cost: %5%/%6%\nNeutral Cost: %7%\nBonus: %8%\nStarting: %9%\nSpecial Text:") 
		% accessName() % Card::rarityToString(accessRarity()) % Card::colourToString(primaryColour) % primaryColourConfrontCost 
		% Card::colourToString(secondaryColour) % secondaryColourConfrontCost % neutralConfrontCost % pointBonus 
		% (isStarting ? "True" : "False") << std::endl;
	printSpecialText();
}

bool Problem::addFields(string inputToAdd) {
	
	Colour prospectiveColour;
	Rarity prospectiveRarity;

	switch (accessFieldsAdded()) {

		case(0) :
			// Require the name
			modifyName(inputToAdd);
			incrementAddedFields();
			std::cout  << "Card Rarity: ";
			return true;
		case(1) :
			// Rarity
			prospectiveRarity = Card::stringToRarity(inputToAdd);
			if (prospectiveRarity != RARITY_INVALID) {
				modifyRarity(prospectiveRarity);
				incrementAddedFields();
				std::cout  << "Bonus Value: ";
				return true;
			}
			else {
				std::cout  << "ERROR: Invalid Rarity entered for Problem.\nCard Rarity: ";
				return false;
			}
		case(2) :
			// Bonus Value
			if (StringUtility::checkIsPositiveInt(inputToAdd)) {
				pointBonus = StringUtility::stringToInt(inputToAdd);
				incrementAddedFields();
				std::cout  << "Starting: ";
				return true;
			}
			else {
				std::cout  << "ERROR: Invalid Bonus Value entered for Problem.\nBonus Value: ";
				return false;
			}
		case(3) :
			// Is Starting Problem?
			if (StringUtility::checkIsBool(inputToAdd)) {
				isStarting = StringUtility::stringToBool(inputToAdd);
				incrementAddedFields();
				std::cout  << "Primary Colour: ";
				return true;
			}
			else {
				std::cout  << "ERROR: Invalid is Starting value entered for Problem.\nStarting? ";
				return false;
			}
		case(4) :
			// Primary Colour
			prospectiveColour = Card::stringToColour(inputToAdd);
			if (prospectiveColour != COLOUR_INVALID) {
				primaryColour = prospectiveColour;
				incrementAddedFields();
				// Prompt for next field:
				std::cout  << "Primary Colour Confront Cost: ";
				return true;
			}
			else {
				std::cout  << "ERROR: Invalid colour passed to Problem.\nPrimary Colour :";
				return false;
			}
		case(5) :
			// Primary Colour Confront Cost
			if (StringUtility::checkIsPositiveInt(inputToAdd)) {
				primaryColourConfrontCost = StringUtility::stringToInt(inputToAdd);
				incrementAddedFields();
				std::cout  << "Secondary Colour (\"None\" if any): ";
				return true;
			}
			else {
				std::cout  << "ERROR: Invalid Primary Confront Cost entered for Problem.\nPrimary Colour Confront Cost: ";
				return false;
			}
		case(6) :
			// Primary Colour
			prospectiveColour = Card::stringToColour(inputToAdd);
			if (prospectiveColour != COLOUR_INVALID) {
				secondaryColour = prospectiveColour;
				incrementAddedFields();
				// Prompt for next field:
				std::cout  << "Secondary Colour Confront Cost: ";
				return true;
			}
			else {
				std::cout  << "ERROR: Invalid colour passed to Problem.\nSecondary Colour (\"None\" if any):";
				return false;
			}
		case(7) :
			// Secondary Colour Confront Cost
			if (StringUtility::checkIsPositiveInt(inputToAdd)) {
				secondaryColourConfrontCost = StringUtility::stringToInt(inputToAdd);
				incrementAddedFields();
				std::cout  << "Opponent's Confront Cost: ";
				return true;
			}
			else {
				std::cout  << "ERROR: Invalid Secondary Confront Cost entered for Problem.\nSecondary Colour Confront Cost: ";
				return false;
			}
		case(8) :
			// Opponent's Confront Cost
			if (StringUtility::checkIsPositiveInt(inputToAdd)) {
				neutralConfrontCost = StringUtility::stringToInt(inputToAdd);
				incrementAddedFields();
				std::cout  << "Special Text: ";
				return true;
			}
			else {
				std::cout  << "ERROR: Invalid Opponent's Confront Cost entered for Problem.\nOpponent's Confront Cost: ";
				return false;
			}
		default :
			// Special Text is being added
			pushSpecialText(inputToAdd);
			return true;
	}

	// Execution should not fall through to here.
	std::cout  << "ERROR: There is a bug in Problem::addFields" << endl;
	return false;
}

bool Problem::isCardComplete() {
	return accessFieldsAdded() >= NUM_FIELDS;
}