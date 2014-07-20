
#ifndef _CARD_
#define _CARD_
#include <string>
#include <vector>
#include <iostream>

using namespace std;

// TODO: Perhaps in Card we could define a protected method for converting
// colours to strings, to aid in the printing process?
typedef enum {
	COLOUR_INVALID,
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
	int frequency;
	string name;
	vector<string> specialText;

public:
	Card();
	Card(string name, vector<string> text);
	
	// Abstract Class
	virtual void printStats() = 0;
	virtual void buildCard(vector<string> formattedInput) = 0;
	
	virtual ~Card();

	void incrementFrequency();
	void decrementFrequency();

	// TODO: Add == comparator operator (compare the names to determine equality)
	bool operator==(Card* toCompare);

protected:
	string accessName();
	vector<string> accessSpecialText();
	void modifyName(string newName);
	void modifySpecialText(vector<string> newText);
	void printSpecialText();

	static Colour stringToColour(string toConvert);
	static string colourToString(Colour toConvert);
};

#endif // ndef _CARD_