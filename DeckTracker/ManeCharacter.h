
#include "PlayableCard.h"

class ManeCharacter : public PlayableCard {

private:
	std::string flipCondition;
	int flippedPower;

public:
	ManeCharacter(
		std::string flipCondition,
		int flippedPower,
		Colour colour,
		int power,
		std::string name,
		std::string specialText);

	~ManeCharacter();

	void printStats();
};