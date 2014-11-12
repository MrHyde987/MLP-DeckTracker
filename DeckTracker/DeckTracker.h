// Universal include file for the project
#ifndef _DECK_TRACKER_
#define _DECK_TRACKER_

#include <map>
#include <stdint.h>

using namespace std;

using sig_t         = uint8_t;
using long_sig_t    = int64_t;
using recordSize_t  = const uint8_t;
using iter_t        = unsigned int;

typedef std::map<int, string> SigMap;
typedef std::pair<int, string> sigMapPair;

// Type Signatures that all classes need to be aware of.

// Card Rarity Signature Values
const static sig_t RARITY_SIG_COMMON =            0x70;
const static sig_t RARITY_SIG_UNCOMMON =          0x71;
const static sig_t RARITY_SIG_RARE =              0x72;
const static sig_t RARITY_SIG_ULTRA_RARE =        0x73;
const static sig_t RARITY_SIG_FIXED =             0x74;
const static sig_t RARITY_SIG_PROMOTIONAL =       0x75;

// Colour Signature Values
const static sig_t COLOUR_SIG_PURPLE =            0x0A;
const static sig_t COLOUR_SIG_BLUE =              0x0B;
const static sig_t COLOUR_SIG_YELLOW =            0x0C;
const static sig_t COLOUR_SIG_PINK =              0x0D;
const static sig_t COLOUR_SIG_WHITE =             0x0E;
const static sig_t COLOUR_SIG_ORANGE =            0x0F;

// Species Signature Values
const static sig_t SPECIES_SIG_UNICORN =          0xA0;
const static sig_t SPECIES_SIG_PEGASUS =          0xA1;
const static sig_t SPECIES_SIG_EARTH_PONY =       0xA2;
const static sig_t SPECIES_SIG_ALICORN =          0xA3;
const static sig_t SPECIES_SIG_ZEBRA =            0xA4;
const static sig_t SPECIES_SIG_DRAGON =           0xA5;
const static sig_t SPECIES_SIG_CRITTER =          0xA6;
const static sig_t SPECIES_SIG_BUFFALO =          0xA7;
const static sig_t SPECIES_SIG_GRIFFON =          0xA8;  // Reserved (My guess is we'll have griffons in Crystal Games)
const static sig_t SPECIES_SIG_DRACONEQUUS =      0xA9;  // Reserved (Discord is coming)

// Resource Location Signatures
const static sig_t LOCATION_SIG_HOME =            0x50;
const static sig_t LOCATION_SIG_FRIEND =          0x51;
const static sig_t LOCATION_SIG_OPPOSING_FRIEND = 0x52;
const static sig_t LOCATION_SIG_TROUBLEMAKER =    0x53;
const static sig_t LOCATION_SIG_PROBLEM =         0x54;
const static sig_t LOCATION_SIG_RESERVED =        0x55;
const static sig_t LOCATION_SIG_MANE_CHARACTER =  0x56;
const static sig_t LOCATION_SIG_OPP_MC =          0x57;
const static sig_t LOCATION_SIG_RESERVED_2 =      0x58;
const static sig_t LOCATION_SIG_RESERVED_3 =      0x59;

const static sig_t COLOUR_SIG_ANY =               0x28;
const static sig_t COLOUR_SIG_NONE =              0x29;

// Type Modifier flags

// Friend/MC Type Modifier Flags
const static sig_t TYPEARG_ELDER =                0x01;
const static sig_t TYPEARG_FOAL =                 0x02;
const static sig_t TYPEARG_ROYALTY =              0x04;
const static sig_t TYPEARG_RESERVED_1 =           0x08;
const static sig_t TYPEARG_RESERVED_2 =           0x10;
const static sig_t TYPEARG_RESERVED_3 =           0x20;
const static sig_t TYPEARG_RESERVED_4 =           0x40;
// 0x80 is reserved for Unique --> See below.

// Resource Type Modifier Flags
const static sig_t RES_TYPEARG_LOCATION =         0x01;
const static sig_t RES_TYPEARG_ASSET =            0x02;
const static sig_t RES_TYPEARG_REPORT =           0x04;
const static sig_t RES_TYPEARG_ACCESSORY =        0x08;
const static sig_t RES_TYPEARG_CONDITION =        0x10;
const static sig_t RES_TYPEARG_ARTIFACT =         0x20;
const static sig_t RES_TYPEARG_RESERVED_3 =       0x40;
// 0x80 is Unique. See below.

// Event Type Modifier Flags
const static sig_t EVENT_TYPEARG_GOTCHA =         0x01;
const static sig_t EVENT_TYPEARG_SHOWDOWN =       0x02; // TODO: Look up what the rest of these are
const static sig_t EVENT_TYPEARG_RESERVED__1 =    0x04;
const static sig_t EVENT_TYPEARG_RESERVED_0 =     0x08;
const static sig_t EVENT_TYPEARG_RESERVED_1 =     0x10;
const static sig_t EVENT_TYPEARG_RESERVED_2 =     0x20;
const static sig_t EVENT_TYPEARG_RESERVED_3 =     0x40;
const static sig_t EVENT_TYPEARG_RESERVED_4 =     0x80; // Events can't be Unique, so we are allowed to use this value.

// Special Typearg values
const static sig_t TYPEARG_UNIQUE =               0x80;

#endif