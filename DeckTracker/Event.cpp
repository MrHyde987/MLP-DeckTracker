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
	Rarity rarity,
	vector<string> specialText) : FRE(actionCost, developmentCost, colour, power, name, rarity, specialText) {}

Event::~Event() {}

bool Event::isCardComplete() {
	return accessFieldsAdded() >= NUM_FIELDS;
}

bool Event::addFields(string inputToAdd) {

	switch (accessFieldsAdded()) {
		case (0) :
			// Require the name
			modifyName(inputToAdd);
			std::cout << "Rarity: ";
			break;
		case(1) :
			// Rarity
			if (modifyRarity(inputToAdd)) {
				std::cout << "Colour: ";
				break;
			}
			else {
				std::cout << "ERROR: Invalid Rarity entered for Event.\n";
				printAcceptableRarities();
				std::cout << "Rarity: ";
				return false;
			}
		case (2) :
			// Require a Colour next
			if (modifyColour(inputToAdd)) {
				// Prompt for next field:
				std::cout << "Action Cost: ";
				break;
			}
			else {
				std::cout << "ERROR: Invalid colour passed to Event.\n";
				printAcceptableColours(true);
				std::cout << "Colour: ";
				return false;
			}
		case (3) :
			// Action Cost
			if (modifyActionCost(inputToAdd)) {
				std::cout << "Colour Cost (0 if none): ";
				break;
			}
			else {
				std::cout << "ERROR: Invalid Action Cost entered for Event.\nAction Cost: ";
				return false;
			}
		case (4) :
			// Colour Cost
			if (modifyDevelopmentCost(inputToAdd)) {
				std::cout << "Faceoff Power: ";
				break;
			}
			else {
				std::cout << "ERROR: Invalid Colour Cost entered for Event.\nColour Cost (0 if none): ";
				return false;
			}
		case (5) :
			// Faceoff Power
			if (modifyPower(inputToAdd)) {
				std::cout << "Special Text: ";
				break;
			}
			else {
				std::cout << "ERROR: Invalid Faceoff Power entered for Event.\nFaceoff Power: ";
				return false;
			}
		default:
			// Special Text is being added
			pushSpecialText(inputToAdd);
			return true;
	}

	incrementAddedFields();
	return true;
}

void Event::printStats() {
	std::cout << boost::format("%1% (%2% Owned)\nAction Cost: %3%\nColour: %4%\nColour Cost: %5%\nSpecial Text:")
		% accessName() % accessFrequency() % accessActionCost() % Card::colourToString(accessColour()) 
		% accessDevelopmentCost() << std::endl;

	printSpecialText();
}