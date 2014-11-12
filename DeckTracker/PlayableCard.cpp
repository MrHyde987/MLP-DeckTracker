#include "PlayableCard.h"

PlayableCard::PlayableCard() {}

PlayableCard::PlayableCard(string name) : Card(name) {}

PlayableCard::PlayableCard(
    sig_t colour,
    int power,
    uint8_t typeModifiers,
    string name,
    sig_t rarity,
    vector<string> specialText) : Card(name, rarity, specialText) {

    this->colour = colour;
    this->power = power;
    this->typeModifiers = typeModifiers;
}

PlayableCard::~PlayableCard() {}

sig_t PlayableCard::accessColour() {
    return colour;
}

int PlayableCard::accessPower() {
    return power;
}

uint8_t PlayableCard::accessTypeModifiers() {
    return typeModifiers;
}

bool PlayableCard::modifyColour(string newColour) {
    sig_t prospectiveColour = Card::stringToColour(newColour);
    if (colourMap.find(prospectiveColour) != colourMap.end()) {
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

sig_t PlayableCard::stringToSpecies(string toSpecies) {

    sig_t newSpecies;
    StringUtility::toLowerCase(toSpecies);

    if (toSpecies.compare("unicorn") == 0)
        newSpecies = SPECIES_SIG_UNICORN;
    else if (toSpecies.compare("pegasus") == 0)
        newSpecies = SPECIES_SIG_PEGASUS;
    else if (toSpecies.compare("earth pony") == 0)
        newSpecies = SPECIES_SIG_EARTH_PONY;
    else if (toSpecies.compare("alicorn") == 0)
        newSpecies = SPECIES_SIG_ALICORN;
    else if (toSpecies.compare("critter") == 0)
        newSpecies = SPECIES_SIG_CRITTER;
    else if (toSpecies.compare("dragon") == 0)
        newSpecies = SPECIES_SIG_DRAGON;
    else if (toSpecies.compare("zebra") == 0)
        newSpecies = SPECIES_SIG_ZEBRA;
    else if (toSpecies.compare("buffalo") == 0)
        newSpecies = SPECIES_SIG_BUFFALO;
    else
        newSpecies = -1;

    return newSpecies;
}

void PlayableCard::assignTypeModifier(uint8_t newTypes) {
    typeModifiers = newTypes;
}

void PlayableCard::printAcceptableSpecies() {
    std::cout << "Acceptable Species: " << endl;
    std::cout << "Unicorn\nPegasus\nEarth pony\nAlicorn\nZebra\nDragon\nBuffalo\n";
}