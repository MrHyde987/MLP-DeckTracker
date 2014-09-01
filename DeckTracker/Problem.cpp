
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
	std::cout << boost::format("%1% (%2% Owned)\nRarity: %3%\nPrimary Colour/Cost: %4%/%5%\nSecondary Colour/Cost: %6%/%7%\nNeutral Cost: %8%\nBonus: %9%\nStarting: %10%") 
		% accessName() % accessFrequency() % Card::rarityToString(accessRarity()) % Card::colourToString(primaryColour) % primaryColourConfrontCost 
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
			if (modifyName(inputToAdd)) {
				std::cout << "Card Rarity: ";
				break;
			}
			else {
				std::cout << "ERROR: Invalid name entered for Problem.\nName: ";
				return false;
			}
		case(1) :
			// Rarity
			prospectiveRarity = Card::stringToRarity(inputToAdd);
			if (modifyRarity(inputToAdd)) {
				std::cout << "Bonus Value: ";
				break;
			}
			else {
				std::cout << "ERROR: Invalid Rarity entered for Problem.\n";
				Card::printAcceptableRarities();
				std::cout << "Rarity: ";
				return false;
			}
		case(2) :
			// Bonus Value
			if (StringUtility::checkIsPositiveInt(inputToAdd)) {
				pointBonus = StringUtility::stringToInt(inputToAdd);
				std::cout << "Starting: ";
				break;
			}
			else {
				std::cout << "ERROR: Invalid Bonus Value entered for Problem.\nBonus Value: ";
				return false;
			}
		case(3) :
			// Is Starting Problem?
			if (StringUtility::checkIsBool(inputToAdd)) {
				isStarting = StringUtility::stringToBool(inputToAdd);
				std::cout << "Primary Colour: ";
				break;
			}
			else {
				std::cout << "ERROR: Invalid is Starting value entered for Problem.\nStarting? ";
				return false;
			}
		case(4) :
			// Primary Colour
			prospectiveColour = Card::stringToColour(inputToAdd);
			if (prospectiveColour != COLOUR_INVALID) {
				primaryColour = prospectiveColour;
				// Prompt for next field:
				std::cout << "Primary Colour Confront Cost: ";
				break;
			}
			else {
				std::cout << "ERROR: Invalid colour passed to Problem.\n";
				Card::printAcceptableColours(false);
				std::cout << "Primary Colour: ";
				return false;
			}
		case(5) :
			// Primary Colour Confront Cost
			if (StringUtility::checkIsPositiveInt(inputToAdd)) {
				primaryColourConfrontCost = StringUtility::stringToInt(inputToAdd);
				std::cout << "Secondary Colour (\"None\" if any): ";
				break;
			}
			else {
				std::cout << "ERROR: Invalid Primary Confront Cost entered for Problem.\nPrimary Colour Confront Cost: ";
				return false;
			}
		case(6) :
			// Primary Colour
			prospectiveColour = Card::stringToColour(inputToAdd);
			if (prospectiveColour != COLOUR_INVALID) {
				secondaryColour = prospectiveColour;
				// Prompt for next field:
				std::cout << "Secondary Colour Confront Cost: ";
				break;
			}
			else {
				std::cout << "ERROR: Invalid colour passed to Problem.\n";
				Card::printAcceptableColours(true);
				std::cout << "Secondary Colour: ";
				return false;
			}
		case(7) :
			// Secondary Colour Confront Cost
			if (StringUtility::checkIsPositiveInt(inputToAdd)) {
				secondaryColourConfrontCost = StringUtility::stringToInt(inputToAdd);
				std::cout << "Opponent's Confront Cost: ";
				break;
			}
			else {
				std::cout << "ERROR: Invalid Secondary Confront Cost entered for Problem.\nSecondary Colour Confront Cost: ";
				return false;
			}
		case(8) :
			// Opponent's Confront Cost
			if (StringUtility::checkIsPositiveInt(inputToAdd)) {
				neutralConfrontCost = StringUtility::stringToInt(inputToAdd);
				std::cout << "Special Text: ";
				break;
			}
			else {
				std::cout << "ERROR: Invalid Opponent's Confront Cost entered for Problem.\nOpponent's Confront Cost: ";
				return false;
			}
		default :
			// Special Text is being added
			pushSpecialText(inputToAdd);
			return true;
	}

	incrementAddedFields();
	return true;
}

bool Problem::isCardComplete() {
	return accessFieldsAdded() >= NUM_FIELDS;
}