#ifndef _TM_
#define _TM_
#include "DeckTracker.h"
#include "PlayableCard.h"

class TroubleMaker : public PlayableCard {

    friend class ManifestInterface;

private:
    int pointValue;
    bool isVillain;

    const static int NUM_FIELDS = 5;

public:
    TroubleMaker();
    TroubleMaker(string name);
    TroubleMaker(
        int pointValue,
        bool isVillain,
        sig_t colour,
        int power,
        uint8_t typeModifiers,
        string name,
        sig_t rarity,
        vector<string> text);

    ~TroubleMaker();

    void printStats();
    bool addFields(string inputToAdd);
    bool isCardComplete();

    bool modifyTypeModifiers(string newTypes);
    void printTypeModifiers();

    string makeManifestString();
};
#endif // _TM_