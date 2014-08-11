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

	const static int NUM_FIELDS = 8;

public:
	Problem();
	Problem(string name);
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
	bool addFields(string inputToAdd);
	bool isCardComplete();
};
#endif // _PROBLEM_