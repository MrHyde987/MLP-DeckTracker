#ifndef _EVENT_
#define _EVENT_
#include "FRE.h"

class Event : public FRE {

public:

	Event();

	Event(
		int actionCost,
		int developmentCost,
		Colour colour,
		int power,
		string name,
		string specialText);

	~Event();

	void printStats();
	static void formatPrompt();
	static bool validateInput(vector<string> input);
	void buildCard(vector<string> formattedInput);

private:
	const static int NUM_PROPERTIES = 6;
};
#endif // _EVENT_