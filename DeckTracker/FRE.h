
// FRE --> Friends, Resources, and Events
#ifndef _FRE_
#define _FRE_
#include "DeckTracker.h"
#include "PlayableCard.h"

class FRE : public PlayableCard {

    friend class ManifestInterface;

private:
    int actionCost;
    int developmentCost;

public:

    FRE();
    FRE(string name);
    FRE(
        int actionCost,
        int developmentCost,
        sig_t colour,
        int power,
        uint8_t typeModifiers,
        string name,
        sig_t rarity,
        vector<string> specialText);
    // Abstract class
    virtual ~FRE();

protected:
    int accessActionCost();
    int accessDevelopmentCost();

    bool modifyActionCost(string newAC);
    bool modifyDevelopmentCost(string newDC);
};
#endif // _FRE_