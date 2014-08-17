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

	std::cout << boost::format("%1% (%2% Owned)\nRarity: %3%\nAction Cost: %4%\nColour: %5%\nColour Cost: %6%\nPower: %7%\nSpecies: %8%\nSpecial Text:") 
		% accessName() %accessFrequency() % Card::rarityToString(accessRarity()) % accessActionCost() % Card::colourToString(accessColour())
		% accessDevelopmentCost() % accessPower() % speciesToString(species) << std::endl;

	printSpecialText();
}

bool Friend::addFields(string inputToAdd) {

	Species prospectiveSpecies;

	switch (accessFieldsAdded()) {

		case (0) :
			// Require the name
			modifyName(inputToAdd);
			std::cout << "Rarity: ";
			break;
		case (1) :
			// Rarity
			if (modifyRarity(inputToAdd))  {
				std::cout << "Colour: ";
				break;
			}
			else {
				std::cout << "ERROR: Invalid Rarity entered for Friend.\n";
				printAcceptableRarities();
				std::cout << "Rarity: ";
				return false;
			}
		case (2) :
			// Require a Colour next
			if (modifyColour(inputToAdd)) {
				// Prompt for next field:
				std::cout << "Species: ";
				break;
			}
			else {
				std::cout << "ERROR: Invalid colour passed to Friend.\n";
				Card::printAcceptableColours(false);
				std::cout << "Colour: ";
				return false;
			}
		case(3) :
			// Species
			prospectiveSpecies = stringToSpecies(inputToAdd);
			if (prospectiveSpecies != SPECIES_INVALID) {
				species = prospectiveSpecies;
				// Prompt for next field:
				std::cout << "Action Cost: ";
				break;
			}
			else {
				std::cout << "ERROR: Invalid Species passed to Friend.\n";
				printAcceptableSpecies();
				std::cout << "Species :";
				return false;
			}
		case (4) :
			// Action Cost
			if (modifyActionCost(inputToAdd)) {
				std::cout << "Colour Cost (0 if none): ";
				break;
			}
			else {
				std::cout << "ERROR: Invalid Action Cost entered for Friend.\nAction Cost: ";
				return false;
			}
		case (5) :
			// Colour Cost
			if (modifyDevelopmentCost(inputToAdd)) {
				std::cout << "Faceoff Power: ";
				break;
			}
			else {
				std::cout << "ERROR: Invalid Colour Cost entered for Friend.\nColour Cost (0 if none): ";
				return false;
			}
		case (6) :
			// Faceoff Power
			if (modifyPower(inputToAdd)) {
				std::cout << "Special Text: ";
				break;
			}
			else {
				std::cout << "ERROR: Invalid Faceoff Power entered for Friend.\nFaceoff Power: ";
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

void Friend::printAcceptableSpecies() {
	std::cout << "Acceptable Species: " << endl;
	std::cout << "Unicorn\nPegasus\nEarth pony\nAlicorn\nZebra\nDragon\nBuffalo\n";
}