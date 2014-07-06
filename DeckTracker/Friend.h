#ifndef _FRIEND_
#define _FRIEND_
#include "FRE.h"

typedef enum {
	
	SPECIES_INVALID,
	SPECIES_UNICORN,
	SPECIES_PEGASUS,
	SPECIES_EP,
	SPECIES_ALICORN,
	SPECIES_ZEBRA,
	SPECIES_CRITTER,
	SPECIES_DRAGON,
	SPECIES_BUFFALO

} Species;

class Friend : public FRE {

private:
	Species species;
	const static int NUM_PROPERTIES = 8;

	// TODO: String or collection of strings? For the moment, keep a string
	string typeModifiers;

	static Species intToSpecies(int toSpecies);

public:
	Friend();
	Friend(
		Species species,
		std::string typeModifiers,
		int actionCost,
		int developmentCost,
		Colour colour,
		int power,
		string name,
		string specialText);

	~Friend();

	void printStats();
	static void formatPrompt();
	static bool validateInput(vector<string> input);
	void buildCard(vector<string> formattedInput);
};
#endif _FRIEND_