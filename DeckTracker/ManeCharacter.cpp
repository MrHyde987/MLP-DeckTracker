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
	vector<string> specialText) : PlayableCard(colour, power, name, specialText) {

	this->flipCondition = flipCondition;
	this->flippedPower = flippedPower;
	this->startHomeLimit = startHomeLimit;
	this->flippedHomeLimit = flippedHomeLimit;
}

ManeCharacter::~ManeCharacter() {}

void ManeCharacter::printStats() {

	std::cout << boost::format("%1%\nColour: %2%\nPower: %3%\nHome Limit: %4%\nFlipped Power: %5%\nFlipped Home Limit: %6%\nFlip Condition: %7%\nSpecial Text (after flipping):") 
		% accessName() % Card::colourToString(accessColour()) % accessPower() % startHomeLimit
		% flippedPower % flippedHomeLimit % flipCondition << std::endl;
	printSpecialText();
}

bool ManeCharacter::addFields(string inputToAdd) {
	Colour prospectiveColour;

	switch (accessFieldsAdded()) {
		case(0) :
			// Require the name
			modifyName(inputToAdd);
			incrementAddedFields();
			cout << "Colour: ";
			return true;
		case(1) :
			// Require a Colour next
			prospectiveColour = Card::stringToColour(inputToAdd);
			if (prospectiveColour != COLOUR_INVALID) {
				modifyColour(prospectiveColour);
				incrementAddedFields();
				// Prompt for next field:
				cout << "Initial Power: ";
				return true;
			}
			else {
				cout << "ERROR: Invalid colour passed to Mane Character.\nColour :";
				return false;
			}
		case(2) :
			// Initial Power
			if (StringUtility::checkIsPositiveInt(inputToAdd)) {
				modifyPower(StringUtility::stringToInt(inputToAdd));
				incrementAddedFields();
				cout << "Initial Home Limit: ";
				return true;
			}
			else {
				cout << "ERROR: Invalid Initial Power entered for Mane Character.\nInitial Power: ";
				return false;
			}
		case(3) :
			// Initial Home Limit
			if (StringUtility::checkIsPositiveInt(inputToAdd)) {
				startHomeLimit = StringUtility::stringToInt(inputToAdd);
				incrementAddedFields();
				cout << "Flipped Power: ";
				return true;
			}
			else {
				cout << "ERROR: Invalid Initial Home Limit entered for Mane Character.\nInitial Home Limit: ";
				return false;
			}
		case(4) :
			// Flipped Power
			if (StringUtility::checkIsPositiveInt(inputToAdd)) {
				flippedPower = StringUtility::stringToInt(inputToAdd);
				incrementAddedFields();
				cout << "Flipped Home Limit: ";
				return true;
			}
			else {
				cout << "ERROR: Invalid Flipped Power entered for Mane Character.\nFlipped Power: ";
				return false;
			}
		case(5) :
			// Flipped Home Limit
			if (StringUtility::checkIsPositiveInt(inputToAdd)) {
				flippedHomeLimit = StringUtility::stringToInt(inputToAdd);
				incrementAddedFields();
				cout << "Flip Condition: ";
				return true;
			}
			else {
				cout << "ERROR: Invalid Flipped Home Limit entered for Mane Character.\nFlipped Home Limit: ";
				return false;
			}
		case(6) :
			// All manes have a flip condition
			flipCondition = inputToAdd;
			incrementAddedFields();
			cout << "Special Text (in Boosted State): ";
			return true;
		default :
			// Special Text is being added
			pushSpecialText(inputToAdd);
			return true;
	}

	// Execution should not fall through to here.
	cout << "ERROR: There is a bug in ManeCharacter::addFields" << endl;
	return false;
}

bool ManeCharacter::isCardComplete() {
	return accessFieldsAdded() >= NUM_FIELDS;
}