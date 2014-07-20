
#ifndef _CARD_SET_
#define _CARD_SET_

#include "Main.h" // for the Mode enum
#include <vector>
#include <iostream>

class Card;
using namespace std;

// The purpose of the CardSet class is to provide an abstraction
// of the program's working set of cards as one big array, when in
// fact the cards are being stored in several vectors for the purpose
// of optimizing query time.
class CardSet {

private:
	vector<Card*>* TMSet;
	vector<Card*>* MCSet;
	vector<Card*>* friendSet;
	vector<Card*>* resourceSet;
	vector<Card*>* eventSet;
	vector<Card*>* problemSet;

	// TODO: Move this to some generic location so that others can use it.
	Card* isVectorMember(vector<Card*>* toQuery, Card* queryItem);
	Card* queryMembership(Card* toQuery);

public:
	CardSet();

	~CardSet();

	void insert(Card* toInsert);
	
	void print();
};

#endif // _CARD_SET_