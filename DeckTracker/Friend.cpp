#include "Friend.h"
#include "SafeStringConversion.h"
#include "boost/format.hpp"

Friend::Friend() {}

Friend::Friend(
	Species species,
	std::string typeModifiers,
	int actionCost,
	int developmentCost,
	Colour colour,
	int power,
	std::string name,
	std::string specialText) : FRE(actionCost, developmentCost, colour, power, name, specialText) {

	this->species = species;
	this->typeModifiers = typeModifiers;
}

Friend::~Friend() {}

void Friend::printStats() {

	// TODO: Test this to see if it overflows the line. -> It does.
	std::cout << boost::format("%1%  Action Cost:%2% Colour:%3% Colour Cost:%4% Power:%5% Species:%6% Types:%7%") 
		% accessName() % accessActionCost() % accessColour()
		% accessDevelopmentCost() % accessPower() % species % typeModifiers << std::endl;
}

void Friend::formatPrompt() {
	cout << "For Friends, please use the following input format:" << endl;
	cout << "[Name],[Colour],[Species],[Type Modifiers, ,...],[Action Cost],[Colour Cost],[Power],[Special Text]" << endl;
}

bool Friend::validateInput(vector<string> input) {

	bool validityFlag = false;

	if (input.size() != NUM_PROPERTIES) {
		cout << "ERROR: Invalid number of arguments passed to Friend." << endl;
		return false;
	}

	// Proper colour
	Colour prospectiveColour = COLOUR_INVALID;
	validityFlag = SafeStringConversion::checkIsInt(input[1]);

	if (validityFlag)
		prospectiveColour = Card::intToColour(SafeStringConversion::stringToInt(input[1]));
	if (prospectiveColour == COLOUR_INVALID) {
		cout << "ERROR: Invalid colour passed to Friend." << endl;
		return false;
	}

	// Species
	Species prospectiveSpecies = SPECIES_INVALID;
	validityFlag = SafeStringConversion::checkIsInt(input[2]);

	if (validityFlag)
		prospectiveSpecies = intToSpecies(SafeStringConversion::stringToInt(input[2]));
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
	modifyColour(Card::intToColour(SafeStringConversion::stringToInt(formattedInput[1])));
	species = intToSpecies(SafeStringConversion::stringToInt(formattedInput[2]));
	typeModifiers = formattedInput[3];
	modifyActionCost(SafeStringConversion::stringToInt(formattedInput[4]));
	modifyDevelopmentCost(SafeStringConversion::stringToInt(formattedInput[5]));
	modifyPower(SafeStringConversion::stringToInt(formattedInput[6]));
	modifySpecialText(formattedInput[7]);
}

Species Friend::intToSpecies(int toSpecies) {

	Species newSpecies;

	switch (toSpecies) {
		case(0) :
			newSpecies = SPECIES_UNICORN;
			break;
		case(1) :
			newSpecies = SPECIES_PEGASUS;
			break;
		case(2) :
			newSpecies = SPECIES_EP;
			break;
		case(3) :
			newSpecies = SPECIES_ALICORN;
			break;
		case(4) :
			newSpecies = SPECIES_ZEBRA;
			break;
		case(5) :
			newSpecies = SPECIES_CRITTER;
			break;
		case(6) :
			newSpecies = SPECIES_DRAGON;
			break;
		case(7) :
			newSpecies = SPECIES_BUFFALO;
			break;
		default:
			newSpecies = SPECIES_INVALID;
			break;
	}

	return newSpecies;
}