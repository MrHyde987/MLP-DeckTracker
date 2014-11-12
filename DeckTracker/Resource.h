#ifndef _RESOURCE_
#define _RESOURCE_
#include "DeckTracker.h"
#include "FRE.h"

extern SigMap locationMap;

class Resource : public FRE {

    friend class ManifestInterface;

private:
    sig_t location;
    
    const static int NUM_FIELDS = 8;

    static sig_t stringToLocation(string toConvert);
    static void printAcceptableLocations();

public:
    Resource();
    Resource(string name);
    Resource(
        sig_t location,
        int actionCost,
        int developmentCost,
        sig_t colour,
        int power,
        uint8_t typeModifiers,
        string name,
        sig_t rarity,
        vector<string> specialText);

    ~Resource();

    void printStats();
    bool addFields(string inputToAdd);
    bool isCardComplete();

    bool modifyTypeModifiers(string newModifiers);
    void printTypeModifiers();
};
#endif // _RESOURCE_
