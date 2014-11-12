
#ifndef _CARD_SET_
#define _CARD_SET_

#include "DeckTracker.h"

#include <vector>
#include <fstream>

#include "TroubleMaker.h"
#include "ManeCharacter.h"
#include "Friend.h"
#include "Resource.h"
#include "Event.h"
#include "Problem.h"

typedef std::_Vector_iterator<std::_Vector_val<std::_Simple_types<TroubleMaker*>>>      TMIterator;
typedef std::_Vector_iterator<std::_Vector_val<std::_Simple_types<ManeCharacter*>>>     MCIterator;
typedef std::_Vector_iterator<std::_Vector_val<std::_Simple_types<Friend*>>>        FriendIterator;
typedef std::_Vector_iterator<std::_Vector_val<std::_Simple_types<Resource*>>>    ResourceIterator;
typedef std::_Vector_iterator<std::_Vector_val<std::_Simple_types<Event*>>>          EventIterator;
typedef std::_Vector_iterator<std::_Vector_val<std::_Simple_types<Problem*>>>      ProblemIterator;

// The purpose of the CardSet class is to provide an abstraction
// of the program's working set of cards as one big array, when in
// fact the cards are being stored in several vectors for the purpose
// of optimizing query time.
class CardSet {

private:
    vector<TroubleMaker*>* TMSet;
    vector<ManeCharacter*>* MCSet;
    vector<Friend*>* friendSet;
    vector<Resource*>* resourceSet;
    vector<Event*>* eventSet;
    vector<Problem*>* problemSet;

    // TODO: Move this to some generic location so that others can use it.
    template<typename T>
    Card* isVectorMember(vector<T*>* toQuery, T* queryItem);
    
    Card* queryMembership(Card* toQuery);

public:

    CardSet();

    ~CardSet();

    void insert(Card* toInsert);
    
    int getNumUniqueCards();
    int getNumUniqueTMs();
    int getNumUniqueMCs();
    int getNumUniqueFriends();
    int getNumUniqueResources();
    int getNumUniqueEvents();
    int getNumUniqueProblems();

    TMIterator getTMIteratorBegin();
    bool checkTMIteratorEnd(TMIterator& tMIt);

    MCIterator getMCIteratorBegin();
    bool checkMCIteratorEnd(MCIterator& mCIt);

    FriendIterator getFriendIteratorBegin();
    bool checkFriendIteratorEnd(FriendIterator& friendIt);

    ResourceIterator getResourceIteratorBegin();
    bool checkResourceIteratorEnd(ResourceIterator& resourceIt);

    EventIterator getEventIteratorBegin();
    bool checkEventIteratorEnd(EventIterator& eventIt);

    ProblemIterator getProblemIteratorBegin();
    bool checkProblemIteratorEnd(ProblemIterator& problemIt);

    void print();

    void populate(vector<Card*> cardsFromFile);
};

#endif // _CARD_SET_