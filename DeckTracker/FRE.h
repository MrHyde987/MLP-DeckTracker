
// FRE --> Friends, Resources, and Events
#ifndef _FRE_
#define _FRE_
#include "PlayableCard.h"

class FRE : public PlayableCard {

private:
	int actionCost;
	int developmentCost;

public:

	FRE();
	FRE(string name);
	FRE(
		int actionCost,
		int developmentCost,
		Colour colour,
		int power,
		string name,
		Rarity rarity,
		vector<string> specialText);
	// Abstract class
	virtual ~FRE();

protected:
	int accessActionCost();
	int accessDevelopmentCost();

	void modifyActionCost(int newAC);
	void modifyDevelopmentCost(int newDC);
};
#endif // _FRE_