#ifndef _MANE_CHARACTER_
#define _MANE_CHARACTER_
#include "PlayableCard.h"

class ManeCharacter : public PlayableCard {

private:
	string flipCondition;
	int flippedPower;
	int startHomeLimit;
	int flippedHomeLimit;
	
	const static int NUM_FIELDS = 8;

public:

	ManeCharacter();
	ManeCharacter(string name);
	ManeCharacter(
		string flipCondition,
		int flippedPower,
		int startHomeLimit,
		int flippedHomeLimit,
		Colour colour,
		int power,
		string name,
		Rarity rarity,
		vector<string> specialText);

	~ManeCharacter();

	void printStats();
	bool addFields(string inputToAdd);
	bool isCardComplete();
};
#endif // _PLAYABLE_CARD_