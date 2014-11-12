
#include "Main.h"

// The mode will be used to govern a lot of operations concerning
// the card set, most importantly allowing us to optimize queries by using
// segmented sets.
Mode mode = MODE_NOT_SET;
// Note that mode is global here and will be externed by several of the other
// compilation units.

SigMap rarityMap;
SigMap colourMap;
SigMap speciesMap;
SigMap locationMap;

void testAddCards(CardSet& cardWorkingSet) {

    string cardInput;
    bool cardInputSuccess = false;

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

void populateGlobalSignatureMaps() {

    rarityMap.insert(sigMapPair(RARITY_SIG_COMMON, "Common"));
    rarityMap.insert(sigMapPair(RARITY_SIG_UNCOMMON, "Uncommon"));
    rarityMap.insert(sigMapPair(RARITY_SIG_RARE, "Rare"));
    rarityMap.insert(sigMapPair(RARITY_SIG_ULTRA_RARE, "Ultra Rare"));
    rarityMap.insert(sigMapPair(RARITY_SIG_FIXED, "Fixed"));
    rarityMap.insert(sigMapPair(RARITY_SIG_PROMOTIONAL, "Promotional"));

    colourMap.insert(sigMapPair(COLOUR_SIG_PURPLE, "Purple"));
    colourMap.insert(sigMapPair(COLOUR_SIG_BLUE, "Blue"));
    colourMap.insert(sigMapPair(COLOUR_SIG_WHITE, "White"));
    colourMap.insert(sigMapPair(COLOUR_SIG_YELLOW, "Yellow"));
    colourMap.insert(sigMapPair(COLOUR_SIG_PINK, "Pink"));
    colourMap.insert(sigMapPair(COLOUR_SIG_ORANGE, "Orange"));
    colourMap.insert(sigMapPair(COLOUR_SIG_NONE, "None"));
    colourMap.insert(sigMapPair(COLOUR_SIG_ANY, "Any other colour"));

    speciesMap.insert(sigMapPair(SPECIES_SIG_UNICORN, "Unicorn"));
    speciesMap.insert(sigMapPair(SPECIES_SIG_PEGASUS, "Pegasus"));
    speciesMap.insert(sigMapPair(SPECIES_SIG_EARTH_PONY, "Earth Pony"));
    speciesMap.insert(sigMapPair(SPECIES_SIG_ALICORN, "Alicorn"));
    speciesMap.insert(sigMapPair(SPECIES_SIG_ZEBRA, "Zebra"));
    speciesMap.insert(sigMapPair(SPECIES_SIG_BUFFALO, "Buffalo"));
    speciesMap.insert(sigMapPair(SPECIES_SIG_CRITTER, "Critter"));
    speciesMap.insert(sigMapPair(SPECIES_SIG_DRAGON, "Dragon"));

    locationMap.insert(sigMapPair(LOCATION_SIG_HOME, "Played at Home"));
    locationMap.insert(sigMapPair(LOCATION_SIG_FRIEND, "Played on a Friend"));
    locationMap.insert(sigMapPair(LOCATION_SIG_OPPOSING_FRIEND, "Played on an opponent's Friend"));
    locationMap.insert(sigMapPair(LOCATION_SIG_TROUBLEMAKER, "Played on a Troublemaker"));
    locationMap.insert(sigMapPair(LOCATION_SIG_PROBLEM, "Played on a Problem"));
    locationMap.insert(sigMapPair(LOCATION_SIG_MANE_CHARACTER, "Played on a Mane Character"));
    locationMap.insert(sigMapPair(LOCATION_SIG_OPP_MC, "Played on opponent's Mane Character"));
}

int main() {

    // TODO: Plenty of stuff here. We'll want some actual initialization to take place here in
    //       main. On start:
    //       1. Check for the presence of a .cards manifest, and load it if possible.
    //       2. Present the user with the main menu, from which they can query the CardSet or add cards
    //          to it.
    //       3. Take them to the proper section of the program based on their selection, then exit when
    //          necessary.

    std::cout << "MLP DeckTracker version 0.5.5" << std::endl;
    std::cout << "Written by Carl Hyde" << std::endl << std::endl;
    
    populateGlobalSignatureMaps();
    CardSet cardWorkingSet = CardSet();

    testAddCards(cardWorkingSet);

    ManifestInterface cardManifest = ManifestInterface();
    cardManifest.writeManifestFile("Manifest.CARDS", cardWorkingSet);

    std::cout << "TEST COMPLETED SUCCESSFULLY" << std::endl;
}