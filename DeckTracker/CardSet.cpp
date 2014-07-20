
#include "CardSet.h"

extern Mode mode;

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
		switch (mode) {

			case(MODE_TM) :
				TMSet->push_back(toInsert);
				break;
			case(MODE_MC) :
				MCSet->push_back(toInsert);
				break;
			case(MODE_FRIEND) :
				friendSet->push_back(toInsert);
				break;
			case(MODE_RESOURCE) :
				resourceSet->push_back(toInsert);
				break;
			case(MODE_EVENT) :
				eventSet->push_back(toInsert);
				break;
			case(MODE_PROBLEM) :
				problemSet->push_back(toInsert);
				break;
			default:
				break;
		}
	}
}

void CardSet::print() {

	unsigned int i = 0;
	
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
	switch (mode) {
		case(MODE_TM) :
			memberFound = isVectorMember(TMSet, toQuery);
			break;
		case(MODE_MC) :
			memberFound = isVectorMember(MCSet, toQuery);
			break;
		case(MODE_FRIEND) :
			memberFound = isVectorMember(friendSet, toQuery);
			break;
		case(MODE_RESOURCE) :
			memberFound = isVectorMember(resourceSet, toQuery);
			break;
		case(MODE_EVENT) :
			memberFound = isVectorMember(eventSet, toQuery);
			break;
		case(MODE_PROBLEM) :
			memberFound = isVectorMember(problemSet, toQuery);
			break;
		default:
			break;
	}

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