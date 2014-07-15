#include "ManeCharacter.h"
#include "SafeStringConversion.h"
#include "boost/format.hpp"

ManeCharacter::ManeCharacter() {}

ManeCharacter::ManeCharacter(
	std::string flipCondition,
	int flippedPower,
	Colour colour,
	int power,
	string name,
	vector<string> specialText) : PlayableCard(colour, power, name, specialText) {

	this->flipCondition = flipCondition;
	this->flippedPower = flippedPower;
}

ManeCharacter::~ManeCharacter() {}

void ManeCharacter::printStats() {

	std::cout << boost::format("%1%  P:%2% Colour:%3% OnFlip%4%") 
		% accessName() % accessPower() % accessColour() % flippedPower << std::endl;
}

void ManeCharacter::formatPrompt() {
	cout << "For Mane Characters, please use the following input format:" << endl;
	cout << "[Name],[Colour],[Initial Power],[Flipped Power],[Flip Condition],[Special Text]" << endl;
}

bool ManeCharacter::validateInput(vector<string> input) {

	bool validityFlag = true;

	if (input.size() < NUM_PROPERTIES) {
		cout << "ERROR: Invalid number of arguments passed to Mane Character." << endl;
		return false;
	}

	// Proper colour
	Colour prospectiveColour = Card::stringToColour(input[1]);

	if (prospectiveColour == COLOUR_INVALID) {
		cout << "ERROR: Invalid colour passed to Mane Character." << endl;
		return false;
	}

	// Initial Power
	validityFlag = SafeStringConversion::checkIsInt(input[2]);

	if (!validityFlag) {
		cout << "ERROR: Invalid initial power passed to Mane Character." << endl;
		return false;
	}

	// Flipped Power
	validityFlag = SafeStringConversion::checkIsInt(input[3]);

	if (!validityFlag) {
		cout << "ERROR: Invalid flipped power passed to Mane Character." << endl;
		return false;
	}

	return validityFlag;
}

void ManeCharacter::buildCard(vector<string> formattedInput) {

	modifyName(formattedInput[0]);
	modifyColour(Card::stringToColour(formattedInput[1]));
	modifyPower(SafeStringConversion::stringToInt(formattedInput[2]));
	flippedPower = SafeStringConversion::stringToInt(formattedInput[3]);
	flipCondition = formattedInput[4];
	// All further strings treated as (flipped) special text / type modifiers.
	vector<string> specialText;
	for (unsigned int i = NUM_PROPERTIES - 1; i < formattedInput.size(); ++i) {
		specialText.push_back(formattedInput[i]);
	}
	modifySpecialText(specialText);
}