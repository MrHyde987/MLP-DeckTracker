#ifndef _TM_
#define _TM_
#include "PlayableCard.h"

class TroubleMaker : public PlayableCard {

private:
	int pointValue;
	bool isVillain;

	const static int NUM_FIELDS = 5;

public:
	TroubleMaker();
	TroubleMaker(string name);
	TroubleMaker(
		int pointValue,
		bool isVillain,
		Colour colour,
		int power,
		string name,
		Rarity rarity,
		vector<string> text);

	~TroubleMaker();

	void printStats();
	bool addFields(string inputToAdd);
	bool isCardComplete();
};
#endif // _TM_