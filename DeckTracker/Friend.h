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
	const static int NUM_FIELDS = 7;

	static Species stringToSpecies(string toSpecies);
	static string speciesToString(Species toString);
	static void printAcceptableSpecies();

public:
	Friend();
	Friend(string name);
	Friend(
		Species species,
		int actionCost,
		int developmentCost,
		Colour colour,
		int power,
		string name,
		Rarity rarity,
		vector<string> specialText);

	~Friend();

	void printStats();
	bool addFields(string inputToAdd);
	bool isCardComplete();
};
#endif _FRIEND_