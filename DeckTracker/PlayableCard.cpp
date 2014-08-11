#include "PlayableCard.h"

PlayableCard::PlayableCard() {}

PlayableCard::PlayableCard(string name) : Card(name) {}

PlayableCard::PlayableCard(
	Colour colour,
	int power,
	string name,
	vector<string> specialText) : Card(name, specialText) {

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

void PlayableCard::modifyColour(Colour newColour) {
	colour = newColour;
}

void PlayableCard::modifyPower(int newPower) {
	power = newPower;
}