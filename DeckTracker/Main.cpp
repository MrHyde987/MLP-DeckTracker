
// TODO: Remember to header guard!
#include "Friend.h"
#include <iostream>
#include <vector>

void testPrinting( int numTrials ) {

	std::vector<Friend*> testSet;

	for (int i = 0; i < numTrials; ++i) {

		testSet.push_back(new Friend(SPECIES_ALICORN, "Royalty", i, 2, COLOUR_YELLOW, 100*i, "Princess Celestia", "Special Text"));
	}

	for (int i = 0; i < numTrials; ++i)
		testSet[i]->printStats();

	for (int i = 0; i < numTrials; ++i)
		delete(testSet[i]);
}

int main() {

	std::cout << "MLP DeckTracker version 0.1.0" << std::endl;
	std::cout << "Written by Carl Hyde" << std::endl << std::endl;

	testPrinting(5);

	std::cout << "TEST COMPLETED SUCCESSFULLY" << std::endl;
}