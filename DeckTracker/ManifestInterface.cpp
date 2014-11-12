#include "ManifestInterface.h"

ManifestInterface::ManifestInterface() {
    
    currBufferPos = buffer;
}

void ManifestInterface::readManifestFile(std::string fileName, CardSet &newSet) {

    manifestFile.open(fileName, std::ifstream::binary | std::ifstream::in);

    // So, rather than just doing a big loop, we have to do this sequentially since we are 
    // parsing a specific file format.
}

void ManifestInterface::writeManifestFile(std::string fileName, CardSet &currSet) {

    manifestFile.open(fileName, std::ifstream::binary | std::ifstream::out);

    StringTable stringTable = StringTable();

    // Beginning signature.
    copyValueToBuffer("CIsBP", SIGNATURE_SIZE);

    uint32_t numUniqueCards = currSet.getNumUniqueCards();
    uint32_t numUniqueTMs = currSet.getNumUniqueTMs();
    uint32_t numUniqueMCs = currSet.getNumUniqueMCs();
    uint32_t numUniqueFriends = currSet.getNumUniqueFriends();
    uint32_t numUniqueResources = currSet.getNumUniqueResources();
    uint32_t numUniqueEvents = currSet.getNumUniqueEvents();
    uint32_t numUniqueProblems = currSet.getNumUniqueProblems();

    // The string table will come immediately after all of the records.
    uint32_t stringTableOffset = 
        HEADER_SIZE +
        numUniqueTMs * TM_BLOCK_SIZE +
        numUniqueMCs * MC_BLOCK_SIZE +
        numUniqueFriends * FRIEND_BLOCK_SIZE +
        numUniqueResources * RESOURCE_BLOCK_SIZE +
        numUniqueEvents * EVENT_BLOCK_SIZE +
        numUniqueProblems * PROBLEM_BLOCK_SIZE;

    // TODO: Working with things on a bit-level like this highlights a lot of problems to do with
    //       sizes in here. I don't think that we can assume the sizes of ints anymore, and that means that
    //       we need project-wide typedef's to ensure that our sizes are all the same.
    copyValueToBuffer(&numUniqueCards, sizeof(uint32_t));
    copyValueToBuffer("resv", 4);
    copyValueToBuffer(&numUniqueTMs, sizeof(uint32_t));
    copyValueToBuffer(&numUniqueMCs, sizeof(uint32_t));
    copyValueToBuffer(&numUniqueFriends, sizeof(uint32_t));
    copyValueToBuffer(&numUniqueResources, sizeof(uint32_t));
    copyValueToBuffer(&numUniqueEvents, sizeof(uint32_t));
    copyValueToBuffer(&numUniqueProblems, sizeof(uint32_t));
    copyValueToBuffer(&stringTableOffset, sizeof(uint32_t));

    manifestFile.write(buffer, HEADER_SIZE);
    clearBuffer();

    for (TMIterator troubleIter = currSet.getTMIteratorBegin(); !currSet.checkTMIteratorEnd(troubleIter); ++troubleIter) {
        
        copyCommonBlock(
            stringTable,
            TYPE_SIG_TM,
            (*troubleIter)->name,
            (*troubleIter)->rarity,
            BOOL_SIG_FALSE, // TODO: Proper foil system not yet implemented
            (*troubleIter)->frequency,
            (*troubleIter)->specialText);

        copyValueToBuffer(&(*troubleIter)->power, sizeof(uint8_t));
        copyValueToBuffer(&((*troubleIter)->isVillain ? BOOL_SIG_TRUE : BOOL_SIG_FALSE), sizeof(sig_t));
        copyValueToBuffer(&(*troubleIter)->pointValue, sizeof(uint8_t));
        copyValueToBuffer(&END_OF_RECORD, sizeof(long_sig_t));

        manifestFile.write(buffer, TM_BLOCK_SIZE);
        clearBuffer();
    }
    for (MCIterator maneIter = currSet.getMCIteratorBegin(); !currSet.checkMCIteratorEnd(maneIter); ++maneIter) {

        copyCommonBlock(
            stringTable,
            TYPE_SIG_MC,
            (*maneIter)->name,
            (*maneIter)->rarity,
            BOOL_SIG_FALSE, // TODO: Proper foil systems
            (*maneIter)->frequency,
            (*maneIter)->specialText);

        copyValueToBuffer(&(*maneIter)->colour, sizeof(sig_t));
        copyValueToBuffer(&(*maneIter)->power, sizeof(uint8_t));
        copyValueToBuffer(&(*maneIter)->typeModifiers, sizeof(uint8_t));

        int stringTableIndex = stringTable.add((*maneIter)->startFlipCondition);
        copyValueToBuffer(&stringTableIndex, sizeof(int));
        stringTableIndex = stringTable.add((*maneIter)->boostedFlipCondition);
        copyValueToBuffer(&stringTableIndex, sizeof(int));

        copyValueToBuffer(&(*maneIter)->species, sizeof(sig_t));
        copyValueToBuffer(&(*maneIter)->boostedPower, sizeof(uint8_t));
        copyValueToBuffer(&(*maneIter)->startHomeLimit, sizeof(uint8_t));
        copyValueToBuffer(&(*maneIter)->boostedHomeLimit, sizeof(uint8_t));

        stringTableIndex = stringTable.add((*maneIter)->startSpecialText);
        copyValueToBuffer(&stringTableIndex, sizeof(int));

        copyValueToBuffer(&END_OF_RECORD, sizeof(long_sig_t));

        manifestFile.write(buffer, MC_BLOCK_SIZE);
        clearBuffer();
    }
    for (FriendIterator friendIter = currSet.getFriendIteratorBegin(); !currSet.checkFriendIteratorEnd(friendIter); ++friendIter) {

        copyCommonBlock(
            stringTable,
            TYPE_SIG_FR,
            (*friendIter)->name,
            (*friendIter)->rarity,
            BOOL_SIG_FALSE, // TODO: Proper foil storage
            (*friendIter)->frequency,
            (*friendIter)->specialText);

        copyValueToBuffer(&(*friendIter)->colour, sizeof(sig_t));
        copyValueToBuffer(&(*friendIter)->power, sizeof(uint8_t));
        copyValueToBuffer(&(*friendIter)->typeModifiers, sizeof(uint8_t));
        copyValueToBuffer(&(*friendIter)->actionCost, sizeof(uint8_t));
        copyValueToBuffer(&(*friendIter)->developmentCost, sizeof(uint8_t));
        copyValueToBuffer(&(*friendIter)->species, sizeof(sig_t));

        copyValueToBuffer(&END_OF_RECORD, sizeof(long_sig_t));

        manifestFile.write(buffer, FRIEND_BLOCK_SIZE);
        clearBuffer();
    }
    for (ResourceIterator resIter = currSet.getResourceIteratorBegin(); !currSet.checkResourceIteratorEnd(resIter); ++resIter) {

        copyCommonBlock(
            stringTable,
            TYPE_SIG_RE,
            (*resIter)->name,
            (*resIter)->rarity,
            BOOL_SIG_FALSE, // TODO: Proper foil storage
            (*resIter)->frequency,
            (*resIter)->specialText);

        copyValueToBuffer(&(*resIter)->colour, sizeof(sig_t));
        copyValueToBuffer(&(*resIter)->power, sizeof(uint8_t));
        copyValueToBuffer(&(*resIter)->typeModifiers, sizeof(uint8_t));
        copyValueToBuffer(&(*resIter)->actionCost, sizeof(uint8_t));
        copyValueToBuffer(&(*resIter)->developmentCost, sizeof(uint8_t));
        copyValueToBuffer(&(*resIter)->location, sizeof(sig_t));

        copyValueToBuffer(&END_OF_RECORD, sizeof(long_sig_t));

        manifestFile.write(buffer, RESOURCE_BLOCK_SIZE);
        clearBuffer();
    }
    for (EventIterator eventIter = currSet.getEventIteratorBegin(); !currSet.checkEventIteratorEnd(eventIter); ++eventIter) {

        copyCommonBlock(
            stringTable,
            TYPE_SIG_EV,
            (*eventIter)->name,
            (*eventIter)->rarity,
            BOOL_SIG_FALSE, // TODO: Proper foil storage
            (*eventIter)->frequency,
            (*eventIter)->specialText);

        copyValueToBuffer(&(*eventIter)->colour, sizeof(sig_t));
        copyValueToBuffer(&(*eventIter)->power, sizeof(uint8_t));
        copyValueToBuffer(&(*eventIter)->typeModifiers, sizeof(uint8_t));
        copyValueToBuffer(&(*eventIter)->actionCost, sizeof(uint8_t));
        copyValueToBuffer(&(*eventIter)->developmentCost, sizeof(uint8_t));

        copyValueToBuffer(&END_OF_RECORD, sizeof(long_sig_t));

        manifestFile.write(buffer, EVENT_BLOCK_SIZE);
        clearBuffer();
    }
    for (ProblemIterator probIter = currSet.getProblemIteratorBegin(); !currSet.checkProblemIteratorEnd(probIter); ++probIter) {

        copyCommonBlock(
            stringTable,
            TYPE_SIG_PR,
            (*probIter)->name,
            (*probIter)->rarity,
            BOOL_SIG_FALSE, // Foil problems don't exist
            (*probIter)->frequency,
            (*probIter)->specialText);

        copyValueToBuffer(&(*probIter)->pointBonus, sizeof(uint8_t));
        copyValueToBuffer(&(*probIter)->neutralConfrontCost, sizeof(uint8_t));
        copyValueToBuffer(&(*probIter)->primaryColour, sizeof(sig_t));
        copyValueToBuffer(&(*probIter)->secondaryColour, sizeof(sig_t));
        copyValueToBuffer(&(*probIter)->primaryColourConfrontCost, sizeof(uint8_t));
        copyValueToBuffer(&(*probIter)->secondaryColourConfrontCost, sizeof(uint8_t));
        copyValueToBuffer(&((*probIter)->isStarting ? BOOL_SIG_TRUE : BOOL_SIG_TRUE), sizeof(sig_t));

        copyValueToBuffer(&END_OF_RECORD, sizeof(long_sig_t));

        manifestFile.write(buffer, PROBLEM_BLOCK_SIZE);
        clearBuffer();
    }

    // Once all of the cards have been written into the file, it's time to then write the string table.
    // Offset all of the strings by the size of the string dictionary.
    int stringTableDictSize = stringTable.getNumStrings() * STRING_TABLE_ENTRY_SIZE;
    stringTable.offsetAllMembers(stringTableDictSize);
    
    for (iter_t i = 0; i < stringTable.getNumStrings(); ++i) {
        int offset = stringTable.getOffsetAt(i);
        copyValueToBuffer(&offset, sizeof(uint32_t));
        int strLength = stringTable.getStringAt(i).length();
        copyValueToBuffer(&strLength, sizeof(uint16_t));
    }

    // Finally, write the strings themselves
    string specialStrings = "";

    for (iter_t i = 0; i < stringTable.getNumStrings(); ++i) {
        specialStrings.append(stringTable.getStringAt(i));
    }

    copyValueToBuffer((void*)specialStrings.c_str(), specialStrings.length());
    manifestFile.write(buffer, stringTableDictSize + specialStrings.length());
    clearBuffer();

    manifestFile.close();
}

