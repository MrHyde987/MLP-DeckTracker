
#include "CardSet.h"

CardSet::CardSet() {
	TMSet = new vector<Card*>();
	MCSet = new vector<Card*>();
	friendSet = new vector<Card*>();
	resourceSet = new vector<Card*>();
	eventSet = new vector<Card*>();
	problemSet = new vector<Card*>();
}

CardSet::~CardSet() {

	unsigned int i = 0;

	for (; i < TMSet->size(); ++i) {
		delete (*TMSet)[i];
	}
	delete TMSet;

	for (i = 0; i < MCSet->size(); ++i) {
		delete (*MCSet)[i];
	}
	delete MCSet;

	for (i = 0; i < friendSet->size(); ++i) {
		delete (*friendSet)[i];
	}
	delete friendSet;

	for (i = 0; i < resourceSet->size(); ++i) {
		delete (*resourceSet)[i];
	}
	delete resourceSet;

	for (i = 0; i < eventSet->size(); ++i) {
		delete (*eventSet)[i];
	}
	delete eventSet;

	for (i = 0; i < problemSet->size(); ++i) {
		delete (*problemSet)[i];
	}
	delete problemSet;
}

void CardSet::insert(Card* toInsert) {

	Card* prospectiveMember = NULL;
	prospectiveMember = queryMembership(toInsert);

	if (prospectiveMember != NULL)
		prospectiveMember->incrementFrequency();
	else {

        if (dynamic_cast<TroubleMaker*>(toInsert))
            TMSet->push_back(toInsert);
        else if (dynamic_cast<ManeCharacter*>(toInsert))
            MCSet->push_back(toInsert);
        else if (dynamic_cast<Friend*>(toInsert))
            friendSet->push_back(toInsert);
        else if (dynamic_cast<Resource*>(toInsert))
            resourceSet->push_back(toInsert);
        else if (dynamic_cast<Event*>(toInsert))
            eventSet->push_back(toInsert);
        else if (dynamic_cast<Problem*>(toInsert))
            problemSet->push_back(toInsert);
        else
            cout << "ERROR: Card inserted that does not conform to a valid type." << endl;
	}
}

void CardSet::print() {

	unsigned int i = 0;
    cout << endl;
	
	if (TMSet->size() > 0) {
		cout << "Trouble Makers:\n-------------------------------------" << endl;
		for (; i < TMSet->size(); ++i) {
			TMSet->at(i)->printStats();
			cout << endl;
		}
		cout << endl;
	}
	if (MCSet->size() > 0) {
		cout << "Mane Characters:\n-------------------------------------" << endl;
		for (i = 0; i < MCSet->size(); ++i) {
			MCSet->at(i)->printStats();
			cout << endl;
		}
		cout << endl;
	}
	if (friendSet->size() > 0) {
		cout << "Friends:\n-------------------------------------" << endl;
		for (i = 0; i < friendSet->size(); ++i) {
			friendSet->at(i)->printStats();
			cout << endl;
		}
		cout << endl;
	}
	if (resourceSet->size() > 0) {
		cout << "Resources:\n-------------------------------------" << endl;
		for (i = 0; i < resourceSet->size(); ++i) {
			resourceSet->at(i)->printStats();
			cout << endl;
		}
		cout << endl;
	}
	if (eventSet->size() > 0) {
		cout << "Events:\n-------------------------------------" << endl;
		for (i = 0; i < eventSet->size(); ++i) {
			eventSet->at(i)->printStats();
			cout << endl;
		}
		cout << endl;
	}
	if (problemSet->size() > 0) {
		cout << "Problems:\n-------------------------------------" << endl;
		for (i = 0; i < problemSet->size(); ++i) {
			problemSet->at(i)->printStats();
			cout << endl;
		}
		cout << endl;
	}
}

///////////////////////////////////////////////////
// Private Helper Functions
///////////////////////////////////////////////////

Card* CardSet::queryMembership(Card* toQuery) {

	Card* memberFound = NULL;

    if (dynamic_cast<TroubleMaker*>(toQuery))
        memberFound = isVectorMember(TMSet, toQuery);
    else if (dynamic_cast<ManeCharacter*>(toQuery))
        memberFound = isVectorMember(MCSet, toQuery);
    else if (dynamic_cast<Friend*>(toQuery))
        memberFound = isVectorMember(friendSet, toQuery);
    else if (dynamic_cast<Resource*>(toQuery))
        memberFound = isVectorMember(resourceSet, toQuery);
    else if (dynamic_cast<Event*>(toQuery))
        memberFound = isVectorMember(eventSet, toQuery);
    else if (dynamic_cast<Problem*>(toQuery))
        memberFound = isVectorMember(problemSet, toQuery);

	return memberFound;
}

Card* CardSet::isVectorMember(vector<Card*>* toQuery, Card* queryItem) {

	bool isMember = false;
	Card* memberFound = NULL;

	for (unsigned int i = 0; i < toQuery->size() && !isMember; ++i) {
		isMember = *((*toQuery)[i]) == (queryItem);
		if (isMember)
			memberFound = (*toQuery)[i];
	}

	return memberFound;
}