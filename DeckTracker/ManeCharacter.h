#ifndef _MANE_CHARACTER_
#define _MANE_CHARACTER_
#include "PlayableCard.h"

class ManeCharacter : public PlayableCard {

private:
	string flipCondition;
	int flippedPower;
	
	const static int NUM_PROPERTIES = 6;

public:

	ManeCharacter();
	ManeCharacter(
		string flipCondition,
		int flippedPower,
		Colour colour,
		int power,
		string name,
		vector<string> specialText);

	~ManeCharacter();

	void printStats();
	static void formatPrompt();
	static bool validateInput(vector<string> input);
	void buildCard(vector<string> formattedInput);
};
#endif // _PLAYABLE_CARD_