// Common code to deal with the common header block for every card
void ManifestInterface::copyCommonBlock(StringTable stringTable, sig_t cardType, string name, sig_t rarity, sig_t isFoil, int frequency, vector<string> specialText) {

    copyValueToBuffer(&cardType, sizeof(sig_t));
    int stringTableIndex = stringTable.add(name);
    copyValueToBuffer(&stringTableIndex, sizeof(int));
    copyValueToBuffer(&rarity, sizeof(sig_t));
    copyValueToBuffer(&isFoil, sizeof(sig_t));
    copyValueToBuffer(&frequency, sizeof(int));

    string specialTextString = "";
    for (iter_t i = 0; i < specialText.size(); ++i) {
        specialTextString.append(specialText[i]);
    }
    stringTableIndex = stringTable.add(specialTextString);\
    copyValueToBuffer(&stringTableIndex, sizeof(int));
}

// Copy value into the buffer and adjust currBufferPos to point immediately after it
void ManifestInterface::copyValueToBuffer(void* value, size_t numBytes) {

    memmove(currBufferPos, value, numBytes);
    currBufferPos = (char*)currBufferPos + numBytes;
}

void ManifestInterface::clearBuffer() {
    // Set currBufferPos back to the start of the buffer.
    currBufferPos = buffer;
}

/////////////////////////////////////////////////////////////////////////////////////////////
//                  String Table Methods
/////////////////////////////////////////////////////////////////////////////////////////////

StringTable::StringTable() {}
StringTable::~StringTable() {}

int StringTable::add(string newString) {
    
    strings.push_back(newString);
    
    if (offsets.size() > 0) {
        int oldOffset = offsets[offsets.size()-1];
        offsets.push_back(oldOffset + newString.length());
    }
    else
        offsets.push_back(0);
    // Index of the newly inserted string, which is also the index in the file's string
    // table where this string's STE will be.
    return strings.size()-1;
}

string StringTable::getStringAt(int index) {
    return strings[index];
}

int StringTable::getOffsetAt(int index) {
    return offsets[index];
}

iter_t StringTable::getNumStrings() {
    return strings.size();
}

// Once all of the records are written to the file, all of the string table entries
// will need to be additionally offset by the size of the string table dictionary.
void StringTable::offsetAllMembers(const int extraOffset) {

    for (iter_t i = 0; i < offsets.size(); ++i) {
        offsets[i] += extraOffset;
    }
}