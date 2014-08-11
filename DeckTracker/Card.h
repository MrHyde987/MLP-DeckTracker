
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

	// This is a state variable used to track the progress of building a card
	// Every class will do this in a similar way, thus they all need this variable.
	int filledFields;

public:
	Card();
	Card(string name);
	Card(string name, vector<string> text);
	
	// Abstract Class
	virtual void printStats() = 0;
	// This method will likely replace the above...
	virtual bool addFields(string inputToAdd) = 0;
	virtual bool isCardComplete() = 0;
	
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
	void pushSpecialText(string textToAdd);
	const int accessFieldsAdded() const;
	void incrementAddedFields();

	static Colour stringToColour(string toConvert);
	static string colourToString(Colour toConvert);
};

#endif // ndef _CARD_