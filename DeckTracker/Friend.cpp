#include "Friend.h"
#include "SafeStringConversion.h"
#include "boost/format.hpp"

Friend::Friend() {}

Friend::Friend(
	Species species,
	int actionCost,
	int developmentCost,
	Colour colour,
	int power,
	string name,
	vector<string> specialText) : FRE(actionCost, developmentCost, colour, power, name, specialText) {

	this->species = species;
}

Friend::~Friend() {}

void Friend::printStats() {

	// TODO: Test this to see if it overflows the line. -> It does.
	std::cout << boost::format("%1%  Action Cost:%2% Colour:%3% Colour Cost:%4% Power:%5% Species:%6%") 
		% accessName() % accessActionCost() % accessColour()
		% accessDevelopmentCost() % accessPower() % species  << std::endl;
}

void Friend::formatPrompt() {
	cout << "For Friends, please use the following input format:" << endl;
	cout << "[Name],[Colour],[Species],[Action Cost],[Colour Cost],[Power],[Special Text]" << endl;
}

bool Friend::validateInput(vector<string> input) {

	bool validityFlag = false;

	if (input.size() < NUM_PROPERTIES) {
		cout << "ERROR: Invalid number of arguments passed to Friend." << endl;
		return false;
	}

	// Proper colour
	Colour prospectiveColour = Card::stringToColour(input[1]);

	if (prospectiveColour == COLOUR_INVALID) {
		cout << "ERROR: Invalid colour passed to Friend." << endl;
		return false;
	}

	// Species
	Species prospectiveSpecies = stringToSpecies(input[2]);

	if (prospectiveSpecies == SPECIES_INVALID) {
		cout << "ERROR: Invalid speices passed to Friend." << endl;
		return false;
	}

	// Action Cost
	validityFlag = SafeStringConversion::checkIsInt(input[4]);

	if (!validityFlag) {
		cout << "ERROR: Invalid action cost passed to Friend." << endl;
		return false;
	}

	// Colour Cost
	validityFlag = SafeStringConversion::checkIsInt(input[5]);

	if (!validityFlag) {
		cout << "ERROR: Invalid development cost passed to Friend." << endl;
		return false;
	}

	// Power
	validityFlag = SafeStringConversion::checkIsInt(input[6]);

	if (!validityFlag) {
		cout << "ERROR: Invalid power passed to Friend." << endl;
		return false;
	}

	return validityFlag;
}

void Friend::buildCard(vector<string> formattedInput) {

	modifyName(formattedInput[0]);
	modifyColour(Card::stringToColour(formattedInput[1]));
	species = stringToSpecies(formattedInput[2]);
	modifyActionCost(SafeStringConversion::stringToInt(formattedInput[3]));
	modifyDevelopmentCost(SafeStringConversion::stringToInt(formattedInput[4]));
	modifyPower(SafeStringConversion::stringToInt(formattedInput[5]));
	// All further strings treated as special text strings.
	vector<string> specialText;
	for (unsigned int i = NUM_PROPERTIES - 1; i < formattedInput.size(); ++i) {
		specialText.push_back(formattedInput[i]);
	}
	modifySpecialText(specialText);
}

Species Friend::stringToSpecies(string toSpecies) {

	Species newSpecies;
	SafeStringConversion::toLowerCase(toSpecies);

	if (toSpecies.compare("unicorn") == 0)
		newSpecies = SPECIES_UNICORN;
	else if (toSpecies.compare("pegasus") == 0)
		newSpecies = SPECIES_PEGASUS;
	else if (toSpecies.compare("earth pony") == 0)
		newSpecies = SPECIES_EP;
	else if (toSpecies.compare("alicorn") == 0)
		newSpecies = SPECIES_ALICORN;
	else if (toSpecies.compare("critter") == 0)
		newSpecies = SPECIES_CRITTER;
	else if (toSpecies.compare("dragon") == 0)
		newSpecies = SPECIES_DRAGON;
	else if (toSpecies.compare("zebra") == 0)
		newSpecies = SPECIES_ZEBRA;
	else if (toSpecies.compare("buffalo") == 0)
		newSpecies = SPECIES_BUFFALO;
	else
		newSpecies = SPECIES_INVALID;

	return newSpecies;
}