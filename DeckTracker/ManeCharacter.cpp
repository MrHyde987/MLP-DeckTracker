#include "ManeCharacter.h"
#include "StringUtility.h"
#include "boost/format.hpp"

ManeCharacter::ManeCharacter() {}

ManeCharacter::ManeCharacter(string name) : PlayableCard(name) {}

ManeCharacter::ManeCharacter(
	std::string flipCondition,
	std::string boostedFlipCondition,
	Species species,
	int flippedPower,
	int startHomeLimit,
	int flippedHomeLimit,
	Colour colour,
	int power,
	vector<string> typeModifiers,
	string name,
	Rarity rarity,
	std::string startSpecialText,
	vector<string> specialText) : PlayableCard(colour, power, typeModifiers, name, rarity, specialText) {

	this->startFlipCondition = flipCondition;
	this->boostedFlipCondition = boostedFlipCondition;
	this->species = species;
	this->boostedPower = flippedPower;
	this->startHomeLimit = startHomeLimit;
	this->boostedHomeLimit = flippedHomeLimit;
	this->startSpecialText = startSpecialText;
}

ManeCharacter::~ManeCharacter() {}

void ManeCharacter::printStats() {

	std::cout << boost::format("%1% (%2% Owned)\nRarity: %3%\nColour: %4%\nSpecies: %5%\nPower: %6%\nHome Limit: %7% \
		\nBoosted Power: %8%\nBoosted Home Limit: %9%\nFlip Condition (Start side): %10%\nFlip Condition (Boosted Side): %11% \
		\nSpecial Text (Start Side): %12%") 
		% accessName() % accessFrequency() % Card::rarityToString(accessRarity()) 
		% Card::colourToString(accessColour())% PlayableCard::speciesToString(species) % accessPower() % startHomeLimit
		% boostedPower % boostedHomeLimit % startFlipCondition % boostedFlipCondition
		% startSpecialText << std::endl;
	printTypeModifiers();
	printSpecialText();
}

bool ManeCharacter::addFields(string inputToAdd) {

	Species prospectiveSpecies;

	switch (accessFieldsAdded()) {
		case(0) :
			// Require the name
			if (modifyName(inputToAdd)) {
				std::cout << "Rarity: ";
				break;
			}
			else {
				std::cout << "ERROR: Invalid Name entered for Mane Character.\n";
				std::cout << "Name: ";
				return false;
			}
		case(1) :
			// Rarity
			if (modifyRarity(inputToAdd)) {
				std::cout << "Type Modifiers (e.g. Royalty etc.): ";
				break;
			}
			else {
				std::cout << "ERROR: Invalid Rarity entered for Mane Character.\n";
				Card::printAcceptableRarities();
				std::cout << "Rarity: ";
				return false;
			}
		case(2) :
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
				std::cout << "Species: ";
				break;
			}
			else {
				std::cout << "ERROR: Invalid colour passed to Mane Character.\n";
				Card::printAcceptableColours(false);
				std::cout << "Colour: ";
				return false;
			}
		case(4) :
			// Species
			prospectiveSpecies = stringToSpecies(inputToAdd);
			if (prospectiveSpecies != SPECIES_INVALID) {
				species = prospectiveSpecies;
				// Prompt for next field:
				std::cout << "Initial Power: ";
				break;
			}
			else {
				std::cout << "ERROR: Invalid Species passed to Mane Character.\n";
				printAcceptableSpecies();
				std::cout << "Species :";
				return false;
			}
		case(5) :
			// Initial Power
			if (modifyPower(inputToAdd)) {
				std::cout << "Initial Home Limit: ";
				break;
			}
			else {
				std::cout << "ERROR: Invalid Initial Power entered for Mane Character.\nInitial Power: ";
				return false;
			}
		case(6) :
			// Initial Home Limit
			if (StringUtility::checkIsPositiveInt(inputToAdd)) {
				startHomeLimit = StringUtility::stringToInt(inputToAdd);
				std::cout << "Boosted Power: ";
				break;
			}
			else {
				std::cout << "ERROR: Invalid Initial Home Limit entered for Mane Character.\nInitial Home Limit: ";
				return false;
			}
		case(7) :
			// Flipped Power
			if (StringUtility::checkIsPositiveInt(inputToAdd)) {
				boostedPower = StringUtility::stringToInt(inputToAdd);
				std::cout << "Boosted Home Limit: ";
				break;
			}
			else {
				std::cout << "ERROR: Invalid Boosted Power entered for Mane Character.\nFlipped Power: ";
				return false;
			}
		case(8) :
			// Flipped Home Limit
			if (StringUtility::checkIsPositiveInt(inputToAdd)) {
				boostedHomeLimit = StringUtility::stringToInt(inputToAdd);
				std::cout << "Flip Condition (Start Side): ";
				break;
			}
			else {
				std::cout << "ERROR: Invalid Boosted Home Limit entered for Mane Character.\nFlipped Home Limit: ";
				return false;
			}
		case(9) :
			// All manes have a flip condition
			startFlipCondition = inputToAdd;
			std::cout << "Flip Condition (Boosted Side): ";
			break;
		case(10) :
			// Some manes can flip back from Boosted to Start
			if (inputToAdd.compare("") == 0)
				inputToAdd = "N/A";
			boostedFlipCondition = inputToAdd;
			std::cout << "Special Text (Start Side): ";
			break;
		case(11) :
			// Some manes have special abilities on their starting state
			if (inputToAdd.compare("") == 0)
				inputToAdd = "N/A";
			startSpecialText = inputToAdd;
			std::cout << "Special Text (Boosted Side): ";
			break;
		default :
			// Special Text is being added
			pushSpecialText(inputToAdd);
			return true;
	}

	incrementAddedFields();
	return true;
}

bool ManeCharacter::isCardComplete() {
	return accessFieldsAdded() >= NUM_FIELDS;
}