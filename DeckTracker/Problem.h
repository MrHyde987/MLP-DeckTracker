#ifndef _PROBLEM_
#define _PROBLEM_

#include "DeckTracker.h"

#include "Card.h"

#include <iostream>

class Problem : public Card {

    friend class ManifestInterface;

private:
    int pointBonus;
    int neutralConfrontCost;
    sig_t primaryColour;
    sig_t secondaryColour;
    int primaryColourConfrontCost;
    int secondaryColourConfrontCost;
    bool isStarting;

    const static int NUM_FIELDS = 9;

public:
    Problem();
    Problem(string name);
    Problem(
        int pointBonus,
        int neutralConfrontCost,
        sig_t primaryColour,
        sig_t secondaryColour,
        int primaryColourConfrontCost,
        int secondaryColourConfrontCost,
        bool isStarting,
        string name,
        sig_t rarity,
        vector<string> specialText);

    ~Problem();

    void printStats();
    bool addFields(string inputToAdd);
    bool isCardComplete();
};
#endif // _PROBLEM_