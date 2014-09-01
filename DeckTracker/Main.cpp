
#include "Main.h"

// The mode will be used to govern a lot of operations concerning
// the card set, most importantly allowing us to optimize queries by using
// segmented sets.
Mode mode = MODE_NOT_SET;
// Note that mode is global here and will be externed by several of the other
// compilation units.

void testAddCards() {

	string cardInput;
	bool cardInputSuccess = false;

	CardSet cardWorkingSet;
	Card* newCard = NULL;
	vector<string> cardArgs;

	std::cout << "Let's add some cards" << endl;

	std::cout << "First, specify the type of card that you are adding: (Choose one) " << endl;
	std::cout << "Trouble Maker\nMane Character\nFriend\nResource\nEvent\nProblem\n\"Quit\" to quit"<< endl;

	getline(cin, cardInput);
	while (cardInput.compare("Quit") != 0) {

		if (cardInput.compare("Trouble Maker") == 0) {
			std::cout << "In entry mode: Trouble Maker" << endl;
			mode = MODE_TM;
			newCard = new TroubleMaker();
		}
		else if (cardInput.compare("Mane Character") == 0) {
			std::cout << "In entry mode: Mane Character" << endl;
			mode = MODE_MC;
			newCard = new ManeCharacter();
		}
		else if (cardInput.compare("Friend") == 0) {
			std::cout << "In entry mode: Friend" << endl;
			mode = MODE_FRIEND;
			newCard = new Friend();
		}
		else if (cardInput.compare("Resource") == 0) {
			std::cout << "In entry mode: Resource" << endl;
			mode = MODE_RESOURCE;
			newCard = new Resource();
		}
		else if (cardInput.compare("Event") == 0) {
			std::cout << "In entry mode: Event" << endl;
			mode = MODE_EVENT;
			newCard = new Event();
		}
		else if (cardInput.compare("Problem") == 0) {
			std::cout << "In entry mode: Problem" << endl;
			mode = MODE_PROBLEM;
			newCard = new Problem();
		}
		else
			std::cout << "ERROR: Not a valid mode." << endl;

		if (mode != MODE_NOT_SET) {
			// Every card starts with a name, so prompt for one.
			std::cout << "Entering new Card:" << endl;
			std::cout << "Name: ";
		}

		while (mode != MODE_NOT_SET) {

			getline(cin, cardInput);
			
			if (cardInput.compare("Quit") == 0) {
				mode = MODE_NOT_SET;
				// Free the pointer's memory if we stopped in the middle of entering a card.
				if (newCard)
					delete newCard;
				std::cout << "Exiting card input." << endl;
				std::cout << "Choose a new entrance mode" << endl;
				std::cout << "Trouble Maker\nMane Character\nFriend\nResource\nEvent\nProblem\n\"Quit\" to quit" << endl;
			}
			else {
				if (cardInput.compare("end") == 0 || cardInput.compare("End") == 0)
					cardInputSuccess = true;
				else
					newCard->addFields(cardInput);
			}

			// Hooray for polymorphism! ^^
			if (cardInputSuccess) {
				if (newCard->isCardComplete()) {
					// The Working set owns the pointer now.
					cardWorkingSet.insert(newCard);
					std::cout << "Card added successfully!\n" << endl;
				}
				else {
					delete newCard;
					std::cout << "Card input halted.\n" << endl;
				}
				// Set up for a new card to be inserted.
				switch (mode) {
					case(MODE_TM) :
						newCard = new TroubleMaker();
						break;
					case(MODE_MC) :
						newCard = new ManeCharacter();
						break;
					case(MODE_FRIEND) :
						newCard = new Friend();
						break;
					case(MODE_RESOURCE) :
						newCard = new Resource();
						break;
					case(MODE_EVENT) :
						newCard = new Event();
						break;
					case(MODE_PROBLEM) :
						newCard = new Problem();
						break;
				}
				cardInputSuccess = false;
				std::cout << "New Card:" << endl;
				std::cout << "Name:";
			}
		}

		getline(cin, cardInput);
	}
	std::cout << "Quitting input" << endl;

	std::cout << "\nCards in working set:" << endl;
	cardWorkingSet.print();
}

int main() {

	std::cout << "MLP DeckTracker version 0.5.5" << std::endl;
	std::cout << "Written by Carl Hyde" << std::endl << std::endl;

	testAddCards();


	std::cout << "TEST COMPLETED SUCCESSFULLY" << std::endl;
}