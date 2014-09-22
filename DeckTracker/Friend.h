#ifndef _FRIEND_
#define _FRIEND_
#include "FRE.h"

class Friend : public FRE {

private:
	Species species;
	const static int NUM_FIELDS = 8;

public:
	Friend();
	Friend(string name);
	Friend(
		Species species,
		int actionCost,
		int developmentCost,
		Colour colour,
		int power,
		vector<string> typeModifiers,
		string name,
		Rarity rarity,
		vector<string> specialText);

	~Friend();

	void printStats();
	bool addFields(string inputToAdd);
	bool isCardComplete();
};
#endif _FRIEND_