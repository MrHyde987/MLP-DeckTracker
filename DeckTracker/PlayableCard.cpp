#include "PlayableCard.h"

PlayableCard::PlayableCard() {}

PlayableCard::PlayableCard(string name) : Card(name) {}

PlayableCard::PlayableCard(
	Colour colour,
	int power,
	vector<string> typeModifiers,
	string name,
	Rarity rarity,
	vector<string> specialText) : Card(name, rarity, specialText) {

	this->colour = colour;
	this->power = power;
	this->typeModifiers = typeModifiers;
}

PlayableCard::~PlayableCard() {}

Colour PlayableCard::accessColour() {
	return colour;
}

int PlayableCard::accessPower() {
	return power;
}

vector<string> PlayableCard::accessTypeModifiers() {
	return typeModifiers;
}

bool PlayableCard::modifyColour(string newColour) {
	Colour prospectiveColour = Card::stringToColour(newColour);
	if (prospectiveColour != COLOUR_INVALID) {
		colour = prospectiveColour;
		return true;
	}
	else
		return false;
}

bool PlayableCard::modifyPower(string newPower) {
	if (StringUtility::checkIsPositiveInt(newPower)) {
		power = StringUtility::stringToInt(newPower);
		return true;
	}
	else {
		return false;
	}
}

bool PlayableCard::modifyTypeModifiers(vector<string> newModifiers) {
	typeModifiers = newModifiers;
	return true; // TODO: This method probably isn't even necessary.
}

bool PlayableCard::pushTypeModifier(string newModifier) {
	
	bool toRet = true;
	if (newModifier.compare("") == 0)
		toRet = false;
	else
		typeModifiers.push_back(newModifier);
	return toRet;
}

void PlayableCard::printTypeModifiers() {
	
	std::cout << "Type Modifiers: ";
	
	if (typeModifiers.size() == 0)
		std::cout << "N/A" << endl;
	else {
		for (unsigned int i = 0; i < typeModifiers.size(); ++i) {
			std::cout << typeModifiers[i];
			if (i != typeModifiers.size() - 1)
				std::cout << ",";
		}
	}

	std::cout << endl;
}

Species PlayableCard::stringToSpecies(string toSpecies) {

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

string PlayableCard::speciesToString(Species toString) {

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
	default:
		toRet = "ERROR: Attempted to convert invalid Species.";
	}

	return toRet;
}

void PlayableCard::printAcceptableSpecies() {
	std::cout << "Acceptable Species: " << endl;
	std::cout << "Unicorn\nPegasus\nEarth pony\nAlicorn\nZebra\nDragon\nBuffalo\n";
}