
#ifndef _CARD_
#define _CARD_

#include "DeckTracker.h"

#include <string>
#include <vector>
#include <iostream>

using namespace std;

extern SigMap rarityMap;
extern SigMap colourMap;

class Card {

    // Allowing the file interface class direct access makes reading and writing to files a lot easier.
    friend class ManifestInterface;

private:
    int frequency;
    string name;
    sig_t rarity;
    vector<string> specialText;

    // This is a state variable used to track the progress of building a card
    // Every class will do this in a similar way, thus they all need this variable.
    int filledFields;

public:
    Card();
    Card(string name);
    Card(string name, sig_t rarity, vector<string> text);
    
    // Abstract Class
    virtual void printStats() = 0;
    virtual bool addFields(string inputToAdd) = 0;
    virtual bool isCardComplete() = 0;
    //virtual string makeManifestString() = 0;
    // virtual Card* parseManifestEntry(string entry) = 0;
    
    virtual ~Card();

    bool operator==(Card* toCompare);

    void incrementFrequency();
    void decrementFrequency();

    string getTextAt(int i);

protected:
    string accessName();
    sig_t accessRarity();
    vector<string> accessSpecialText();
    
    bool modifyName(string newName);
    bool modifyRarity(string newRarity);
    void modifySpecialText(vector<string> newText);
    void printSpecialText();
    void pushSpecialText(string textToAdd);
    
    const int accessFieldsAdded() const;
    void incrementAddedFields();

    const int accessFrequency() const;

    static sig_t stringToColour(string toConvert);
    static void printAcceptableColours(bool allowNone);

    static sig_t stringToRarity(string toConvert);
    static void printAcceptableRarities();
};

#endif // ndef _CARD_