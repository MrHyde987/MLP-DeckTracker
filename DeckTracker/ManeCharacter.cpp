#include "ManeCharacter.h"
#include "StringUtility.h"
#include "boost/format.hpp"

ManeCharacter::ManeCharacter() {}

ManeCharacter::ManeCharacter(string name) : PlayableCard(name) {}

ManeCharacter::ManeCharacter(
	std::string flipCondition,
	int flippedPower,
	int startHomeLimit,
	int flippedHomeLimit,
	Colour colour,
	int power,
	string name,
	Rarity rarity,
	vector<string> specialText) : PlayableCard(colour, power, name, rarity, specialText) {

	this->flipCondition = flipCondition;
	this->flippedPower = flippedPower;
	this->startHomeLimit = startHomeLimit;
	this->flippedHomeLimit = flippedHomeLimit;
}

ManeCharacter::~ManeCharacter() {}

void ManeCharacter::printStats() {

	std::cout << boost::format("%1% (%2% Owned)\nRarity: %3%\nColour: %4%\nPower: %5%\nHome Limit: %6%\nFlipped Power: %7%\nFlipped Home Limit: %8%\nFlip Condition: %9%\nSpecial Text (after flipping):") 
		% accessName() % accessFrequency() % Card::rarityToString(accessRarity()) % Card::colourToString(accessColour()) % accessPower() % startHomeLimit
		% flippedPower % flippedHomeLimit % flipCondition << std::endl;
	printSpecialText();
}

bool ManeCharacter::addFields(string inputToAdd) {

	switch (accessFieldsAdded()) {
		case(0) :
			// Require the name
			modifyName(inputToAdd);
			incrementAddedFields();
			std::cout << "Rarity: ";
			return true;
		case(1) :
			// Rarity
			if (modifyRarity(inputToAdd)) {
				std::cout << "Colour: ";
				break;
			}
			else {
				std::cout << "ERROR: Invalid Rarity entered for Mane Character.\n";
				Card::printAcceptableRarities();
				std::cout << "Rarity: ";
				return false;
			}
		case(2) :
			// Require a Colour next
			if (modifyColour(inputToAdd)) {
				// Prompt for next field:
				std::cout << "Initial Power: ";
				break;
			}
			else {
				std::cout << "ERROR: Invalid colour passed to Mane Character.\n";
				Card::printAcceptableColours(false);
				std::cout << "Colour: ";
				return false;
			}
		case(3) :
			// Initial Power
			if (modifyPower(inputToAdd)) {
				std::cout << "Initial Home Limit: ";
				break;
			}
			else {
				std::cout << "ERROR: Invalid Initial Power entered for Mane Character.\nInitial Power: ";
				return false;
			}
		case(4) :
			// Initial Home Limit
			if (StringUtility::checkIsPositiveInt(inputToAdd)) {
				startHomeLimit = StringUtility::stringToInt(inputToAdd);
				std::cout << "Flipped Power: ";
				break;
			}
			else {
				std::cout << "ERROR: Invalid Initial Home Limit entered for Mane Character.\nInitial Home Limit: ";
				return false;
			}
		case(5) :
			// Flipped Power
			if (StringUtility::checkIsPositiveInt(inputToAdd)) {
				flippedPower = StringUtility::stringToInt(inputToAdd);
				std::cout << "Flipped Home Limit: ";
				break;
			}
			else {
				std::cout << "ERROR: Invalid Flipped Power entered for Mane Character.\nFlipped Power: ";
				return false;
			}
		case(6) :
			// Flipped Home Limit
			if (StringUtility::checkIsPositiveInt(inputToAdd)) {
				flippedHomeLimit = StringUtility::stringToInt(inputToAdd);
				std::cout << "Flip Condition: ";
				break;
			}
			else {
				std::cout << "ERROR: Invalid Flipped Home Limit entered for Mane Character.\nFlipped Home Limit: ";
				return false;
			}
		case(7) :
			// All manes have a flip condition
			flipCondition = inputToAdd;
			std::cout << "Special Text (in Boosted State): ";
			break;
		default :
			// Special Text is being added
			pushSpecialText(inputToAdd);
			return true;
	}

	incrementAddedFields();
	return true;
}

bool ManeCharacter::isCardComplete() {
	return accessFieldsAdded() >= NUM_FIELDS;
}