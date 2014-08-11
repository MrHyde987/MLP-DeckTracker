#ifndef _MAIN_
#define _MAIN_

#include "Friend.h"
#include "Resource.h"
#include "Event.h"
#include "Problem.h"
#include "TroubleMaker.h"
#include "ManeCharacter.h"
#include "CardSet.h"

#include "StringUtility.h"

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

// TODO: On the refactor, this is another utility method that should go in 
// some general location.
vector<string> &split(string &s, char delim, vector<string> &elems);

#endif // ndef _MAIN_