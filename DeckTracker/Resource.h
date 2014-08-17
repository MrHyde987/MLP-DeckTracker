#ifndef _RESOURCE_
#define _RESOURCE_
#include "FRE.h"

typedef enum {

	LOCATION_INVALID,
	LOCATION_HOME,
	LOCATION_FRIEND,
	LOCATION_OPPOSING_FRIEND,
	LOCATION_TM,
	LOCATION_PROBLEM,
	LOCATION_MC,
	LOCATION_OPPOSING_MC

} Location;

class Resource : public FRE {

private:
	Location location;
	
	const static int NUM_FIELDS = 7;

	static Location stringToLocation(string toConvert);
	static string locationToString(Location toConvert);
	static void printAcceptableLocations();

public:
	Resource();
	Resource(string name);
	Resource(
		Location location,
		int actionCost,
		int developmentCost,
		Colour colour,
		int power,
		string name,
		Rarity rarity,
		vector<string> specialText);

	~Resource();

	void printStats();
	bool addFields(string inputToAdd);
	bool isCardComplete();
};
#endif // _RESOURCE_
