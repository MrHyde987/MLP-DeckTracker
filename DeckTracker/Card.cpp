
#include "Card.h"
#include "StringUtility.h"

Card::Card() {

	filledFields = 0;
	specialText = vector<string>();
}

// This version of the constructor is the one that will be used more
// frequently for dynamic card-building, since we will start with 
// just the card's name.
Card::Card(string name) : name(name) {

	filledFields = 1;
	specialText = vector<string>();
}

// NOTE: Even though the dynamic "card-building" methods will not
// make use of these constructors, they will be important for reading
// cards from deck and manifest files later on.
Card::Card(string name, vector<string> specialText) {

	// How to deal with frequency when reading in files is a design
	// decision that has yet to be made.
	//frequency = 1;
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
//		Operator Overloads
//////////////////////////////////////////////
bool Card::operator==(Card* toCompare) {

	return (name.compare(toCompare->name) == 0);
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

void Card::printSpecialText() {
	for (unsigned int i = 0; i < specialText.size(); ++i) {
		std::cout << specialText[i] << endl;
	}
}

void Card::pushSpecialText(string textToAdd) {
	specialText.push_back(textToAdd);
}

void Card::incrementAddedFields() {
	filledFields++;
}

const int Card::accessFieldsAdded() const {
	return filledFields;
}

Colour Card::stringToColour(string toConvert) {

	Colour colour;
	StringUtility::toLowerCase(toConvert);

	if (toConvert.compare("none") == 0)
		colour = COLOUR_NONE;
	else if (toConvert.compare("purple") == 0)
		colour = COLOUR_PURPLE;
	else if (toConvert.compare("white") == 0)
		colour = COLOUR_WHITE;
	else if (toConvert.compare("yellow") == 0)
		colour = COLOUR_YELLOW;
	else if (toConvert.compare("orange") == 0)
		colour = COLOUR_ORANGE;
	else if (toConvert.compare("pink") == 0)
		colour = COLOUR_PINK;
	else if (toConvert.compare("blue") == 0)
		colour = COLOUR_BLUE;
	else
		colour = COLOUR_INVALID;

	return colour;
}

string Card::colourToString(Colour toConvert) {

	string toRet;
	switch (toConvert) {
		case (COLOUR_NONE) :
			toRet = "None";
			break;
		case (COLOUR_PURPLE) :
			toRet = "Purple";
			break;
		case (COLOUR_WHITE) :
			toRet = "White";
			break;
		case (COLOUR_YELLOW) :
			toRet = "Yellow";
			break;
		case (COLOUR_ORANGE) :
			toRet = "Orange";
			break;
		case (COLOUR_BLUE) :
			toRet = "Blue";
			break;
		case (COLOUR_PINK) :
			toRet = "Pink";
			break;
		default :
			toRet = "ERROR: Attempted to convert invalid Colour";
	}

	return toRet;
}