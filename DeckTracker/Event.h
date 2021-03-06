#ifndef _EVENT_
#define _EVENT_
#include "FRE.h"

class Event : public FRE {

public:

	Event();

	Event(string name);

	Event(
		int actionCost,
		int developmentCost,
		Colour colour,
		int power,
		vector<string> typeModifiers,
		string name,
		Rarity rarity,
		vector<string> specialText);

	~Event();

	void printStats();
	bool addFields(string inputToAdd);
	bool isCardComplete();

private:
	const static int NUM_FIELDS = 7;
};
#endif // _EVENT_