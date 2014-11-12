#include "Resource.h"
#include "StringUtility.h"
#include "boost/format.hpp"

Resource::Resource() {}
Resource::Resource(string name) : FRE(name) {}
Resource::Resource(
    sig_t location,
    int actionCost,
    int developmentCost,
    sig_t colour,
    int power,
    uint8_t typeModifiers,
    string name,
    sig_t rarity,
    vector<string> specialText) : FRE(actionCost, developmentCost, colour, power, typeModifiers, name, rarity, specialText) {

    this->location = location;
}

Resource::~Resource() {}

void Resource::printStats() {

    std::cout << boost::format("%1% (%2% Owned)\nRarity: %3%\nAction Cost: %4%\nColour: %5%\nColour Cost: %6%\nPower: %7%\nLocation: %8%")
        % accessName() % accessFrequency() % rarityMap.find(accessRarity())->second % accessActionCost() 
        % colourMap.find(accessColour())->second % accessDevelopmentCost() 
        % accessPower() % locationMap.find(location)->second << std::endl;
    printTypeModifiers();
    printSpecialText();
}

bool Resource::addFields(string inputToAdd) {
    
    sig_t prospectiveLocation;

    switch (accessFieldsAdded()) {

        case(0) :
            // Require the name
            if (modifyName(inputToAdd)) {
                std::cout << "Rarity: ";
                break;
            }
            else {
                std::cout << "ERROR: Invalid name entered for Resource.\n";
                std::cout << "Name: ";
                return false;
            }
        case(1) :
            if (modifyRarity(inputToAdd)) {
                std::cout << "Type Modifiers (e.g. Report etc.): ";
                break;
            }
            else {
                std::cout << "ERROR: Invalid Rarity entered for Resource.\n";
                Card::printAcceptableRarities();
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
                std::cout << "ERROR: Invalid Types passed to Resource.\n";
                return false;
            }
        case(3) :
            // Require a Colour next
            if (modifyColour(inputToAdd)) {
                // Prompt for next field:
                std::cout << "Action Cost: ";
                break;
            }
            else {
                std::cout << "ERROR: Invalid colour entered for Resource.\n";
                Card::printAcceptableColours(true);
                std::cout << "Colour: ";
                return false;
            }
        case(4) :
            // Action Cost
            if (modifyActionCost(inputToAdd)) {
                std::cout << "Colour Cost (0 if none): ";
                break;
            }
            else {
                std::cout << "ERROR: Invalid Action Cost entered for Resource.\nAction Cost: ";
                return false;
            }
        case(5) :
            // Colour Cost
            if (modifyDevelopmentCost(inputToAdd)) {
                std::cout << "Faceoff Power: ";
                break;
            }
            else {
                std::cout << "ERROR: Invalid Colour Cost entered for Resource.\nColour Cost (0 if none): ";
                return false;
            }
        case(6) :
            // Faceoff Power
            if (modifyPower(inputToAdd)) {
                std::cout << "Location: ";
                break;
            }
            else {
                std::cout << "ERROR: Invalid Faceoff Power entered for Resource.\nFaceoff Power: ";
                return false;
            }
        case(7) :
            // Location
            prospectiveLocation = stringToLocation(inputToAdd);
            if (locationMap.find(prospectiveLocation) != locationMap.end()) {
                location = prospectiveLocation;
                // Prompt for next field:
                std::cout << "Special Text: ";
                break;
            }
            else {
                std::cout << "ERROR: Invalid location entered for Resource.\n";
                printAcceptableLocations();
                std::cout << "Location: ";
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

bool Resource::isCardComplete() {
    return accessFieldsAdded() >= NUM_FIELDS;
}

sig_t Resource::stringToLocation(string toConvert) {

    sig_t newLocation;
    StringUtility::toLowerCase(toConvert);
    
    if (toConvert.compare("home") == 0)
        newLocation = LOCATION_SIG_HOME;
    else if (toConvert.compare("friend") == 0)
        newLocation = LOCATION_SIG_FRIEND;
    else if (toConvert.compare("opposing friend") == 0)
        newLocation = LOCATION_SIG_OPPOSING_FRIEND;
    else if (toConvert.compare("trouble maker") == 0)
        newLocation = LOCATION_SIG_TROUBLEMAKER;
    else if (toConvert.compare("problem") == 0)
        newLocation = LOCATION_SIG_PROBLEM;
    else if (toConvert.compare("mane character") == 0)
        newLocation = LOCATION_SIG_MANE_CHARACTER;
    else if (toConvert.compare("opposing mane character") == 0)
        newLocation = LOCATION_SIG_OPP_MC;
    else
        newLocation = -1;

    return newLocation;
}

void Resource::printAcceptableLocations() {
    std::cout << "Accepatble Locations: " << endl;
    std::cout << "Home\nFriend\nOpposing Friend\nTrouble Maker\nProblem\nMane Character\nOpposing Mane Character\n";
}

bool Resource::modifyTypeModifiers(string newModifiers) {
    uint8_t modifierVector = 0;
    vector<string> modifiers;
    bool entryIsValid = true;

    StringUtility::split(newModifiers, ';', modifiers);

    for (iter_t i = 0; i < modifiers.size() && entryIsValid; ++i) {

        // Supported Modifiers
        // Elder, Foal, Royalty, Unique
        StringUtility::toLowerCase(modifiers[i]);
        if (modifiers[i].compare("location") == 0)
            modifierVector |= RES_TYPEARG_LOCATION;
        else if (modifiers[i].compare("asset") == 0)
            modifierVector |= RES_TYPEARG_ASSET;
        else if (modifiers[i].compare("report") == 0)
            modifierVector |= RES_TYPEARG_REPORT;
        else if (modifiers[i].compare("accessory"))
            modifierVector |= RES_TYPEARG_ACCESSORY;
        else if (modifiers[i].compare("condition"))
            modifierVector |= RES_TYPEARG_CONDITION;
        else if (modifiers[i].compare("artifact"))
            modifierVector |= RES_TYPEARG_ARTIFACT;
        else if (modifiers[i].compare("unique") == 0)
            modifierVector |= TYPEARG_UNIQUE;
        else
            entryIsValid = false;
    }

    if (entryIsValid)
        assignTypeModifier(modifierVector);

    return entryIsValid;
}

void Resource::printTypeModifiers() {
    
    uint8_t modifierVector = accessTypeModifiers();
    bool typesPresent = modifierVector == 0;
    
    if (typesPresent) {
        std::cout << "Special Types: ";

        if ((modifierVector & RES_TYPEARG_LOCATION) > 0)
            std::cout << "Location; ";
        if ((modifierVector & RES_TYPEARG_ASSET) > 0)
            std::cout << "Asset; ";
        if ((modifierVector & RES_TYPEARG_REPORT) > 0)
            std::cout << "Report; ";
        if ((modifierVector & RES_TYPEARG_ACCESSORY) > 0)
            std::cout << "Accessory; ";
        if ((modifierVector & RES_TYPEARG_CONDITION) > 0)
            std::cout << "Condition; ";
        if ((modifierVector & RES_TYPEARG_ARTIFACT) > 0)
            std::cout << "Artifact; ";
        if ((modifierVector & TYPEARG_UNIQUE) > 0)
            std::cout << "Unique; ";
        std::cout << std::endl;
    }
}