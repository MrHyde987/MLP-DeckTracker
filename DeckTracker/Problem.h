#ifndef _PROBLEM_
#define _PROBLEM_

#include "Card.h"

#include <iostream>

class Problem : public Card {

private:
	int pointBonus;
	int neutralConfrontCost;
	Colour primaryColour;
	Colour secondaryColour;
	int primaryColourConfrontCost;
	int secondaryColourConfrontCost;
	bool isStarting;

	const static int NUM_PROPERTIES = 9;

public:
	Problem();
	Problem(
		int pointBonus,
		int neutralConfrontCost,
		Colour primaryColour,
		Colour secondaryColour,
		int primaryColourConfrontCost,
		int secondaryColourConfrontCost,
		bool isStarting,
		string name,
		vector<string> specialText);

	~Problem();

	void printStats();
	static void formatPrompt();
	static bool validateInput(vector<string> input);
	void buildCard(vector<string> formattedInput);
};
#endif // _PROBLEM_