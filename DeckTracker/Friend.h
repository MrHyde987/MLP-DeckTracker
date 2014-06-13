
#include "FRE.h"

typedef enum {

	SPECIES_UNICORN,
	SPECIES_PEGASUS,
	SPECIES_EP,
	SPECIES_ALICORN,
	SPECIES_ZEBRA,
	SPECIES_CRITTER

} Species;

class Friend : public FRE {

private:
	Species species;

	// TODO: String or collection of strings? For the moment, keep a string
	std::string typeModifiers;

public:
	Friend(
		Species species,
		std::string typeModifiers,
		int actionCost,
		int developmentCost,
		Colour colour,
		int power,
		std::string name,
		std::string specialText);

	~Friend();

	void printStats();
};