#include "Friend.h"
#include "StringUtility.h"
#include "boost/format.hpp"

Friend::Friend() {}

Friend::Friend(string name) : FRE(name) {}

Friend::Friend(
	Species species,
	int actionCost,
	int developmentCost,
	Colour colour,
	int power,
	vector<string> typeModifiers,
	string name,
	Rarity rarity,
	vector<string> specialText) : FRE(actionCost, developmentCost, colour, power, typeModifiers, name, rarity, specialText) {

	this->species = species;
}

Friend::~Friend() {}

void Friend::printStats() {

	std::cout << boost::format("%1% (%2% Owned)\nRarity: %3%\nAction Cost: %4%\nColour: %5%\nColour Cost: %6%\nPower: %7%\nSpecies: %8%") 
		% accessName() %accessFrequency() % Card::rarityToString(accessRarity()) % accessActionCost() % Card::colourToString(accessColour())
		% accessDevelopmentCost() % accessPower() % speciesToString(species) << std::endl;
	printTypeModifiers();
	printSpecialText();
}

bool Friend::addFields(string inputToAdd) {

	Species prospectiveSpecies;

	switch (accessFieldsAdded()) {

		case (0) :
			// Require the name
			if (modifyName(inputToAdd)) {
				std::cout << "Rarity: ";
				break;
			}
			else {
				std::cout << "ERROR: Invalid name entered for Friend.\n";
				std::cout << "Name: ";
				return false;
			}
		case (1) :
			// Rarity
			if (modifyRarity(inputToAdd))  {
				std::cout << "Type Modifiers (e.g. Royalty etc.): ";
				break;
			}
			else {
				std::cout << "ERROR: Invalid Rarity entered for Friend.\n";
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
				// Prompt for next field:
				std::cout << "Species: ";
				break;
			}
			else {
				std::cout << "ERROR: Invalid colour passed to Friend.\n";
				Card::printAcceptableColours(false);
				std::cout << "Colour: ";
				return false;
			}
		case(4) :
			// Species
			prospectiveSpecies = stringToSpecies(inputToAdd);
			if (prospectiveSpecies != SPECIES_INVALID) {
				species = prospectiveSpecies;
				// Prompt for next field:
				std::cout << "Action Cost: ";
				break;
			}
			else {
				std::cout << "ERROR: Invalid Species passed to Friend.\n";
				printAcceptableSpecies();
				std::cout << "Species :";
				return false;
			}
		case (5) :
			// Action Cost
			if (modifyActionCost(inputToAdd)) {
				std::cout << "Colour Cost (0 if none): ";
				break;
			}
			else {
				std::cout << "ERROR: Invalid Action Cost entered for Friend.\nAction Cost: ";
				return false;
			}
		case (6) :
			// Colour Cost
			if (modifyDevelopmentCost(inputToAdd)) {
				std::cout << "Faceoff Power: ";
				break;
			}
			else {
				std::cout << "ERROR: Invalid Colour Cost entered for Friend.\nColour Cost (0 if none): ";
				return false;
			}
		case (7) :
			// Faceoff Power
			if (modifyPower(inputToAdd)) {
				std::cout << "Special Text: ";
				break;
			}
			else {
				std::cout << "ERROR: Invalid Faceoff Power entered for Friend.\nFaceoff Power: ";
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

bool Friend::isCardComplete() {
	return accessFieldsAdded() >= NUM_FIELDS;
}





