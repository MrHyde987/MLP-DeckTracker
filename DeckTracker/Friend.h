#ifndef _FRIEND_
#define _FRIEND_
#include "DeckTracker.h"
#include "FRE.h"

class Friend : public FRE {

    friend class ManifestInterface;

private:
    sig_t species;
    const static int NUM_FIELDS = 8;

public:
    Friend();
    Friend(string name);
    Friend(
        sig_t species,
        int actionCost,
        int developmentCost,
        sig_t colour,
        int power,
        uint8_t typeModifiers,
        string name,
        sig_t rarity,
        vector<string> specialText);

    ~Friend();

    void printStats();
    bool addFields(string inputToAdd);
    bool isCardComplete();

    bool modifyTypeModifiers(string newModifiers);
    void printTypeModifiers();
};
#endif _FRIEND_