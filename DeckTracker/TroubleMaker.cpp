#include "TroubleMaker.h"
#include "StringUtility.h"
#include "boost/format.hpp"

TroubleMaker::TroubleMaker() {}
TroubleMaker::TroubleMaker(string name) : PlayableCard(name) {}
TroubleMaker::TroubleMaker(
	int pointValue,
	bool isVillain,
	Colour colour,
	int power,
	vector<string> typeModifiers,
	string name,
	Rarity rarity,
	vector<string> specialText) : PlayableCard(colour, power, typeModifiers, name, rarity, specialText) {

	this->pointValue = pointValue;
	this->isVillain = isVillain;
}

TroubleMaker::~TroubleMaker() {}

void TroubleMaker::printStats() {
	std::cout << boost::format("%1% (%2% Owned)\nRarity: %3%\nVillain: %4%\nPower: %5%\nPts: %6%")
		% accessName() % accessFrequency() % Card::rarityToString(accessRarity()) % (isVillain ? "True " : "False") % accessPower() % pointValue << std::endl;
	printTypeModifiers();
	printSpecialText();
}

bool TroubleMaker::addFields(string inputToAdd) {

	switch (accessFieldsAdded()) {

		case(0) :
			// Require the name
			if (modifyName(inputToAdd)) {
				modifyColour("None"); // All TMs have no colour
				std::cout << "Rarity: ";
				break;
			}
			else {
				std::cout << "ERROR: Invalid Name entered for Trouble Maker.\n";
				std::cout << "Name: ";
				return false;
			}
		case(1) :
			// Rarity
			if (modifyRarity(inputToAdd)) {
				std::cout << "Type Modifiers (e.g. Royalty etc.): ";
				break;
			}
			else {
				std::cout << "ERROR: Invalid Rarity entered for Trouble Maker.\n";
				Card::printAcceptableRarities();
				std::cout << "Rarity: ";
				return false;
			}
		case (2) :
			// Type Modifiers
			if (pushTypeModifier(inputToAdd))
				return true;
			else {
				std::cout << "Point Value: ";
				break;
			}
		case(3) :
			// Point Value
			if (StringUtility::checkIsPositiveInt(inputToAdd)) {
				pointValue = StringUtility::stringToInt(inputToAdd);
				std::cout << "Villain? ";
				break;
			}
			else {
				std::cout << "ERROR: Invalid Point Value entered for Trouble Maker.\nPoint Value: ";
				return false;
			}
		case(4) :
			// Is Villain?
			if (StringUtility::checkIsBool(inputToAdd)) {
				isVillain = StringUtility::stringToBool(inputToAdd);
				std::cout << "Faceoff Power: ";
				break;
			}
			else {
				std::cout << "ERROR: Invalid isVillain value entered for Trouble Maker.\nVillain? ";
				return false;
			}
		case(5) :
			// Faceoff Power
			if (modifyPower(inputToAdd)) {
				std::cout << "Special Text: ";
				break;
			}
			else {
				std::cout << "ERROR: Invalid Faceoff Power entered for Event.\nFaceoff Power: ";
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

bool TroubleMaker::isCardComplete() {
	return accessFieldsAdded() >= NUM_FIELDS;
}