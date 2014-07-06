#include "TroubleMaker.h"
#include "SafeStringConversion.h"
#include "boost/format.hpp"

TroubleMaker::TroubleMaker() {}

TroubleMaker::TroubleMaker(
	int pointValue,
	bool isVillain,
	Colour colour,
	int power,
	std::string name,
	std::string specialText) : PlayableCard(colour, power, name, specialText) {

	this->pointValue = pointValue;
	this->isVillain = isVillain;
}

TroubleMaker::~TroubleMaker() {}

void TroubleMaker::printStats() {

	std::cout << boost::format("%1%  V:%2% P:%3% Pts:%4%") 
		% accessName() % (isVillain ? "True " : "False") % accessPower() % pointValue << std::endl;
}

void TroubleMaker::formatPrompt() {
	cout << "For Trouble Makers, please use the following input format:" << endl;
	cout << "[Name],[Point Value],[Villain?],[Confront Cost],[Special Text]" << endl;
}

bool TroubleMaker::validateInput(vector<string> input) {

	bool validityFlag = false;

	if (input.size() != NUM_PROPERTIES) {
		cout << "ERROR: Invalid number of arguments passed to Trouble Maker." << endl;
		return false;
	}

	// Point Value
	validityFlag = SafeStringConversion::checkIsInt(input[1]);

	if (!validityFlag) {
		cout << "ERROR: Invalid point value passed to Trouble Maker." << endl;
		return false;
	}

	// is Villain?
	validityFlag = SafeStringConversion::checkIsBool(input[2]);

	if (!validityFlag) {
		cout << "ERROR: Invalid isVillain value passed to Trouble Maker." << endl;
		return false;
	}

	// Confront Cost
	validityFlag = SafeStringConversion::checkIsInt(input[3]);

	if (!validityFlag) {
		cout << "ERROR: Invalid confront cost passed to Trouble Maker." << endl;
		return false;
	}

	return validityFlag;
}

void TroubleMaker::buildCard(vector<string> formattedInput) {

	modifyName(formattedInput[0]);
	pointValue = SafeStringConversion::stringToInt(formattedInput[1]);
	isVillain = SafeStringConversion::stringToBool(formattedInput[2]);
	modifyColour(COLOUR_NONE);
	modifyPower(SafeStringConversion::stringToInt(formattedInput[3]));
	modifySpecialText(formattedInput[4]);
}