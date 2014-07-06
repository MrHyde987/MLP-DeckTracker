#ifndef _TM_
#define _TM_
#include "PlayableCard.h"

class TroubleMaker : public PlayableCard {

private:
	int pointValue;
	bool isVillain;

	const static int NUM_PROPERTIES = 5;

public:
	TroubleMaker();
	TroubleMaker(
		int pointValue,
		bool isVillain,
		Colour colour,
		int power,
		string name,
		string text);

	~TroubleMaker();

	void printStats();
	static void formatPrompt();
	static bool validateInput(vector<string> input);
	void buildCard(vector<string> formattedInput);
};
#endif // _TM_