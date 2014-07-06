#ifndef _SSC_
#define _SSC_

#include <string>

using namespace std;

// This class contains utility functions for validating that strings
// conform to certain proper forms. It can be used for input validation,
// supplementing the relatively weak error protection offered by functions
// like stoi.
class SafeStringConversion {

private:
	const static int ASCII_ZERO = 48;
	const static int ASCII_NINE = 57;

public:
	// These are the verification functions
	static bool checkIsInt(string in);
	static bool checkIsBool(string in);
	static bool checkIsFloat(string in);

	// These actually do the conversions
	static int stringToInt(string in);
	static bool stringToBool(string in);
	static float stringToFloat(string in);
};
#endif // _SSC_