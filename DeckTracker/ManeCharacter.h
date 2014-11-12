#ifndef _MANE_CHARACTER_
#define _MANE_CHARACTER_
#include "DeckTracker.h"
#include "PlayableCard.h"

class ManeCharacter : public PlayableCard {

    friend class ManifestInterface;

private:
    string startFlipCondition;
    string boostedFlipCondition;
    sig_t species;
    int boostedPower;
    int startHomeLimit;
    int boostedHomeLimit;
    string startSpecialText;
    
    const static int NUM_FIELDS = 12;

public:

    ManeCharacter();
    ManeCharacter(string name);
    ManeCharacter(
        string flipCondition,
        string boostedFlipCondition,
        sig_t species,
        int flippedPower,
        int startHomeLimit,
        int flippedHomeLimit,
        sig_t colour,
        int power,
        uint8_t typeModifiers,
        string name,
        sig_t rarity,
        string startSpecialText,
        vector<string> specialText);

    ~ManeCharacter();

    void printStats();
    bool addFields(string inputToAdd);
    bool isCardComplete();

    string getStartFlipCondition();
    string getBoostedFlipCondition();
    string getStartSpecialText();

    bool modifyTypeModifiers(string newTypes);
    void printTypeModifiers();
};
#endif // _PLAYABLE_CARD_