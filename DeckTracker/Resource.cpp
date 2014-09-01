#include "Resource.h"
#include "StringUtility.h"
#include "boost/format.hpp"

Resource::Resource() {}
Resource::Resource(string name) : FRE(name) {}
Resource::Resource(
	Location location,
	int actionCost,
	int developmentCost,
	Colour colour,
	int power,
	vector<string> typeModifiers,
	string name,
	Rarity rarity,
	vector<string> specialText) : FRE(actionCost, developmentCost, colour, power, typeModifiers, name, rarity, specialText) {

	this->location = location;
}

Resource::~Resource() {}

void Resource::printStats() {

	std::cout << boost::format("%1% (%2% Owned)\nRarity: %3%\nAction Cost: %4%\nColour: %5%\nColour Cost: %6%\nPower: %7%\nLocation: %8%")
		% accessName() % accessFrequency() % Card::rarityToString(accessRarity()) % accessActionCost() % Card::colourToString(accessColour()) % accessDevelopmentCost() 
		% accessPower() % locationToString(location) << std::endl;
	printTypeModifiers();
	printSpecialText();
}

bool Resource::addFields(string inputToAdd) {
	
	Location prospectiveLocation;

	switch (accessFieldsAdded()) {

		case(0) :
			// Require the name
			if (modifyName(inputToAdd)) {
				std::cout << "Rarity: ";
				break;
			}
			else {
				std::cout << "ERROR: Invalid name entered for Resource.\n";
				std::cout << "Name: ";
				return false;
			}
		case(1) :
			if (modifyRarity(inputToAdd)) {
				std::cout << "Type Modifiers (e.g. Report etc.): ";
				break;
			}
			else {
				std::cout << "ERROR: Invalid Rarity entered for Resource.\n";
				Card::printAcceptableRarities();
				std::cout << "Rarity: ";
				return false;
			}
		case (2) :
			// Type Modifiers
			if (pushTypeModifier(inputToAdd))
				return true;
			else {
				std::cout << "Colour: ";
				break;
			}
		case(3) :
			// Require a Colour next
			if (modifyColour(inputToAdd)) {
				// Prompt for next field:
				std::cout << "Action Cost: ";
				break;
			}
			else {
				std::cout << "ERROR: Invalid colour entered for Resource.\n";
				Card::printAcceptableColours(true);
				std::cout << "Colour: ";
				return false;
			}
		case(4) :
			// Action Cost
			if (modifyActionCost(inputToAdd)) {
				std::cout << "Colour Cost (0 if none): ";
				break;
			}
			else {
				std::cout << "ERROR: Invalid Action Cost entered for Resource.\nAction Cost: ";
				return false;
			}
		case(5) :
			// Colour Cost
			if (modifyDevelopmentCost(inputToAdd)) {
				std::cout << "Faceoff Power: ";
				break;
			}
			else {
				std::cout << "ERROR: Invalid Colour Cost entered for Resource.\nColour Cost (0 if none): ";
				return false;
			}
		case(6) :
			// Faceoff Power
			if (modifyPower(inputToAdd)) {
				std::cout << "Location: ";
				break;
			}
			else {
				std::cout << "ERROR: Invalid Faceoff Power entered for Resource.\nFaceoff Power: ";
				return false;
			}
		case(7) :
			// Location
			prospectiveLocation = stringToLocation(inputToAdd);
			if (prospectiveLocation != LOCATION_INVALID) {
				location = prospectiveLocation;
				// Prompt for next field:
				std::cout << "Special Text: ";
				break;
			}
			else {
				std::cout << "ERROR: Invalid location entered for Resource.\n";
				printAcceptableLocations();
				std::cout << "Location: ";
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

bool Resource::isCardComplete() {
	return accessFieldsAdded() >= NUM_FIELDS;
}

Location Resource::stringToLocation(string toConvert) {

	Location newLocation;
	StringUtility::toLowerCase(toConvert);
	
	if (toConvert.compare("home") == 0)
		newLocation = LOCATION_HOME;
	else if (toConvert.compare("friend") == 0)
		newLocation = LOCATION_FRIEND;
	else if (toConvert.compare("opposing friend") == 0)
		newLocation = LOCATION_OPPOSING_FRIEND;
	else if (toConvert.compare("trouble maker") == 0)
		newLocation = LOCATION_TM;
	else if (toConvert.compare("problem") == 0)
		newLocation = LOCATION_PROBLEM;
	else if (toConvert.compare("mane character") == 0)
		newLocation = LOCATION_MC;
	else if (toConvert.compare("opposing mane character") == 0)
		newLocation = LOCATION_OPPOSING_MC;
	else
		newLocation = LOCATION_INVALID;

	return newLocation;
}

string Resource::locationToString(Location toConvert) {

	string toRet;
	switch (toConvert) {
		case (LOCATION_HOME) :
			toRet = "Played at Home";
			break;
		case (LOCATION_FRIEND) :
			toRet = "Played on a Friend";
			break;
		case (LOCATION_OPPOSING_FRIEND) :
			toRet = "Played on opponent's Friend";
			break;
		case (LOCATION_TM) :
			toRet = "Played on a Trouble Maker";
			break;
		case (LOCATION_PROBLEM) :
			toRet = "Played on a Problem";
			break;
		case (LOCATION_MC) :
			toRet = "Played on a Mane Character";
			break;
		case (LOCATION_OPPOSING_MC) :
			toRet = "Played on opponent's Mane Character";
			break;
		default :
			toRet = "ERROR: Attempted to convert invalid Resource location.";
	}

	return toRet;
}

void Resource::printAcceptableLocations() {
	std::cout << "Accepatble Locations: " << endl;
	std::cout << "Home\nFriend\nOpposing Friend\nTrouble Maker\nProblem\nMane Character\nOpposing Mane Character\n";
}