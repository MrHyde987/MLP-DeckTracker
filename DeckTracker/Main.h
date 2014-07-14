#ifndef _MAIN_
#define _MAIN_

#include "Friend.h"
#include "Resource.h"
#include "Event.h"
#include "Problem.h"
#include "TroubleMaker.h"
#include "ManeCharacter.h"
#include "CardSet.h"

#include <iostream>
#include <sstream>
#include <vector>
#include <string>

#include "boost/tokenizer.hpp"

using namespace std;

typedef enum {

	MODE_NOT_SET,
	MODE_TM,
	MODE_MC,
	MODE_FRIEND,
	MODE_RESOURCE,
	MODE_EVENT,
	MODE_PROBLEM

} Mode;

// The mode will be used to govern a lot of operations concerning
// the card set, most importantly allowing us to optimize queries by using
// segmented sets.
static Mode mode = MODE_NOT_SET;

#endif // ndef _MAIN_