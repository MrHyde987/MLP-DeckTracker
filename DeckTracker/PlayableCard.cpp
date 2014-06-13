#include "PlayableCard.h"

PlayableCard::PlayableCard(
	Colour colour,
	int power,
	std::string name,
	std::string specialText) : Card(name, specialText) {

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