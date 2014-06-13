
#include "FRE.h"

typedef enum {

	LOCATION_HOME,
	LOCATION_FRIEND,
	LOCATION_OPPOSING_FRIEND

} Location;

class Resource : public FRE {

private:
	Location location;

public:
	Resource(
		Location location,
		int actionCost,
		int developmentCost,
		Colour colour,
		int power,
		std::string name,
		std::string specialText);

	~Resource();

	void printStats();
};
