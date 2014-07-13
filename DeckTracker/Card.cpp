
#include "Card.h"

Card::Card() {}

// Notably, for cards that have no special text, the specialText
// field will hold the empty string ("")
// NOTE: Even though the dynamic "card-building" methods will not
// make use of these constructors, they will be important for reading
// cards from deck and manifest files later on.
Card::Card(string name, vector<string> specialText) {

	frequency = 1;
	this->name = name;
	this->specialText = specialText;
}

Card::~Card() {}

void Card::incrementFrequency() {
	frequency++;
}

void Card::decrementFrequency() {
	frequency--;
}

//////////////////////////////////////////////
//		Protected Methods
//////////////////////////////////////////////

string Card::accessName() {
	return name;
}

vector<string> Card::accessSpecialText() {
	return specialText;
}

void Card::modifyName(string newName) {
	name = newName;
}

void Card::modifySpecialText(vector<string> newText) {
	specialText = newText;
}

Colour Card::intToColour(int inputNum) {

	Colour colour;

	switch (inputNum) {
		case(0) :
			colour = COLOUR_NONE;
			break;
		case(1) :
			colour = COLOUR_PURPLE;
			break;
		case(2) :
			colour = COLOUR_WHITE;
			break;
		case(3) :
			colour = COLOUR_YELLOW;
			break;
		case(4) :
			colour = COLOUR_ORANGE;
			break;
		case(5) :
			colour = COLOUR_BLUE;
			break;
		case(6) :
			colour = COLOUR_PINK;
			break;
		default :
			colour = COLOUR_INVALID;
			break;
	}

	return colour;
}