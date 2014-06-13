
#include "FRE.h"

class Event : public FRE {

public:

	Event(
		int actionCost,
		int developmentCost,
		Colour colour,
		int power,
		std::string name,
		std::string specialText);

	~Event();

	void printStats();
};