#ifndef _PLAYABLE_CARD_
#define _PLAYABLE_CARD_
#include "Card.h"

class PlayableCard : public Card {

private:
	Colour colour;
	int power;

public:

	PlayableCard();

	PlayableCard(string name);

	PlayableCard(Colour colour, int power, string name, Rarity rarity, vector<string> text);
	
	// Abstract Class
	virtual ~PlayableCard();

protected:
	Colour accessColour();
	int accessPower();

	void modifyColour(Colour newColour);
	void modifyPower(int newPower);
};
#endif // _PLAYABLE_CARD_