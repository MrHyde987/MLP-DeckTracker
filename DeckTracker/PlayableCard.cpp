#include "PlayableCard.h"

PlayableCard::PlayableCard() {}

PlayableCard::PlayableCard(string name) : Card(name) {}

PlayableCard::PlayableCard(
	Colour colour,
	int power,
	string name,
	Rarity rarity,
	vector<string> specialText) : Card(name, rarity, specialText) {

	this->colour = colour;
	this->power = power;
}

PlayableCard::~PlayableCard() {}

Colour PlayableCard::accessColour() {
	return colour;
}

int PlayableCard::accessPower() {
	return power;
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