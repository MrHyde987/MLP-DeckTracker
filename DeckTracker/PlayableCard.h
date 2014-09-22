#ifndef _PLAYABLE_CARD_
#define _PLAYABLE_CARD_
#include "Card.h"
#include "StringUtility.h"

// Both ManeCharacter and Friend need access to the concept of a Species.
typedef enum {

	SPECIES_INVALID,
	SPECIES_UNICORN,
	SPECIES_PEGASUS,
	SPECIES_EP,
	SPECIES_ALICORN,
	SPECIES_ZEBRA,
	SPECIES_CRITTER,
	SPECIES_DRAGON,
	SPECIES_BUFFALO

} Species;

class PlayableCard : public Card {

private:
	Colour colour;
	int power;
	vector<string> typeModifiers;

public:

	PlayableCard();

	PlayableCard(string name);

	PlayableCard(
		Colour colour, 
		int power, 
		vector<string> typeModifiers, 
		string name, 
		Rarity rarity, 
		vector<string> text);
	
	// Abstract Class
	virtual ~PlayableCard();

protected:
	Colour accessColour();
	int accessPower();
	vector<string> accessTypeModifiers();

	bool modifyColour(string newColour);
	bool modifyPower(string newPower);
	bool modifyTypeModifiers(vector<string> newTypes);

	bool pushTypeModifier(string newModifier);
	void printTypeModifiers();

	static Species stringToSpecies(string toSpecies);
	static string speciesToString(Species toString);
	static void printAcceptableSpecies();
};
#endif // _PLAYABLE_CARD_