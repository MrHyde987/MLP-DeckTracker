#include "FRE.h"

FRE::FRE(
	int actionCost,
	int developmentCost,
	Colour colour,
	int power,
	std::string name,
	std::string specialText) : PlayableCard(colour, power, name, specialText) {

	this->actionCost = actionCost;
	this->developmentCost = developmentCost;
}

FRE::~FRE() {}

int FRE::accessActionCost() {
	return actionCost;
}

int FRE::accessDevelopmentCost() {
	return developmentCost;
}