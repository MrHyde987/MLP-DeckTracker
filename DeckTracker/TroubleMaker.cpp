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
	std::cout << boost::format("%1%\nRarity: %2%\nVillain: %3%\nPower: %4%\nPts: %5%\nSpecial Text:")
		% accessName() % Card::rarityToString(accessRarity()) % (isVillain ? "True " : "False") % accessPower() % pointValue << std::endl;
	printSpecialText();
}

bool TroubleMaker::addFields(string inputToAdd) {

	Rarity prospectiveRarity;

	switch (accessFieldsAdded()) {

		case(0) :
			// Require the name
			modifyName(inputToAdd);
			incrementAddedFields();
			modifyColour(COLOUR_NONE); // All TMs have no colour
			std::cout  << "Rarity: ";
			return true;
		case(1) :
			// Rarity
			prospectiveRarity = Card::stringToRarity(inputToAdd);
			if (prospectiveRarity != RARITY_INVALID) {
				modifyRarity(prospectiveRarity);
				incrementAddedFields();
				std::cout  << "Point Value: ";
				return true;
			}
			else {
				std::cout  << "ERROR: Invalid Rarity entered for Trouble Maker.\nRarity: ";
				return false;
			}
		case(2) :
			// Point Value
			if (StringUtility::checkIsPositiveInt(inputToAdd)) {
				pointValue = StringUtility::stringToInt(inputToAdd);
				incrementAddedFields();
				std::cout  << "Villain? ";
				return true;
			}
			else {
				std::cout  << "ERROR: Invalid Point Value entered for Trouble Maker.\nPoint Value: ";
				return false;
			}
		case(3) :
			if (StringUtility::checkIsBool(inputToAdd)) {
				isVillain = StringUtility::stringToBool(inputToAdd);
				incrementAddedFields();
				std::cout  << "Faceoff Power: ";
				return true;
			}
			else {
				std::cout  << "ERROR: Invalid isVillain value entered for Trouble Maker.\nVillain? ";
				return false;
			}
		case(4) :
			// Faceoff Power
			if (StringUtility::checkIsPositiveInt(inputToAdd)) {
			modifyPower(StringUtility::stringToInt(inputToAdd));
			incrementAddedFields();
			std::cout  << "Special Text: ";
			return true;
			}
			else {
				std::cout  << "ERROR: Invalid Faceoff Power entered for Event.\nFaceoff Power: ";
				return false;
			}
		default :
			// Special Text is being added
			pushSpecialText(inputToAdd);
			return true;
	}

	// Execution should not fall through to here.
	std::cout  << "ERROR: There is a bug in TroubleMaker::addFields" << endl;
	return false;
}

bool TroubleMaker::isCardComplete() {
	return accessFieldsAdded() >= NUM_FIELDS;
}