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
		string name,
		vector<string> specialText);

	~Event();

	void printStats();
	bool addFields(string inputToAdd);
	bool isCardComplete();

private:
	const static int NUM_FIELDS = 5;
};
#endif // _EVENT_