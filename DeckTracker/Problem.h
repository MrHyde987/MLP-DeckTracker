
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

public:
	Problem(
		int pointBonus,
		int neutralConfrontCost,
		Colour primaryColour,
		Colour secondaryColour,
		int primaryColourConfrontCost,
		int secondaryColourConfrontCost,
		bool isStarting,
		std::string name,
		std::string specialText);

	~Problem();

	void printStats();
};