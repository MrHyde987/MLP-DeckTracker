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
	string name,
	Rarity rarity,
	vector<string> specialText) : PlayableCard(colour, power, name, rarity, specialText) {

	this->pointValue = pointValue;
	this->isVillain = isVillain;
}

TroubleMaker::~TroubleMaker() {}

void TroubleMaker::printStats() {
	std::cout << boost::format("%1% (%2% Owned)\nRarity: %3%\nVillain: %4%\nPower: %5%\nPts: %6%\nSpecial Text:")
		% accessName() % accessFrequency() % Card::rarityToString(accessRarity()) % (isVillain ? "True " : "False") % accessPower() % pointValue << std::endl;
	printSpecialText();
}

bool TroubleMaker::addFields(string inputToAdd) {

	switch (accessFieldsAdded()) {

		case(0) :
			// Require the name
			modifyName(inputToAdd);
			incrementAddedFields();
			modifyColour("None"); // All TMs have no colour
			std::cout << "Rarity: ";
			return true;
		case(1) :
			// Rarity
			if (modifyRarity(inputToAdd)) {
				std::cout << "Point Value: ";
				break;
			}
			else {
				std::cout << "ERROR: Invalid Rarity entered for Trouble Maker.\n";
				Card::printAcceptableRarities();
				std::cout << "Rarity: ";
				return false;
			}
		case(2) :
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
		case(3) :
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
		case(4) :
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