
#include <string>

using namespace std;

// TODO: Perhaps in Card we could define a protected method for converting
// colours to strings, to aid in the printing process?
typedef enum {
	COLOUR_NONE,
	COLOUR_PURPLE,
	COLOUR_WHITE,
	COLOUR_YELLOW,
	COLOUR_ORANGE,
	COLOUR_BLUE,
	COLOUR_PINK
} Colour;

class Card {

private:
	std::string name;
	std::string specialText;

public:
	Card(std::string name, std::string text);
	
	// Abstract Class
	virtual void printStats() = 0;
	
	virtual ~Card();

protected:
	std::string accessName();
	std::string accessSpecialText();
};