#ifndef _EVENT_
#define _EVENT_
#include "DeckTracker.h"
#include "FRE.h"

class ManifestInterface;

class Event : public FRE {

    friend class ManifestInterface;

public:

    Event();

    Event(string name);

    Event(
        int actionCost,
        int developmentCost,
        sig_t colour,
        int power,
        uint8_t typeModifiers,
        string name,
        sig_t rarity,
        vector<string> specialText);

    ~Event();

    void printStats();
    bool addFields(string inputToAdd);
    bool isCardComplete();

    bool modifyTypeModifiers(string newModifiers);
    void printTypeModifiers();

private:
    const static int NUM_FIELDS = 7;
};
#endif // _EVENT_