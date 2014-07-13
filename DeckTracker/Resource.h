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
	
	const static int NUM_PROPERTIES = 7;

	static Location intToLocation(int toConvert);

public:
	Resource();
	Resource(
		Location location,
		int actionCost,
		int developmentCost,
		Colour colour,
		int power,
		string name,
		vector<string> specialText);

	~Resource();

	void printStats();
	static void formatPrompt();
	static bool validateInput(vector<string> input);
	void buildCard(vector<string> formattedInput);
};
#endif // _RESOURCE_
