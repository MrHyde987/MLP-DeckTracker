
#include "PlayableCard.h"

class TroubleMaker : public PlayableCard {

private:
	int pointValue;
	bool isVillain;

public:

	TroubleMaker(
		int pointValue,
		bool isVillain,
		Colour colour,
		int power,
		std::string name,
		std::string text);

	~TroubleMaker();

	void printStats();
};