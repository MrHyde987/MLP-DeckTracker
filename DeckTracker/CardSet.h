
#ifndef _CARD_SET_
#define _CARD_SET_

#include "Main.h" // for the Mode enum
#include <vector>
#include <iostream>
#include <fstream>

class Card;
using namespace std;

// The purpose of the CardSet class is to provide an abstraction
// of the program's working set of cards as one big array, when in
// fact the cards are being stored in several vectors for the purpose
// of optimizing query time.
class CardSet {

#define FILE_OUT    std::fstream::out
#define FILE_IN     std::fstream::in
#define FILE_BIN    std::fstream::binary
#define FILE_ATE    std::fstream::ate
#define FILE_APPEND std::fstream::app
#define FILE_TRUNC  std::fstream::trunc

private:
	vector<TroubleMaker*>* TMSet;
	vector<ManeCharacter*>* MCSet;
	vector<Friend*>* friendSet;
	vector<Resource*>* resourceSet;
	vector<Event*>* eventSet;
	vector<Problem*>* problemSet;

    fstream cardsManifest;

	// TODO: Move this to some generic location so that others can use it.
	template<typename T>
    Card* isVectorMember(vector<T*>* toQuery, T* queryItem);
	
    Card* queryMembership(Card* toQuery);

public:
	CardSet();

	~CardSet();

	void insert(Card* toInsert);
	
	void print();

    void populate(vector<Card*> cardsFromFile);

    void saveToFile();
    bool loadFromFile();
};

#endif // _CARD_SET_