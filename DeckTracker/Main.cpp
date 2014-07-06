
#include "TroubleMaker.h"
#include "ManeCharacter.h"
#include "Friend.h"
#include "Resource.h"
#include "Event.h"
#include "Problem.h"

#include <iostream>
#include <sstream>
#include <vector>
#include <string>

#include "boost/tokenizer.hpp"

using namespace std;

typedef enum {

	MODE_NOT_SET,
	MODE_TM,
	MODE_MC,
	MODE_FRIEND,
	MODE_RESOURCE,
	MODE_EVENT,
	MODE_PROBLEM

} Mode;

vector<string> &split(string &s, char delim, vector<string> &elems) {
	stringstream ss(s);
	string item;
	while (getline(ss, item, delim)) {
		if (!item.empty())
			elems.push_back(item);
	}
	return elems;
}

void testInput() {

	std::string inText;

	std::getline(std::cin, inText);

	std::cout << inText;
}

void testAddCards() {

	string cardInput;
	Mode mode = MODE_NOT_SET;
	bool newModeSelected = false;
	bool cardInputSuccess = false;

	vector<Card*> cardWorkingSet;
	vector<string> cardArgs;

	cout << "Let's add some cards" << endl;

	cout << "First, specify the type of card that you are adding: (Choose one) " << endl;
	cout << "Trouble Maker" << endl << "Mane Character" << endl << "Friend" << endl
		<< "Resource" << endl << "Event" << endl << "Problem" << endl << "\"Quit\" to quit"<< endl;

	getline(cin, cardInput);
	while (cardInput.compare("Quit") != 0) {

		newModeSelected = false;

		// At any time, entering a new mode switches, so these checks are
		// always run.
		if (cardInput.compare("Trouble Maker") == 0) {
			cout << "In entry mode: Trouble Maker" << endl;
			mode = MODE_TM;
			TroubleMaker::formatPrompt();
			newModeSelected = true;
		}
		else if (cardInput.compare("Mane Character") == 0) {
			cout << "In entry mode: Mane Character" << endl;
			mode = MODE_MC;
			ManeCharacter::formatPrompt();
			newModeSelected = true;
		}
		else if (cardInput.compare("Friend") == 0) {
			cout << "In entry mode: Friend" << endl;
			mode = MODE_FRIEND;
			Friend::formatPrompt();
			newModeSelected = true;
		}
		else if (cardInput.compare("Resource") == 0) {
			cout << "In entry mode: Resource" << endl;
			mode = MODE_RESOURCE;
			Resource::formatPrompt();
			newModeSelected = true;
		}
		else if (cardInput.compare("Event") == 0) {
			cout << "In entry mode: Event" << endl;
			mode = MODE_EVENT;
			Event::formatPrompt();
			newModeSelected = true;
		}
		else if (cardInput.compare("Problem") == 0) {
			cout << "In entry mode: Problem" << endl;
			mode = MODE_PROBLEM;
			Problem::formatPrompt();
			newModeSelected = true;
		}

		if (!newModeSelected) {
			// Start getting actual card input.
			// Presumably, cardInput holds proper card formatting, if it was not a mode.
			cardArgs.clear();
			cardArgs = split(cardInput, ',', cardArgs);

			// Hooray for polymorphism!
			switch (mode) {

				case(MODE_TM) :
					cardInputSuccess = TroubleMaker::validateInput(cardArgs);
					if (cardInputSuccess) {
						cardWorkingSet.push_back(new TroubleMaker);
					}
					break;
				case(MODE_MC) :
					cardInputSuccess = ManeCharacter::validateInput(cardArgs);
					if (cardInputSuccess) {
						cardWorkingSet.push_back(new ManeCharacter);
					}
					break;
				case(MODE_FRIEND) :
					cardInputSuccess = Friend::validateInput(cardArgs);
					if (cardInputSuccess) {
						cardWorkingSet.push_back(new Friend);
					}
					break;
				case(MODE_RESOURCE) :
					cardInputSuccess = Resource::validateInput(cardArgs);
					if (cardInputSuccess) {
						cardWorkingSet.push_back(new Resource);
					}
					break;
				case(MODE_EVENT) :
					cardInputSuccess = Event::validateInput(cardArgs);
					if (cardInputSuccess) {
						cardWorkingSet.push_back(new Event);
					}
					break;
				case(MODE_PROBLEM) :
					cardInputSuccess = Problem::validateInput(cardArgs);
					if (cardInputSuccess) {
						cardWorkingSet.push_back(new Problem);
					}
					break;
			}

			if (cardInputSuccess) {
				cout << "Card added successfully!" << endl;
				cardWorkingSet[cardWorkingSet.size() - 1]->buildCard(cardArgs);
			}
		}

		getline(cin, cardInput);
	}
	cout << "Quitting input" << endl;
}

int main() {

	std::cout << "MLP DeckTracker version 0.2.0" << std::endl;
	std::cout << "Written by Carl Hyde" << std::endl << std::endl;

	testAddCards();

	std::cout << "TEST COMPLETED SUCCESSFULLY" << std::endl;
}