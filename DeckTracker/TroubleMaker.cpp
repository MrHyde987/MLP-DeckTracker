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
	vector<string> specialText) : PlayableCard(colour, power, name, specialText) {

	this->pointValue = pointValue;
	this->isVillain = isVillain;
}

TroubleMaker::~TroubleMaker() {}

void TroubleMaker::printStats() {
	std::cout << boost::format("%1%\nVillain: %2%\nPower: %3%\nPts: %4%\nSpecial Text:")
		% accessName() % (isVillain ? "True " : "False") % accessPower() % pointValue << std::endl;
	printSpecialText();
}

bool TroubleMaker::addFields(string inputToAdd) {

	switch (accessFieldsAdded()) {

		case(0) :
			// Require the name
			modifyName(inputToAdd);
			incrementAddedFields();
			modifyColour(COLOUR_NONE); // All TMs have no colour
			cout << "Point Value: ";
			return true;
		case(1) :
			// Point Value
			if (StringUtility::checkIsInt(inputToAdd)) {
				pointValue = StringUtility::stringToInt(inputToAdd);
				incrementAddedFields();
				cout << "Villain? ";
				return true;
			}
			else {
				cout << "ERROR: Invalid Point Value entered for Trouble Maker.\nPoint Value: ";
				return false;
			}
		case(2) :
			if (StringUtility::checkIsBool(inputToAdd)) {
				isVillain = StringUtility::stringToBool(inputToAdd);
				incrementAddedFields();
				cout << "Faceoff Power: ";
				return true;
			}
			else {
				cout << "ERROR: Invalid isVillain value entered for Trouble Maker.\nVillain? ";
				return false;
			}
		case(3) :
			// Faceoff Power
			if (StringUtility::checkIsInt(inputToAdd)) {
			modifyPower(StringUtility::stringToInt(inputToAdd));
			incrementAddedFields();
			cout << "Special Text: ";
			return true;
			}
			else {
				cout << "ERROR: Invalid Faceoff Power entered for Event.\nFaceoff Power: ";
				return false;
			}
		default :
			// Special Text is being added
			pushSpecialText(inputToAdd);
			return true;
	}

	// Execution should not fall through to here.
	cout << "ERROR: There is a bug in TroubleMaker::addFields" << endl;
	return false;
}

bool TroubleMaker::isCardComplete() {
	//cout << boost::format("Access Fields Added: %1% >= NUM FIELDS%2%") % accessFieldsAdded() % NUM_FIELDS << endl;
	return accessFieldsAdded() >= NUM_FIELDS;
}