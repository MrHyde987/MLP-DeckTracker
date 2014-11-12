#include "TroubleMaker.h"
#include "StringUtility.h"
#include "boost/format.hpp"

TroubleMaker::TroubleMaker() {}
TroubleMaker::TroubleMaker(string name) : PlayableCard(name) {}
TroubleMaker::TroubleMaker(
    int pointValue,
    bool isVillain,
    sig_t colour,
    int power,
    uint8_t typeModifiers,
    string name,
    sig_t rarity,
    vector<string> specialText) : PlayableCard(colour, power, typeModifiers, name, rarity, specialText) {

    this->pointValue = pointValue;
    this->isVillain = isVillain;
}

TroubleMaker::~TroubleMaker() {}

void TroubleMaker::printStats() {
    std::cout << boost::format("%1% (%2% Owned)\nRarity: %3%\nVillain: %4%\nPower: %5%\nPts: %6%")
        % accessName() % accessFrequency() % (rarityMap.find(accessRarity()))->second % (isVillain ? "True " : "False") % accessPower() % pointValue << std::endl;
    printTypeModifiers();
    printSpecialText();
}

bool TroubleMaker::addFields(string inputToAdd) {

    switch (accessFieldsAdded()) {

        case(0) :
            // Require the name
            if (modifyName(inputToAdd)) {
                modifyColour("None"); // All TMs have no colour
                std::cout << "Rarity: ";
                break;
            }
            else {
                std::cout << "ERROR: Invalid Name entered for Trouble Maker.\n";
                std::cout << "Name: ";
                return false;
            }
        case(1) :
            // Rarity
            if (modifyRarity(inputToAdd)) {
                std::cout << "PointValue: ";
                break;
            }
            else {
                std::cout << "ERROR: Invalid Rarity entered for Trouble Maker.\n";
                Card::printAcceptableRarities();
                std::cout << "Rarity: ";
                return false;
            }
        case(2) :
            // Point Value
            if (StringUtility::checkIsPositiveInt(inputToAdd)) {
                pointValue = StringUtility::stringToInt(inputToAdd);
                std::cout << "Villain? ";
                break;
            }
            else {
                std::cout << "ERROR: Invalid Point Value entered for Trouble Maker.\nPoint Value: ";
                return false;
            }
        case(3) :
            // Is Villain?
            if (StringUtility::checkIsBool(inputToAdd)) {
                isVillain = StringUtility::stringToBool(inputToAdd);
                std::cout << "Faceoff Power: ";
                break;
            }
            else {
                std::cout << "ERROR: Invalid isVillain value entered for Trouble Maker.\nVillain? ";
                return false;
            }
        case(4) :
            // Faceoff Power
            if (modifyPower(inputToAdd)) {
                std::cout << "Special Text: ";
                break;
            }
            else {
                std::cout << "ERROR: Invalid Faceoff Power entered for Event.\nFaceoff Power: ";
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

bool TroubleMaker::isCardComplete() {
    return accessFieldsAdded() >= NUM_FIELDS;
}

bool TroubleMaker::modifyTypeModifiers(string newTypes) {

    // Troublemakers currently only support the "Epic" modifier
    // which just means "Villain" in the current rule set.
    // So there is no real reason to implement anything here.
    return true;
}

void TroubleMaker::printTypeModifiers() {

    // Troublemakers have no real modifiers to print.
}

//string TroubleMaker::makeManifestString() {
//    return (boost::format("TroubleMaker,%1%,%2%,%3%,%4%,%5%,%6%,%7%,%8%") 
//        % accessName() 
//        % accessRarity() 
//        % ).str();
//}