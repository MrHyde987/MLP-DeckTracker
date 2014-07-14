
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
	for (int i = 0; i < TMSet->size(); ++i) {
		delete (*TMSet)[i];
	}
	delete TMSet;

	for (int i = 0; i < MCSet->size(); ++i) {
		delete (*MCSet)[i];
	}
	delete MCSet;

	for (int i = 0; i < friendSet->size(); ++i) {
		delete (*friendSet)[i];
	}
	delete friendSet;

	for (int i = 0; i < resourceSet->size(); ++i) {
		delete (*resourceSet)[i];
	}
	delete resourceSet;

	for (int i = 0; i < eventSet->size(); ++i) {
		delete (*eventSet)[i];
	}
	delete eventSet;

	for (int i = 0; i < problemSet->size(); ++i) {
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

	for (int i = 0; i < toQuery->size() && !isMember; ++i) {
		isMember = *((*toQuery)[i]) == (queryItem);
		if (isMember)
			memberFound = (*toQuery)[i];
	}

	return memberFound;
}