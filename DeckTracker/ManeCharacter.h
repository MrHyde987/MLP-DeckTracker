#ifndef _MANE_CHARACTER_
#define _MANE_CHARACTER_
#include "PlayableCard.h"

class ManeCharacter : public PlayableCard {

private:
	string startFlipCondition;
	string boostedFlipCondition;
	Species species;
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
		Species species,
		int flippedPower,
		int startHomeLimit,
		int flippedHomeLimit,
		Colour colour,
		int power,
		vector<string> typeModifiers,
		string name,
		Rarity rarity,
		string startSpecialText,
		vector<string> specialText);

	~ManeCharacter();

	void printStats();
	bool addFields(string inputToAdd);
	bool isCardComplete();
};
#endif // _PLAYABLE_CARD_