
#include "Card.h"

class PlayableCard : public Card {

private:
	Colour colour;
	int power;

public:

	PlayableCard(Colour colour, int power, std::string name, std::string text);
	
	// Abstract Class
	virtual ~PlayableCard();

protected:
	Colour accessColour();
	int accessPower();
};