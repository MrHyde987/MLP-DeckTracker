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
	vector<string> typeModifiers,
	string name,
	Rarity rarity,
	vector<string> specialText) : FRE(actionCost, developmentCost, colour, power, typeModifiers, name, rarity, specialText) {}

Event::~Event() {}

bool Event::isCardComplete() {
	return accessFieldsAdded() >= NUM_FIELDS;
}

bool Event::addFields(string inputToAdd) {

	switch (accessFieldsAdded()) {
		case (0) :
			// Require the name
			if (modifyName(inputToAdd)) {
				std::cout << "Rarity: ";
				break;
			}
			else {
				std::cout << "ERROR: Invalid name entered for Event.\n";
				std::cout << "Name: ";
				return false;
			}
		case(1) :
			// Rarity
			if (modifyRarity(inputToAdd)) {
				std::cout << "Type Modifiers (e.g. Gotcha etc.): ";
				break;
			}
			else {
				std::cout << "ERROR: Invalid Rarity entered for Event.\n";
				printAcceptableRarities();
				std::cout << "Rarity: ";
				return false;
			}
		case (2) :
			// Type Modifiers
			if (pushTypeModifier(inputToAdd))
				return true;
			else {
				std::cout << "Colour: ";
				break;
			}
		case (3) :
			// Require a Colour next
			if (modifyColour(inputToAdd)) {
				std::cout << "Action Cost: ";
				break;
			}
			else {
				std::cout << "ERROR: Invalid colour passed to Event.\n";
				printAcceptableColours(true);
				std::cout << "Colour: ";
				return false;
			}
		case (4) :
			// Action Cost
			if (modifyActionCost(inputToAdd)) {
				std::cout << "Colour Cost (0 if none): ";
				break;
			}
			else {
				std::cout << "ERROR: Invalid Action Cost entered for Event.\nAction Cost: ";
				return false;
			}
		case (5) :
			// Colour Cost
			if (modifyDevelopmentCost(inputToAdd)) {
				std::cout << "Faceoff Power: ";
				break;
			}
			else {
				std::cout << "ERROR: Invalid Colour Cost entered for Event.\nColour Cost (0 if none): ";
				return false;
			}
		case (6) :
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
	std::cout << boost::format("%1% (%2% Owned)\nAction Cost: %3%\nColour: %4%\nColour Cost: %5%")
		% accessName() % accessFrequency() % accessActionCost() % Card::colourToString(accessColour()) 
		% accessDevelopmentCost() << std::endl;
	printTypeModifiers();
	printSpecialText();
}