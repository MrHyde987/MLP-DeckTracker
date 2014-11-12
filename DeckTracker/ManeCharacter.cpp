#include "ManeCharacter.h"
#include "StringUtility.h"
#include "boost/format.hpp"

ManeCharacter::ManeCharacter() {}

ManeCharacter::ManeCharacter(string name) : PlayableCard(name) {}

ManeCharacter::ManeCharacter(
    std::string flipCondition,
    std::string boostedFlipCondition,
    sig_t species,
    int flippedPower,
    int startHomeLimit,
    int flippedHomeLimit,
    sig_t colour,
    int power,
    uint8_t typeModifiers,
    string name,
    sig_t rarity,
    std::string startSpecialText,
    vector<string> specialText) : PlayableCard(colour, power, typeModifiers, name, rarity, specialText) {

    this->startFlipCondition = flipCondition;
    this->boostedFlipCondition = boostedFlipCondition;
    this->species = species;
    this->boostedPower = flippedPower;
    this->startHomeLimit = startHomeLimit;
    this->boostedHomeLimit = flippedHomeLimit;
    this->startSpecialText = startSpecialText;
}

ManeCharacter::~ManeCharacter() {}

void ManeCharacter::printStats() {

    std::cout << boost::format("%1% (%2% Owned)\nRarity: %3%\nColour: %4%\nSpecies: %5%\nPower: %6%\nHome Limit: %7% \
        \nBoosted Power: %8%\nBoosted Home Limit: %9%\nFlip Condition (Start side): %10%\nFlip Condition (Boosted Side): %11% \
        \nSpecial Text (Start Side): %12%") 
        % accessName() % accessFrequency() % rarityMap.find(accessRarity())->second 
        % colourMap.find(accessColour())->second % speciesMap.find(species)->second % accessPower() % startHomeLimit
        % boostedPower % boostedHomeLimit % startFlipCondition % boostedFlipCondition
        % startSpecialText << std::endl;
    printTypeModifiers();
    printSpecialText();
}

bool ManeCharacter::addFields(string inputToAdd) {

    sig_t prospectiveSpecies;

    switch (accessFieldsAdded()) {
        case(0) :
            // Require the name
            if (modifyName(inputToAdd)) {
                std::cout << "Rarity: ";
                break;
            }
            else {
                std::cout << "ERROR: Invalid Name entered for Mane Character.\n";
                std::cout << "Name: ";
                return false;
            }
        case(1) :
            // Rarity
            if (modifyRarity(inputToAdd)) {
                std::cout << "Type Modifiers (e.g. Royalty etc.): ";
                break;
            }
            else {
                std::cout << "ERROR: Invalid Rarity entered for Mane Character.\n";
                Card::printAcceptableRarities();
                std::cout << "Rarity: ";
                return false;
            }
        case(2) :
            // Type Modifiers
            if (modifyTypeModifiers(inputToAdd)) {
                std::cout << "Colour: ";
                break;
            }
            else {
                std::cout << "ERROR: Invalid Types entered for Mane Character.\n";
                return false;
            }
        case(3) :
            // Require a Colour next
            if (modifyColour(inputToAdd)) {
                // Prompt for next field:
                std::cout << "Species: ";
                break;
            }
            else {
                std::cout << "ERROR: Invalid colour passed to Mane Character.\n";
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
                std::cout << "Initial Power: ";
                break;
            }
            else {
                std::cout << "ERROR: Invalid Species passed to Mane Character.\n";
                printAcceptableSpecies();
                std::cout << "Species :";
                return false;
            }
        case(5) :
            // Initial Power
            if (modifyPower(inputToAdd)) {
                std::cout << "Initial Home Limit: ";
                break;
            }
            else {
                std::cout << "ERROR: Invalid Initial Power entered for Mane Character.\nInitial Power: ";
                return false;
            }
        case(6) :
            // Initial Home Limit
            if (StringUtility::checkIsPositiveInt(inputToAdd)) {
                startHomeLimit = StringUtility::stringToInt(inputToAdd);
                std::cout << "Boosted Power: ";
                break;
            }
            else {
                std::cout << "ERROR: Invalid Initial Home Limit entered for Mane Character.\nInitial Home Limit: ";
                return false;
            }
        case(7) :
            // Flipped Power
            if (StringUtility::checkIsPositiveInt(inputToAdd)) {
                boostedPower = StringUtility::stringToInt(inputToAdd);
                std::cout << "Boosted Home Limit: ";
                break;
            }
            else {
                std::cout << "ERROR: Invalid Boosted Power entered for Mane Character.\nFlipped Power: ";
                return false;
            }
        case(8) :
            // Flipped Home Limit
            if (StringUtility::checkIsPositiveInt(inputToAdd)) {
                boostedHomeLimit = StringUtility::stringToInt(inputToAdd);
                std::cout << "Flip Condition (Start Side): ";
                break;
            }
            else {
                std::cout << "ERROR: Invalid Boosted Home Limit entered for Mane Character.\nFlipped Home Limit: ";
                return false;
            }
        case(9) :
            // All manes have a flip condition
            startFlipCondition = inputToAdd;
            std::cout << "Flip Condition (Boosted Side): ";
            break;
        case(10) :
            // Some manes can flip back from Boosted to Start
            if (inputToAdd.compare("") == 0)
                inputToAdd = "N/A";
            boostedFlipCondition = inputToAdd;
            std::cout << "Special Text (Start Side): ";
            break;
        case(11) :
            // Some manes have special abilities on their starting state
            if (inputToAdd.compare("") == 0)
                inputToAdd = "N/A";
            startSpecialText = inputToAdd;
            std::cout << "Special Text (Boosted Side): ";
            break;
        default :
            // Special Text is being added
            pushSpecialText(inputToAdd);
            return true;
    }

    incrementAddedFields();
    return true;
}

bool ManeCharacter::isCardComplete() {
    return accessFieldsAdded() >= NUM_FIELDS;
}

string ManeCharacter::getStartFlipCondition() {
    return startFlipCondition;
}

string ManeCharacter::getBoostedFlipCondition() {
    return boostedFlipCondition;
}

string ManeCharacter::getStartSpecialText() {
    return startSpecialText;
}

bool ManeCharacter::modifyTypeModifiers(string newTypes) {

    uint8_t modifierVector = 0;
    vector<string> modifiers;
    bool entryIsValid = true;

    StringUtility::split(newTypes, ';', modifiers);

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

void ManeCharacter::printTypeModifiers() {

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