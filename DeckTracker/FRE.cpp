#include "FRE.h"

FRE::FRE() {}

FRE::FRE(string name) : PlayableCard(name) {}

FRE::FRE(
    int actionCost,
    int developmentCost,
    sig_t colour,
    int power,
    uint8_t typeModifiers,
    string name,
    sig_t rarity,
    vector<string> specialText) : PlayableCard(colour, power, typeModifiers, name, rarity, specialText) {

    this->actionCost = actionCost;
    this->developmentCost = developmentCost;
}

FRE::~FRE() {}

int FRE::accessActionCost() {
    return actionCost;
}

int FRE::accessDevelopmentCost() {
    return developmentCost;
}

bool FRE::modifyActionCost(string newAC) {
    if (StringUtility::checkIsPositiveInt(newAC)) {
        actionCost = StringUtility::stringToInt(newAC);
        return true;
    }
    else
        return false;
}

bool FRE::modifyDevelopmentCost(string newDC) {
    if (StringUtility::checkIsPositiveInt(newDC)) {
        developmentCost = StringUtility::stringToInt(newDC);
        return true;
    }
    else
        return false;
}

