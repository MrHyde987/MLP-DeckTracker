
// FRE --> Friends, Resources, and Events

#include "PlayableCard.h"

class FRE : public PlayableCard {

private:
	int actionCost;
	int developmentCost;

public:

	FRE(
		int actionCost,
		int developmentCost,
		Colour colour,
		int power,
		std::string name,
		std::string specialText);
	// Abstract class
	virtual ~FRE();

protected:
	int accessActionCost();
	int accessDevelopmentCost();
};