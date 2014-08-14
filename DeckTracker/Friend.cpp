#include "Friend.h"
#include "StringUtility.h"
#include "boost/format.hpp"

Friend::Friend() {}

Friend::Friend(string name) : FRE(name) {}

Friend::Friend(
	Species species,
	int actionCost,
	int developmentCost,
	Colour colour,
	int power,
	string name,
	Rarity rarity,
	vector<string> specialText) : FRE(actionCost, developmentCost, colour, power, name, rarity, specialText) {

	this->species = species;
}

Friend::~Friend() {}

void Friend::printStats() {

	std::cout << boost::format("%1%\nRarity: %2%\nAction Cost: %3%\nColour: %4%\nColour Cost: %5%\nPower: %6%\nSpecies: %7%\nSpecial Text:") 
		% accessName() % Card::rarityToString(accessRarity()) % accessActionCost() % Card::colourToString(accessColour())
		% accessDevelopmentCost() % accessPower() % speciesToString(species) << std::endl;

	printSpecialText();
}

bool Friend::addFields(string inputToAdd) {
	
	Colour prospectiveColour;
	Rarity prospectiveRarity;
	Species prospectiveSpecies;

	switch (accessFieldsAdded()) {

		case (0) :
			// Require the name
			modifyName(inputToAdd);
			incrementAddedFields();
			std::cout  << "Rarity: ";
			return true;
		case (1) :
			// Rarity
			prospectiveRarity = Card::stringToRarity(inputToAdd);
			if (prospectiveRarity != RARITY_INVALID)  {
				modifyRarity(prospectiveRarity);
				incrementAddedFields();
				std::cout  << "Colour: ";
				return true;
			}
			else {
				std::cout  << "ERROR: Invalid Rarity entered for Friend.\nRarity: ";
				return false;
			}
		case (2) :
			// Require a Colour next
			prospectiveColour = Card::stringToColour(inputToAdd);
			if (prospectiveColour != COLOUR_INVALID) {
				modifyColour(prospectiveColour);
				incrementAddedFields();
				// Prompt for next field:
				std::cout  << "Species: ";
				return true;
			}
			else {
				std::cout  << "ERROR: Invalid colour passed to Friend.\nColour :";
				return false;
			}
		case(3) :
			// Species
			prospectiveSpecies = stringToSpecies(inputToAdd);
			if (prospectiveSpecies != SPECIES_INVALID) {
				species = prospectiveSpecies;
				incrementAddedFields();
				// Prompt for next field:
				std::cout  << "Action Cost: ";
				return true;
			}
			else {
				std::cout  << "ERROR: Invalid Species passed to Friend.\nSpecies :";
				return false;
			}
		case (4) :
			// Action Cost
			if (StringUtility::checkIsPositiveInt(inputToAdd)) {
			modifyActionCost(StringUtility::stringToInt(inputToAdd));
			incrementAddedFields();
			std::cout  << "Colour Cost (0 if none): ";
			return true;
			}
			else {
				std::cout  << "ERROR: Invalid Action Cost entered for Friend.\nAction Cost: ";
				return false;
			}
		case (5) :
			// Colour Cost
			if (StringUtility::checkIsPositiveInt(inputToAdd)) {
			modifyDevelopmentCost(StringUtility::stringToInt(inputToAdd));
			incrementAddedFields();
			std::cout  << "Faceoff Power: ";
			return true;
			}
			else {
				std::cout  << "ERROR: Invalid Colour Cost entered for Friend.\nColour Cost (0 if none): ";
				return false;
			}
		case (6) :
			// Faceoff Power
			if (StringUtility::checkIsPositiveInt(inputToAdd)) {
			modifyPower(StringUtility::stringToInt(inputToAdd));
			incrementAddedFields();
			std::cout  << "Special Text: ";
			return true;
			}
			else {
				std::cout  << "ERROR: Invalid Faceoff Power entered for Friend.\nFaceoff Power: ";
				return false;
			}
		default :
			// Special Text is being added
			pushSpecialText(inputToAdd);
			return true;
	}

	// Execution should not fall through to here.
	std::cout  << "ERROR: There is a bug in Friend::addFields" << endl;
	return false;
}

bool Friend::isCardComplete() {
	return accessFieldsAdded() >= NUM_FIELDS;
}

Species Friend::stringToSpecies(string toSpecies) {

	Species newSpecies;
	StringUtility::toLowerCase(toSpecies);

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

string Friend::speciesToString(Species toString) {

	string toRet;
	switch (toString) {

		case (SPECIES_UNICORN) :
			toRet = "Unicorn";
			break;
		case (SPECIES_PEGASUS) :
			toRet = "Pegasus";
			break;
		case (SPECIES_EP) :
			toRet = "Earth Pony";
			break;
		case (SPECIES_ALICORN) :
			toRet = "Alicorn";
			break;
		case (SPECIES_ZEBRA) :
			toRet = "Zebra";
			break;
		case (SPECIES_CRITTER) :
			toRet = "Critter";
			break;
		case (SPECIES_DRAGON) :
			toRet = "Dragon";
			break;
		case (SPECIES_BUFFALO) :
			toRet = "Buffalo";
			break;
		default :
			toRet = "ERROR: Attempted to convert invalid Species.";
	}

	return toRet;
}