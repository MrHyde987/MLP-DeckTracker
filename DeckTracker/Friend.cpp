#include "Friend.h"
#include "StringUtility.h"
#include "boost/format.hpp"

Friend::Friend() {}

Friend::Friend(string name) : FRE(name) {}

Friend::Friend(
    sig_t species,
    int actionCost,
    int developmentCost,
    sig_t colour,
    int power,
    uint8_t typeModifiers,
    string name,
    sig_t rarity,
    vector<string> specialText) : FRE(actionCost, developmentCost, colour, power, typeModifiers, name, rarity, specialText) {

    this->species = species;
}

Friend::~Friend() {}

void Friend::printStats() {

    std::cout << boost::format("%1% (%2% Owned)\nRarity: %3%\nAction Cost: %4%\nColour: %5%\nColour Cost: %6%\nPower: %7%\nSpecies: %8%") 
        % accessName() %accessFrequency() % rarityMap.find(accessRarity())->second % accessActionCost() % colourMap.find(accessColour())->second
        % accessDevelopmentCost() % accessPower() % speciesMap.find(species)->second << std::endl;
    printTypeModifiers();
    printSpecialText();
}

bool Friend::addFields(string inputToAdd) {

    sig_t prospectiveSpecies;

    switch (accessFieldsAdded()) {

        case (0) :
            // Require the name
            if (modifyName(inputToAdd)) {
                std::cout << "Rarity: ";
                break;
            }
            else {
                std::cout << "ERROR: Invalid name entered for Friend.\n";
                std::cout << "Name: ";
                return false;
            }
        case (1) :
            // Rarity
            if (modifyRarity(inputToAdd))  {
                std::cout << "Type Modifiers (e.g. Royalty etc.): ";
                break;
            }
            else {
                std::cout << "ERROR: Invalid Rarity entered for Friend.\n";
                printAcceptableRarities();
                std::cout << "Rarity: ";
                return false;
            }
        case (2) :
            // Type Modifiers
            if (modifyTypeModifiers(inputToAdd)) {
                std::cout << "Colour: ";
                break;
            }
            else {
                std::cout << "ERROR: Invalid Types enterd for Friend.\n";
                return false;
            }
        case (3) :
            // Require a Colour next
            if (modifyColour(inputToAdd)) {
                // Prompt for next field:
                std::cout << "Species: ";
                break;
            }
            else {
                std::cout << "ERROR: Invalid colour passed to Friend.\n";
                Card::printAcceptableColours(false);
                std::cout << "Colour: ";
                return false;
            }
        case(4) :
            // Species
            prospectiveSpecies = stringToSpecies(inputToAdd);
            if (speciesMap.find(prospectiveSpecies) != speciesMap.end()) {
                species = prospectiveSpecies;
                // Prompt for next field:
                std::cout << "Action Cost: ";
                break;
            }
            else {
                std::cout << "ERROR: Invalid Species passed to Friend.\n";
                printAcceptableSpecies();
                std::cout << "Species :";
                return false;
            }
        case (5) :
            // Action Cost
            if (modifyActionCost(inputToAdd)) {
                std::cout << "Colour Cost (0 if none): ";
                break;
            }
            else {
                std::cout << "ERROR: Invalid Action Cost entered for Friend.\nAction Cost: ";
                return false;
            }
        case (6) :
            // Colour Cost
            if (modifyDevelopmentCost(inputToAdd)) {
                std::cout << "Faceoff Power: ";
                break;
            }
            else {
                std::cout << "ERROR: Invalid Colour Cost entered for Friend.\nColour Cost (0 if none): ";
                return false;
            }
        case (7) :
            // Faceoff Power
            if (modifyPower(inputToAdd)) {
                std::cout << "Special Text: ";
                break;
            }
            else {
                std::cout << "ERROR: Invalid Faceoff Power entered for Friend.\nFaceoff Power: ";
                return false;
            }
        default :
            // Special Text is being added
            pushSpecialText(inputToAdd);
            return true;
    }

    incrementAddedFields();
    return true;
}

bool Friend::isCardComplete() {
    return accessFieldsAdded() >= NUM_FIELDS;
}

// Friend and Mane Character support the same type Modifiers
bool Friend::modifyTypeModifiers(string newModifiers) {
    
    uint8_t modifierVector = 0;
    vector<string> modifiers;
    bool entryIsValid = true;

    StringUtility::split(newModifiers, ';', modifiers);

    for (iter_t i = 0; i < modifiers.size() && entryIsValid; ++i) {

        // Supported Modifiers
        // Elder, Foal, Royalty, Unique
        StringUtility::toLowerCase(modifiers[i]);
        if (modifiers[i].compare("elder") == 0)
            modifierVector |= TYPEARG_ELDER;
        else if (modifiers[i].compare("foal") == 0)
            modifierVector |= TYPEARG_FOAL;
        else if (modifiers[i].compare("royalty") == 0)
            modifierVector |= TYPEARG_ROYALTY;
        else if (modifiers[i].compare("unique") == 0)
            modifierVector |= TYPEARG_UNIQUE;
        else
            entryIsValid = false;
    }

    if (entryIsValid)
        assignTypeModifier(modifierVector);

    return entryIsValid;
}

void Friend::printTypeModifiers() {
    
    uint8_t modifierVector = accessTypeModifiers();
    bool typesPresent = modifierVector == 0;
    
    if (typesPresent) {
        std::cout << "Special Types: ";

        if ((modifierVector & TYPEARG_ELDER) > 0)
            std::cout << "Elder; ";
        if ((modifierVector & TYPEARG_FOAL) > 0)
            std::cout << "Foal; ";
        if ((modifierVector & TYPEARG_ROYALTY) > 0)
            std::cout << "Royalty; ";
        if ((modifierVector & TYPEARG_UNIQUE) > 0)
            std::cout << "Unique; ";
        std::cout << std::endl;
    }
}