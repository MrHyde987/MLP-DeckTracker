
#include "Card.h"

// Notably, for cards that have no special text, the specialText
// field will hold the empty string ("")
Card::Card(std::string name, std::string specialText) {

	this->name = name;
	this->specialText = specialText;
}

Card::~Card() {}

std::string Card::accessName() {
	return name;
}

std::string Card::accessSpecialText() {
	return specialText;
}