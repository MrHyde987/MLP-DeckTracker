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
	string name,
	Rarity rarity,
	vector<string> specialText) : FRE(actionCost, developmentCost, colour, power, name, rarity, specialText) {

	this->location = location;
}

Resource::~Resource() {}

void Resource::printStats() {

	std::cout << boost::format("%1%\nRarity: %2%Action Cost: %3%\nColour: %4%\nColour Cost: %5%\nPower: %6%\nLocation: %7%\nSpecial Text:")
		% accessName() % Card::rarityToString(accessRarity()) % accessActionCost() % Card::colourToString(accessColour()) % accessDevelopmentCost() 
		% accessPower() % locationToString(location) << std::endl;
	printSpecialText();
}

bool Resource::addFields(string inputToAdd) {
	
	Colour prospectiveColour;
	Rarity prospectiveRarity;
	Location prospectiveLocation;

	switch (accessFieldsAdded()) {

		case(0) :
			// Require the name
			modifyName(inputToAdd);
			incrementAddedFields();
			std::cout  << "Rarity: ";
			return true;
		case(1) :
			prospectiveRarity = Card::stringToRarity(inputToAdd);
			if (prospectiveRarity != RARITY_INVALID) {
				modifyRarity(prospectiveRarity);
				incrementAddedFields();
				std::cout  << "Colour: ";
				return true;
			}
			else {
				std::cout  << "ERROR: Invalid Rarity entered for Resource.\nRarity: ";
				return false;
			}
		case(2) :
			// Require a Colour next
			prospectiveColour = Card::stringToColour(inputToAdd);
			if (prospectiveColour != COLOUR_INVALID) {
				modifyColour(prospectiveColour);
				incrementAddedFields();
				// Prompt for next field:
				std::cout  << "Action Cost: ";
				return true;
			}
			else {
				std::cout  << "ERROR: Invalid colour entered for Resource.\nColour :";
				return false;
			}
		case(3) :
			// Action Cost
			if (StringUtility::checkIsPositiveInt(inputToAdd)) {
				modifyActionCost(StringUtility::stringToInt(inputToAdd));
				incrementAddedFields();
				std::cout  << "Colour Cost (0 if none): ";
				return true;
			}
			else {
				std::cout  << "ERROR: Invalid Action Cost entered for Resource.\nAction Cost: ";
				return false;
			}
		case(4) :
			// Colour Cost
			if (StringUtility::checkIsPositiveInt(inputToAdd)) {
				modifyDevelopmentCost(StringUtility::stringToInt(inputToAdd));
				incrementAddedFields();
				std::cout  << "Faceoff Power: ";
				return true;
			}
			else {
				std::cout  << "ERROR: Invalid Colour Cost entered for Resource.\nColour Cost (0 if none): ";
				return false;
			}
		case(5) :
			// Faceoff Power
			if (StringUtility::checkIsPositiveInt(inputToAdd)) {
				modifyPower(StringUtility::stringToInt(inputToAdd));
				incrementAddedFields();
				std::cout  << "Location: ";
				return true;
			}
			else {
				std::cout  << "ERROR: Invalid Faceoff Power entered for Resource.\nFaceoff Power: ";
				return false;
			}
		case(6) :
			// Location
			prospectiveLocation = stringToLocation(inputToAdd);
			if (prospectiveLocation != LOCATION_INVALID) {
				location = prospectiveLocation;
				incrementAddedFields();
				// Prompt for next field:
				std::cout  << "Special Text: ";
				return true;
			}
			else {
				std::cout  << "ERROR: Invalid location entered for Resource.\nLocation :";
				return false;
			}
		default :
			// Special Text is being added
			pushSpecialText(inputToAdd);
			return true;
	}

	// Execution should not fall through to here
	std::cout  << "ERROR: There is a bug in Resource::addFields" << endl;
	return false;
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