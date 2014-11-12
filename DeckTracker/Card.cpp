
#include "Card.h"
#include "StringUtility.h"

Card::Card() {

    filledFields = 0;
    frequency = 1;
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
Card::Card(string name, sig_t rarity, vector<string> specialText) {

    // How to deal with frequency when reading in files is a design
    // decision that has yet to be made.
    //frequency = 1;
    this->name = name;
    this->rarity = rarity;
    this->specialText = specialText;
}

Card::~Card() {}

string Card::getTextAt(int i) {
    return specialText[i];
}

//////////////////////////////////////////////
//        Operator Overloads
//////////////////////////////////////////////
bool Card::operator==(Card* toCompare) {

    return (name.compare(toCompare->name) == 0);
}

//////////////////////////////////////////////
//        Protected Methods
//////////////////////////////////////////////

string Card::accessName() {
    return name;
}

sig_t Card::accessRarity() {
    return rarity;
}

vector<string> Card::accessSpecialText() {
    return specialText;
}

bool Card::modifyName(string newName) {
    name = newName;

    if (newName.compare("") != 0) {
        name = newName;
        return true;
    }
    else
        return false;
}

bool Card::modifyRarity(string newRarity) {
    sig_t prospectiveRarity = stringToRarity(newRarity);
    if (rarityMap.find(static_cast<int>(prospectiveRarity)) != rarityMap.end()) {
        rarity = prospectiveRarity;
        return true;
    }
    else
        return false;
}

void Card::modifySpecialText(vector<string> newText) {
    specialText = newText;
}

void Card::printSpecialText() {

    std::cout << "Special Text: ";

    if (specialText.size() == 0)
        std::cout << "N/A" << endl;
    else {
        for (unsigned int i = 0; i < specialText.size(); ++i) {
            std::cout << specialText[i] << endl;
        }
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

const int Card::accessFrequency() const {
    return frequency;
}

void Card::incrementFrequency() {
    frequency++;
}

void Card::decrementFrequency() {
    frequency--;
}

//////////////////////////////////////////////
//        Static Enum Converters
//////////////////////////////////////////////

sig_t Card::stringToColour(string toConvert) {

    sig_t colour;
    StringUtility::toLowerCase(toConvert);

    if (toConvert.compare("none") == 0)
        colour = COLOUR_SIG_NONE;
    else if (toConvert.compare("purple") == 0)
        colour = COLOUR_SIG_PURPLE;
    else if (toConvert.compare("white") == 0)
        colour = COLOUR_SIG_WHITE;
    else if (toConvert.compare("yellow") == 0)
        colour = COLOUR_SIG_YELLOW;
    else if (toConvert.compare("orange") == 0)
        colour = COLOUR_SIG_ORANGE;
    else if (toConvert.compare("pink") == 0)
        colour = COLOUR_SIG_PINK;
    else if (toConvert.compare("blue") == 0)
        colour = COLOUR_SIG_BLUE;
    else
        colour = -1;

    return colour;
}

void Card::printAcceptableColours(bool allowNone) {
    std::cout << "Acceptable Colours: " << endl;
    std::cout << "Purple\nWhite\nYellow\nPink\nOrange\nBlue\n";
    
    // Some kinds are cards are allowed to have no colour.
    if (allowNone) std::cout << "None\n";
}

sig_t Card::stringToRarity(string toConvert) {

    sig_t rarity;
    StringUtility::toLowerCase(toConvert);

    if (toConvert.compare("common") == 0)
        rarity = RARITY_SIG_COMMON;
    else if (toConvert.compare("uncommon") == 0)
        rarity = RARITY_SIG_UNCOMMON;
    else if (toConvert.compare("rare") == 0)
        rarity = RARITY_SIG_RARE;
    else if (toConvert.compare("ultra rare") == 0)
        rarity = RARITY_SIG_ULTRA_RARE;
    else if (toConvert.compare("fixed") == 0)
        rarity = RARITY_SIG_FIXED;
    else if (toConvert.compare("promo") == 0)
        rarity = RARITY_SIG_PROMOTIONAL;
    else
        rarity = -1;

    return rarity;
}

void Card::printAcceptableRarities() {
    std::cout << "Acceptable Rarities: " << endl;
    std::cout << "Common\nUncommon\nRare\nUltra Rare\nFixed\nPromo\n";
}