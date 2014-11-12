
#ifndef _MANIFEST_INTERFACE_
#define _MANIFEST_INTERFACE_

#include "DeckTracker.h"

#include "CardSet.h"

#include <fstream>

//////////////////////////////////////////////////////////////////////////////////////////
//          SIGNATURE AND FLAG VALUES
//////////////////////////////////////////////////////////////////////////////////////////

// Many of these signatures were moved to DeckTracker.h because we decided to use them globally.
// Whether the rest of them stay or not is yet to be decided.

// End of record signature value
static long_sig_t END_OF_RECORD =   0x43454C4553544941;

// Boolean signature Values
static sig_t BOOL_SIG_FALSE =               0x00;
static sig_t BOOL_SIG_TRUE =                0xFF;

// Card Type Signature Values
static sig_t TYPE_SIG_TM =                  0x01;
static sig_t TYPE_SIG_MC =                  0x02;
static sig_t TYPE_SIG_FR =                  0x03;
static sig_t TYPE_SIG_RE =                  0x04;
static sig_t TYPE_SIG_EV =                  0x05;
static sig_t TYPE_SIG_PR =                  0x06;

// Special Signature values
static long_sig_t HEADER_SIG =      0x4349734250;

//////////////////////////////////////////////////////////////////////////////////////////
//          SIZES
//////////////////////////////////////////////////////////////////////////////////////////

static recordSize_t HEADER_SIZE =                41;
static recordSize_t SIGNATURE_SIZE =              5;
static recordSize_t EOR_SIGNATURE_SIZE =          8;
static recordSize_t TM_BLOCK_SIZE =              24;
static recordSize_t MC_BLOCK_SIZE =              40;
static recordSize_t FRIEND_BLOCK_SIZE =          27;
static recordSize_t RESOURCE_BLOCK_SIZE =        27;
static recordSize_t EVENT_BLOCK_SIZE =           26;
static recordSize_t PROBLEM_BLOCK_SIZE =         27;

static recordSize_t STRING_TABLE_ENTRY_SIZE =     6;

// The purpose of the StringTable class is to act as the in-memory
// representation of the manifest's string table. As the file is being written, the locations
// and lengths of the strings will be written into this class, so that once it is time to write
// the string table, that can be easily done.
class StringTable {

public:

    StringTable();
    ~StringTable();

    int add(string newString);
    string getStringAt(int index);
    int getOffsetAt(int index);
    iter_t getNumStrings();

    void offsetAllMembers(const int extraOffset);

private:
    vector<string>  strings;
    vector<int>     offsets;
};

class ManifestInterface {

public:
    ManifestInterface();

    void readManifestFile(std::string fileName, CardSet &newSet);
    void writeManifestFile(std::string fileName, CardSet &currSet);

private:
    
    // Length of the longest possible entry in the string table.
    const static int BUFFER_SIZE = 65535;

    fstream manifestFile;
    char buffer[BUFFER_SIZE];
    void* currBufferPos;

    void copyCommonBlock(StringTable stringTable, sig_t cardType, string name, sig_t rarity, sig_t isFoil, int frequency, vector<string> specialText);
    void copyValueToBuffer(void* value, size_t numBytes);
    void clearBuffer();
};

#endif // _MANIFEST_INTERFACE