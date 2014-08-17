
#ifndef _CARD_
#define _CARD_
#include <string>
#include <vector>
#include <iostream>

using namespace std;

typedef enum {
	COLOUR_INVALID,
	COLOUR_NONE,
	COLOUR_PURPLE,
	COLOUR_WHITE,
	COLOUR_YELLOW,
	COLOUR_ORANGE,
	COLOUR_BLUE,
	COLOUR_PINK
} Colour;

typedef enum {
	RARITY_INVALID,
	RARITY_COMMON,
	RARITY_UNCOMMON,
	RARITY_RARE,
	RARITY_ULTRA_RARE,
	RARITY_FIXED,
	RARITY_FOIL,
	RARITY_PROMO
} Rarity;

class Card {

private:
	int frequency;
	string name;
	Rarity rarity;
	vector<string> specialText;

	// This is a state variable used to track the progress of building a card
	// Every class will do this in a similar way, thus they all need this variable.
	int filledFields;

public:
	Card();
	Card(string name);
	Card(string name, Rarity rarity, vector<string> text);
	
	// Abstract Class
	virtual void printStats() = 0;
	virtual bool addFields(string inputToAdd) = 0;
	virtual bool isCardComplete() = 0;
	
	virtual ~Card();

	bool operator==(Card* toCompare);

	void incrementFrequency();
	void decrementFrequency();

protected:
	string accessName();
	Rarity accessRarity();
	vector<string> accessSpecialText();
	
	void modifyName(string newName);
	bool modifyRarity(string newRarity);
	void modifySpecialText(vector<string> newText);
	void printSpecialText();
	void pushSpecialText(string textToAdd);
	
	const int accessFieldsAdded() const;
	void incrementAddedFields();

	const int accessFrequency() const;

	static Colour stringToColour(string toConvert);
	static string colourToString(Colour toConvert);
	static void printAcceptableColours(bool allowNone);

	static Rarity stringToRarity(string toConvert);
	static string rarityToString(Rarity toConvert);
	static void printAcceptableRarities();
};

#endif // ndef _CARD_