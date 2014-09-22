
#include "CardSet.h"

CardSet::CardSet() {

	TMSet = new vector<TroubleMaker*>();
	MCSet = new vector<ManeCharacter*>();
	friendSet = new vector<Friend*>();
	resourceSet = new vector<Resource*>();
	eventSet = new vector<Event*>();
	problemSet = new vector<Problem*>();

    cardsManifest = fstream();
}

CardSet::~CardSet() {

	iter_t i = 0;

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

void CardSet::populate(vector<Card*> cardsFromFile) {

    Card* currCard = NULL;

    for (iter_t i = 0; i < cardsFromFile.size(); ++i) {

        currCard = cardsFromFile[i];
        if (currCard != NULL)
            insert(currCard);
    }
}

void CardSet::insert(Card* toInsert) {

	Card* prospectiveMember = NULL;
	prospectiveMember = queryMembership(toInsert);

	if (prospectiveMember != NULL)
		prospectiveMember->incrementFrequency();
	else {

        if (dynamic_cast<TroubleMaker*>(toInsert))
            TMSet->push_back(dynamic_cast<TroubleMaker*>(toInsert));
        else if (dynamic_cast<ManeCharacter*>(toInsert))
            MCSet->push_back(dynamic_cast<ManeCharacter*>(toInsert));
        else if (dynamic_cast<Friend*>(toInsert))
            friendSet->push_back(dynamic_cast<Friend*>(toInsert));
        else if (dynamic_cast<Resource*>(toInsert))
            resourceSet->push_back(dynamic_cast<Resource*>(toInsert));
        else if (dynamic_cast<Event*>(toInsert))
            eventSet->push_back(dynamic_cast<Event*>(toInsert));
        else if (dynamic_cast<Problem*>(toInsert))
            problemSet->push_back(dynamic_cast<Problem*>(toInsert));
        else
            cout << "ERROR: Card inserted that does not conform to a valid type." << endl;
	}
}

void CardSet::print() {

	iter_t i = 0;
    cout << endl;
	
	if (TMSet->size() > 0) {
		std::cout << "Trouble Makers:\n-------------------------------------" << endl;
		for (; i < TMSet->size(); ++i) {
			TMSet->at(i)->printStats();
			std::cout << endl;
		}
		std::cout << endl;
	}
	if (MCSet->size() > 0) {
		std::cout << "Mane Characters:\n-------------------------------------" << endl;
		for (i = 0; i < MCSet->size(); ++i) {
			MCSet->at(i)->printStats();
			std::cout << endl;
		}
		std::cout << endl;
	}
	if (friendSet->size() > 0) {
		std::cout << "Friends:\n-------------------------------------" << endl;
		for (i = 0; i < friendSet->size(); ++i) {
			friendSet->at(i)->printStats();
			std::cout << endl;
		}
		std::cout << endl;
	}
	if (resourceSet->size() > 0) {
		std::cout << "Resources:\n-------------------------------------" << endl;
		for (i = 0; i < resourceSet->size(); ++i) {
			resourceSet->at(i)->printStats();
			std::cout << endl;
		}
		std::cout << endl;
	}
	if (eventSet->size() > 0) {
		std::cout << "Events:\n-------------------------------------" << endl;
		for (i = 0; i < eventSet->size(); ++i) {
			eventSet->at(i)->printStats();
			std::cout << endl;
		}
		std::cout << endl;
	}
	if (problemSet->size() > 0) {
		std::cout << "Problems:\n-------------------------------------" << endl;
		for (i = 0; i < problemSet->size(); ++i) {
			problemSet->at(i)->printStats();
			std::cout << endl;
		}
		std::cout << endl;
	}
}

void CardSet::saveToFile() {

    cardsManifest.open("Test_Manifest.cards", FILE_OUT | FILE_APPEND);

    if (cardsManifest.is_open()) {
        
        iter_t i = 0;

        for (; i < TMSet->size(); ++i) {
            // Call out to getManifestString for the Troublemakers etc.
        }

        for (i = 0; i < MCSet->size(); ++i) {

        }

        for (i = 0; i < friendSet->size(); ++i) {

        }

        for (i = 0; i < resourceSet->size(); ++i) {

        }

        for (i = 0; i < eventSet->size(); ++i) {

        }

        for (i = 0; i < problemSet->size(); ++i) {

        }
    }
    cardsManifest.close();
}

bool CardSet::loadFromFile() {
    return false;
}

///////////////////////////////////////////////////
// Private Helper Functions
///////////////////////////////////////////////////

Card* CardSet::queryMembership(Card* toQuery) {

	Card* memberFound = NULL;

    if (dynamic_cast<TroubleMaker*>(toQuery))
        memberFound = isVectorMember(TMSet, dynamic_cast<TroubleMaker*>(toQuery));
    else if (dynamic_cast<ManeCharacter*>(toQuery))
        memberFound = isVectorMember(MCSet, dynamic_cast<ManeCharacter*>(toQuery));
    else if (dynamic_cast<Friend*>(toQuery))
        memberFound = isVectorMember(friendSet, dynamic_cast<Friend*>(toQuery));
    else if (dynamic_cast<Resource*>(toQuery))
        memberFound = isVectorMember(resourceSet, dynamic_cast<Resource*>(toQuery));
    else if (dynamic_cast<Event*>(toQuery))
        memberFound = isVectorMember(eventSet, dynamic_cast<Event*>(toQuery));
    else if (dynamic_cast<Problem*>(toQuery))
        memberFound = isVectorMember(problemSet, dynamic_cast<Problem*>(toQuery));

	return memberFound;
}

template<typename T>
Card* CardSet::isVectorMember(vector<T*>* toQuery, T* queryItem) {

	bool isMember = false;
	Card* memberFound = NULL;

	for (iter_t i = 0; i < toQuery->size() && !isMember; ++i) {
		isMember = *((*toQuery)[i]) == (queryItem);
		if (isMember)
			memberFound = (*toQuery)[i];
	}

	return memberFound;
}