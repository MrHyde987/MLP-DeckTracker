#include "FRE.h"

FRE::FRE() {}

FRE::FRE(string name) : PlayableCard(name) {}

FRE::FRE(
	int actionCost,
	int developmentCost,
	Colour colour,
	int power,
	string name,
	vector<string> specialText) : PlayableCard(colour, power, name, specialText) {

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

void FRE::modifyActionCost(int newAC) {
	actionCost = newAC;
}

void FRE::modifyDevelopmentCost(int newDC) {
	developmentCost = newDC;
}