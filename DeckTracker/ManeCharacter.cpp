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

	std::cout << boost::format("%1%\nRarity: %2%\nColour: %3%\nPower: %4%\nHome Limit: %5%\nFlipped Power: %6%\nFlipped Home Limit: %7%\nFlip Condition: %8%\nSpecial Text (after flipping):") 
		% accessName() % Card::rarityToString(accessRarity()) % Card::colourToString(accessColour()) % accessPower() % startHomeLimit
		% flippedPower % flippedHomeLimit % flipCondition << std::endl;
	printSpecialText();
}

bool ManeCharacter::addFields(string inputToAdd) {
	Colour prospectiveColour;
	Rarity prospectiveRarity;

	switch (accessFieldsAdded()) {
		case(0) :
			// Require the name
			modifyName(inputToAdd);
			incrementAddedFields();
			std::cout << "Rarity: ";
			return true;
		case(1) :
			// Rarity
			prospectiveRarity = Card::stringToRarity(inputToAdd);
			if (prospectiveRarity != RARITY_INVALID) {
				modifyRarity(prospectiveRarity);
				incrementAddedFields();
				std::cout << "Colour: ";
				return true;
			}
			else {
				std::cout << "ERROR: Invalid Rarity entered for Mane Character.\nRarity: ";
				return false;
			}
		case(2) :
			// Require a Colour next
			prospectiveColour = Card::stringToColour(inputToAdd);
			if (prospectiveColour != COLOUR_INVALID) {
				modifyColour(prospectiveColour);
				incrementAddedFields();
				// Prompt for next field:
				std::cout << "Initial Power: ";
				return true;
			}
			else {
				std::cout << "ERROR: Invalid colour passed to Mane Character.\nColour :";
				return false;
			}
		case(3) :
			// Initial Power
			if (StringUtility::checkIsPositiveInt(inputToAdd)) {
				modifyPower(StringUtility::stringToInt(inputToAdd));
				incrementAddedFields();
				std::cout << "Initial Home Limit: ";
				return true;
			}
			else {
				std::cout << "ERROR: Invalid Initial Power entered for Mane Character.\nInitial Power: ";
				return false;
			}
		case(4) :
			// Initial Home Limit
			if (StringUtility::checkIsPositiveInt(inputToAdd)) {
				startHomeLimit = StringUtility::stringToInt(inputToAdd);
				incrementAddedFields();
				std::cout << "Flipped Power: ";
				return true;
			}
			else {
				std::cout << "ERROR: Invalid Initial Home Limit entered for Mane Character.\nInitial Home Limit: ";
				return false;
			}
		case(5) :
			// Flipped Power
			if (StringUtility::checkIsPositiveInt(inputToAdd)) {
				flippedPower = StringUtility::stringToInt(inputToAdd);
				incrementAddedFields();
				std::cout << "Flipped Home Limit: ";
				return true;
			}
			else {
				std::cout << "ERROR: Invalid Flipped Power entered for Mane Character.\nFlipped Power: ";
				return false;
			}
		case(6) :
			// Flipped Home Limit
			if (StringUtility::checkIsPositiveInt(inputToAdd)) {
				flippedHomeLimit = StringUtility::stringToInt(inputToAdd);
				incrementAddedFields();
				std::cout << "Flip Condition: ";
				return true;
			}
			else {
				std::cout << "ERROR: Invalid Flipped Home Limit entered for Mane Character.\nFlipped Home Limit: ";
				return false;
			}
		case(7) :
			// All manes have a flip condition
			flipCondition = inputToAdd;
			incrementAddedFields();
			std::cout << "Special Text (in Boosted State): ";
			return true;
		default :
			// Special Text is being added
			pushSpecialText(inputToAdd);
			return true;
	}

	// Execution should not fall through to here.
	std::cout << "ERROR: There is a bug in ManeCharacter::addFields" << endl;
	return false;
}

bool ManeCharacter::isCardComplete() {
	return accessFieldsAdded() >= NUM_FIELDS;
}