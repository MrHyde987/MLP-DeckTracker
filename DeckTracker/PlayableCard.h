#ifndef _PLAYABLE_CARD_
#define _PLAYABLE_CARD_

#include "DeckTracker.h"

#include "Card.h"
#include "StringUtility.h"

extern SigMap speciesMap;

class PlayableCard : public Card {

    friend class ManifestInterface;

private:
    sig_t colour;
    int power;
    uint8_t typeModifiers;

public:

    PlayableCard();

    PlayableCard(string name);

    PlayableCard(
        sig_t colour, 
        int power, 
        uint8_t typeModifiers, 
        string name, 
        sig_t rarity, 
        vector<string> text);
    
    // Abstract Class
    virtual ~PlayableCard();

    // The type modifiers are all different for the various classes underneath here.
    // So each of them will need to define their own way to deal with the strings entered.
    virtual bool modifyTypeModifiers(string newTypes) = 0;
    virtual void printTypeModifiers() = 0;

protected:
    sig_t accessColour();
    int accessPower();
    uint8_t accessTypeModifiers();

    bool modifyColour(string newColour);
    bool modifyPower(string newPower);

    void assignTypeModifier(uint8_t newTypes);

    static sig_t stringToSpecies(string toSpecies);
    static void printAcceptableSpecies();
};
#endif // _PLAYABLE_CARD_