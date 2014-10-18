///////////////////////////////////////////////////
/// Project Documentation
/// Last edited: Oct. 12, 2014 by Carl Hyde
///////////////////////////////////////////////////

The DeckTracker project originally grew out of my own frustration in having to search through my
own pile of cards every time someone would come up to me looking for a trade. Granted, that was
before I started organizing my cards in any way, but even now that organization is piecemeal
and I often don't take the time to make sure that all of my rares are properly catalogued.
(As some people are well aware.)

So thus, this first cut of the program seeks to allow a user to answer a simple question:
"Do I have X card in my collection?" For now, this is all that we are shooting for, but there
are plenty of directions that the project can take once we get there, which shall be discussed
nearer to the end of the document.

As I have planned it out so far, a program that can accomplish this goal is composed of three
primary pieces:
	1. A mechanism for entering cards into storage.
	2. A way to store these card records long-term.
	3. A way to query this storage for details concerning the stored cards.
	
One could also make an argument that the underlying structure to tie together these pieces is a 
piece in and of itself, in which case we have four core components to work with.

At the moment, the card entering mechanism is in a usable state. I would perhaps hesitate to call
it finished (in fact, it's definitely not finished), but it can at least be used to enter some
incomplete records which could be used to test out the other components. For the past few sessions,
much of my own effort has gone towards #2 above, the file reading/writing layer. As of this edit,
that component is still untested, but most of the code has been written.

Remaining composition of the document:
	1. Equipment needed to work on the project
	2. Program Usage Instructions
	3. How cards are represented internally
	4. Outline of the file interface layer
	5. Discussion of future directions for the project.
	
	
========================================================================================
		Section 1 -- TOOLS USEFUL TO AN ENGINEER
========================================================================================
	
Thus far, I have done all of my work on the project in Visual Studio 2013 Express Edition.
Of course, any text editing application will do for C++ development, but I personally prefer
a properly featured development environment. If you are a student, you might want to look
into whether your school has a partnership with Microsoft's Dreamspark program, in which case
you are probably entitled to a truly tricked-out version of VS. Just make sure to get a 
2013 edition, so that we shall be building with the same version of the compiler.

Since the current development also involves a great deal of low-level file layer stuff, it
would also be useful to have a hex-editing application, so that you can examine the output 
files from the program, and also create your own test files. A sample manifest file that I
manually created, as well as a disassembly showing off its various fields, is included in the 
project.

The source code for the project is hosted on GitHub, for the moment at:
https://github.com/MrHyde987/MLP-DeckTracker

While I was writing this documentation I discovered that GitHub offers a way to document the
project online, as well as an issue-tracking feature. So in the future we will likely start
making use of these things.

Plans and progress on the project are also done using Trello, which is an excellent service.
You will need a Trello account to view the board for the project, so once you have one,
send me a message and I will be sure to add you.
	
========================================================================================
		Section 2 -- PROGRAM USAGE INSTRUCTIONS
========================================================================================

Upon start, there will be a small version declaration printed. (Any contributors to the project
will likely wish to add their own credit to this declaration, if they wish to be associated with
the project.)

Since the UI is still incomplete, the program immediately moves into the card insertion
mode. There are six modes for card insertion, corresponding to the six types of cards in
the game: Troublemaker, Mane Character, Friend, Resource, Event, and Problem. Entering any 
one of these modes will initiate the creation of a card of that type. While at this level,
entering Quit will exit the program.

Entering a card is a relatively simple process: each field is prompted individually, and expects
merely a reasonable value. Entering "Quit" at any point in the process will discard the card
being created, and exit back to the mode choosing menu.

Certain fields are special. 
	- The Type Modifiers field (present for Mane Characters,
	  Friends, Resources, and Events) expects a semicolon-delimited list of strings representing the 
	  spcecial modifiers assigned to that card (Royalty, Accessory, Showdown, etc.) 
	- The Special Text field (present and last for all cards) includes all text on the card not covered 
	  by the other fields (EXCEPT for Mane Characters, more on them below). Special Text is an
	  open-ended field, in that it will continue accepting strings until the string "end" is entered.
	  (Entering the "end" string at any other point in the creation process discards the card and starts
	  a new one.) Card keywords (Inspired, Random, etc.) are Special Text, and should be entered as a 
	  separate line in the Special Text field.
	- Mane Characters have many unique fields because they are the least uniform of all the various 
	  types of cards. For example, the uncommon Applejack from Canterlot Nights has text that would
	  be considered Special Text on its "Start" side, and is currently the only Mane to do so.
	  (The normal "Special Text" field for Manes only includes text on the "Boosted" side of the card.)
	  Execeptions to previously assumed rules like these have necessitated the need for a few extra
	  fields. Each of these fields accepts a SINGLE STRING.
			- Start Flip Condition - The text that explains how to flip the card from "Start" to "Boosted"
			- Boosted Flip Condition - The text that explains how to flip the card from "Boosted" to
			  "Start". Currently, only the Ultra-Rare Celestia and Luna from Canterlot Nights have this
			  field defined.
			- Start Special Text - Text on the "Start" side of the card that does NOT relate to flipping
			  the card to its "Boosted" side. As noted above, currently the Uncommon Applejck from
			  Canterlot Nights is the only card to have this field defined.
			  
Once a card is finished, there will be a message printed to assure the user that the card was properly entered
into the working set. Entry will immediately begin on a new card of the same type as the one last entered.


========================================================================================
		Section 3 -- INTERNAL REPRESENTATION OF CARDS
========================================================================================

Within the project directory there should be a class diagram file that depicts the hierarchy of classes used
to represent cards. Unfortunately, VS Express edition is unable to comprehend this file, and so it is likely
that a textual explanation is also in order.

First, a small note on typedef's. There are several types used throughout the code, and all of their typedef's
are to be found within the universal header DeckTracker.h. The important ones are:
	
	- typedef unsigned __int32 uint32_t
	- typedef unsigned __int16 uint16_t
	- typedef unsigned __int8  uint8_t
	
These three are relatively self-explanatory. They are here simply to remove the ambiguity concerning the size of 
the integer types used throughout the program. (ints are still used in a couple of places in the program. If you 
ever find a conflict between the type of a variable used in the program, and the type described here, this 
documentation shall prevail.)

	- typedef unsigned __int8  sig_t

This is of course a redundant definition. sig_t stands for signature type, and sig_t's are used throughout the code
to mark signatures and flags. For example, a card's "Rarity" field consists of a sig_t, which maps to a rarity through
the global rarityMap.

	- typedef __int64		   long_sig_t
	
Similar to the signature type above, long_sig_t is the long signature type, used for longer signature values.

	- typedef const unsigned __int8 recordSize_t
	
This one is entirely for the purposes of the file layer at the moment (so it should probably be moved there).
recordSize_t's are used to define the sizes of the various blocks that make up the manifest file.

	- typedef unsigned int  iter_t
	
This really is just my own annoyance at getting the signed/unsigned mismatch warning in all of the for-loops. Use 
iter_t's when defining loop variables (unless using an explicit iterator type, such as those defined by CardSet).

Classes used in representing cards:

Class Card
Parents: None
Children: PlayableCard, Problem
Member variables:
	frequency (uint16_t) -- The number of copies of a card currently owned.
	name (string) -- The card's full name (e.g. Rarity -- Nest Weaver)
	rarity (sig_t) -- The card's rarity designation.
	specialText (vector<string>) -- All of the modifying text for the card.
	filledFields (int) -- Internal variable used for determining how many of a card's fields have been filled by values.
	
Exposed methods:
	Various constructors
	void printStats() (virtual = 0) -- Used to print a card's info to the console.
	bool addFields(string) (virtual = 0) -- The method used to add a field to a card during the creaion process.
	bool isCardComplete() (virtual = 0) -- Also used during the creation process to check if a card is finished.
	bool operator==(Card*) -- Comparison operator (Cards are equal if their names match)
	void incrementFrequency() -- Adds 1 to the frequency, meaning another copy of the card is now owned.
	void decrementFrequency() -- Inverse of the above.
	string getTextAt(int) -- Retrieves the specialText at the specified index in the internal vector.
	
Protected methods:
	Accessors for name, rarity, and specialText
	bool modifyName(string) -- Attempts to assign a new string to name (return value signifies success/failure)
	bool modifyRarity(string) -- Attempts to assign a new value to rarity (return value as above)
	void modifySpecialText(vector<string>) -- Attempts to assign a new vector to specialText.
	void printSpecialText() -- Prints all Special Text to the console.
	void pushSpecialText(string) -- Pushes the string onto the back of the specialText vector.
	const int accessFieldsAdded() const -- Accessor for filledFields.
	void incrementAddedFields() -- Increments filledFields.
	const int accessFrequency() const -- Accessor for frequency.
	static sig_t stringToColour(string) -- Attempts to convert the string to a colour signature.
	static void printAcceptableColours() -- Prints all acceptable colours to the console.
	static sig_t stringToRarity(string) -- Attempts to convert the string to a rarity signature.
	static void printAcceptableRarities() -- Prints all acceptable rarities to the console.
	
	
Class Problem
Parents: Card
Children: None
Member Variables:
	pointBonus (uint8_t) -- The problem's point bonus.
	neutralConfrontCost (uint8_t) -- The power required for the opponent to confront the problem.
	primaryColour (sig_t) -- The left colour required by the card's owner to confront it.
	secondaryColour (sig_t) -- The right colour required by the card's owner to confront it.
	primaryColourConfrontCost (uint8_t) -- The power required in the primary colour to confront the problem.
	secondaryColourConfrontCost (uint8_t) -- The power required in the secondary colour to confront the problem.
	isStarting (bool) -- Defines whether the problem is a starting problem.
	NUM_FIELDS (const static int) -- The number of fields required to constitute a complete Problem.
	
Exposed methods:
	Constructors
	void printStats() -- Implements pure virtual from Card.
	bool addFields(string) -- Implements pure virtual from Card.
	bool isCardComplete() -- Implements pure virtual from Card.
	

Class PlayableCard
Parents: Card
Children: Troublemaker, ManeCharacter, FRE
Member Variables:
	colour (sig_t) -- Defines the colour of the card. Troublemakers have no colour, whilst Mane Characters and Friends have
					  colours defined by their power. Resources and Events could have a colour if they have a colour cost,
					  otherwise they have no colour.
	power (uint8_t) -- The number in the top-right of the card, used when the card is involved in a faceoff.
	typeModifiers (uint8_t) -- Special Modifiers to the type of the card, which appear as strings next to their usual type.
							   The internal representation is as single bits OR'ed into a byte.

Exposed methods:
	bool modifyTypeModifiers(string) (virtual = 0) -- Attempts to assign a new value to typeModifiers based on the string.
	void printTypeModifiers() (virtual = 0) -- Prints the type modifiers for a card to the console.
	
Protected Methods:
	Accessors for colour, power, and typeModifiers
	bool modifyColour(string) -- Attempts to assign a new value to colour based on the string.
	bool modifyPower(string) -- Attempts to assign a new value to power based on the string.
	void assignTypeModifier(uint8_t) -- Assigns a new value to typeModifers.
	static sig_t stringToSpecies(string) -- Attempts to convert the given string to a species signature.
	static void printAcceptableSpecies() -- Prints a list of acceptable species to the console.
	
	
Class TroubleMaker
Parents: PlayableCard
Member Variables:
	pointValue (uint8_t) -- The number of points awarded to the player that defeats the troublemaker.
	isVillain (bool) -- Defines whether the troublemaker is a villain.
	NUM_FIELDS (const static int) -- Serves same purpose as in Problem above. (This field is present in all instantiable classes 
									 descended from Card.
 
Exposed Methods:
	Constructors
	printStats() (void) -- Implements pure virtual from Card.
	addFields(string) (bool) -- Implements pure virtual from Card.
	isCardComplete() (bool) -- Implements pure virtual from Card.
	modifyTypeModifiers(string) (bool) -- Implements pure virtual from PlayableCard.
	printTypeModifiers() (void) -- Implements pure virtual from PlayableCard.
	

Class ManeCharacter
Parents: PlayableCard
Member Variables:
	startFlipCondition (string) -- The text that defines the condition for flipping the card from "Start" to "Boosted"
	boostedFlipCondition (string) -- The text that defines the condtions for flipping the card from "Boosted" to "Start"
	species (sig_t) -- A signature that defines the card's species.
	boostedPower (uint8_t) -- The power of the card on its "Boosted" side.
	startHomeLimit (uint8_t) -- The home limit of the card on its "Start" side.
	boostedHomeLimit (uint8_t) -- The home limit of the card on its "Boosted" side.
	startSpecialText (string) -- The text on the "Start" side of the card that doesn't define the condition to flip the card over.
	NUM_FIELDS (const static int) -- See Problem above.

Exposed Methods:
	The class API exactly matches TroubleMaker above, with the addtion of Accessors for startFlipCondition, boostedFlipCondition,
	and startSpecialText.
	

Class FRE
Parents: PlayableCard
Children: Friend, Resource, Event
Member Variables:
	actionCost (uint8_t) -- The number of actions required to play the card.
	colourCost (uint8_t) -- Also called "developmentCost" in some places. This is the amount of power in the card's colour that must
							be already in play for the card to enter the field.
	
Exposed Methods:
	Constructors
Protected Methods:
	Accessors for actionCost and colourCost
	modifyActionCost(string) (bool) -- Attempts to assign a new value to actionCost based on the given string.
	modifyColourCost(string) (bool) -- Attempts to assign a new value to colourCost based on the given string.
	
	
Class Friend
Parents: FRE
Member Variables:
	species (sig_t) -- A signature that defines the friend's species.
	NUM_FIELDS (const static int) -- See Problem above.
Exposed Methods:
	The exposed API again exactly matches that of Troublemaker above. Most of the instantiable classes have very similar APIs.
	
	
Class Resource
Parents: FRE
Member Variables:
	location (sig_t) -- A signature that defines where the resource is to be played.
	NUM_FIELDS (const static int) -- See Problem above.
Exposed Methods:
	The exposed API again exactly matches that of TroubleMaker above.
	

Class Event
Parents: FRE
Member Variables:
	NUM_FIELDS (const static int) -- See Problem above.
Exposed Methods:
	Once more, the exposed API exactly matches that of TroubleMaker.
	
	
========================================================================================
		Section 4 -- OUTLINE OF THE CARDS MANIFEST FORMAT
========================================================================================

A more detailed explanation of the format used in the .CARDS manifest file can be found in the file "CARDS Format Specification.txt"
in the DeckTracker folder.

In the program's current state, after card input has been halted, the current working set is saved out to a file.
The class responsible for all of the low-level byte-work is the ManifestInterface class. Notably, ManifestInterface has friend access
to all of the internal storage classes listed above, which makes the reading and writing of manifest files simple and pain-free.

Broadly speaking, a manifest file consists of a header block, followed by a set of Csrd Record blocks. The record blocks store the
fields of the cards that have fixed storage widths (i.e. everything except for the various text fields). The text fields instead
provide indices into a String Table, which is stored after the record blocks. The String Table consists of a String Table
Dictionary, followed by raw strings. The dictionary is merely a set of offsets and lengths; each String Table Entry holds an offset
(which defines where the relevant string starts relative to the start of the string table dictionary), and a length, which is just
the length of the stored string.

Though the functionality is not built in yet, the program will eventually load a CARDS manifest (should one exist) on startup.


========================================================================================
		Section 5 -- THOUGHTS ABOUT THE FUTURE
========================================================================================

Once we have a competent program for answering that first user question, a discussion will have to commence concerning where to take
the program from there. Major items that I had considered were:

	1. A proper Graphical interface. Text interaction is clunky and obtuse. And I've never done a proper GUI before, so it seems like a good 
	   thing to try. Plus, if we become familiar with a good graphics library, we could try more advanced graphical things later.
	2. Support for the concept of a "deck", which is to say, for example, rather than "I have two of this card", instead "I have two of 
	   this card, but they're both in decks, so I can't trade them." Once we have decks, we can start tracking statistics for decks, to
	   provide users with a way to track their performance over time.
	3. Deck Analytics. This builds off of number 2 above, and provides probably the best opportunity for some fancy algorithms. (And who
	   doesn't like fancy algorithms?) The problem of "Is this deck good?" is a very hard one to answer, but we could at least take a
	   reasonable crack at it. We could tackle the problem in small steps. I've given this one a bit of thought, and I can think of a couple
	   of graduated stages to put a deck through:
			Level 0
				A level 0 deck is one that contains any cards that can't possibly be played, or serve any value whatsoever.
				(Even if an Event can't be played, it might be discarded onto Luna in a faceoff, for example).
			Level 1
				A level 1 deck might be all playable, but doesn't have a mechanic for flipping over its Mane Character.
			And further levels depending on more complex metrics.
		
		Or, we could take an approach that evaluates a deck based on patterns of good synergies between cards (given positive points) and 
		negative points given for cards that don't contribute to the deck, can rarely be played efficiently, etc. There are many places
		that we could go with this kind of a problem.
	4. Deck visualizations. This is kind of an analytic too. The ability to visualize a deck can be quite useful for evaluating it. For
	   example, we could show which cards become available once the Mane flips over, or once certain cards enter play.
	   The ultimate dream for this sort of work would be the ability to simulate a couple of turns at the start of a game, to let the user
	   see how the deck will play out in common situations.
	5. The ability to pre-load starter decks. Card entry will be a slow process for first-time users, so it makes sense to pre-store manifests
	   for the starter decks, which will make it easier for new players to get started.
	6. Streamline card entry further by pre-storing relations for all cards in play. Then, inserting a card can be simply a matter of entering
	   its set and number within that set, and the program can take care of the rest.
	6. Building towards a commercial application. The only commercial application that I've been able to see for this software is as an 
	   aid to tournaments and livestreams of games. Deck-lists could be submitted in the CARDS format rather than on paper, and a 
	   commentator could use some of the visualizations above to better explore and show some of the combinations and strategies that exist
	   in a deck as the game is played. Naturally, this really is a pipe dream at the moment, but I've given some thought to it.