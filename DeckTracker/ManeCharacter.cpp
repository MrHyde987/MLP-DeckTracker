#include "ManeCharacter.h"
#include "boost/format.hpp"

ManeCharacter::ManeCharacter(
	std::string flipCondition,
	int flippedPower,
	Colour colour,
	int power,
	std::string name,
	std::string specialText) : PlayableCard(colour, power, name, specialText) {

	this->flipCondition = flipCondition;
	this->flippedPower = flippedPower;
}

ManeCharacter::~ManeCharacter() {}

void ManeCharacter::printStats() {

	std::cout << boost::format("%1%  P:%2% Colour:%3% OnFlip%4%") 
		% accessName() % accessPower() % accessColour() % flippedPower << std::endl;
}