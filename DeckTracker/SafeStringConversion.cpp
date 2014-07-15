
#include "SafeStringConversion.h"

// Verifies that a string fits the proper format to be considered
// a well-formed int. Overflows are considered errors.
bool SafeStringConversion::checkIsInt(string in) {

	// Ints may start with a '-' for negative
	// Other characters must be digits, and so fall within
	// the ASCII range 48-57
	unsigned int i = 0;
	bool retVal = true;
	bool isNegative = false;
	int tempResult = 0;

	if (in[0] == '-') {
		i++;
		isNegative = true;
	}

	while (i < in.size() && retVal) {
		if (in[i] < ASCII_ZERO || in[i] > ASCII_NINE)
			retVal = false;
		else {
			// Overflow detection: This function will treat overflows as
			// invalid.
			if (tempResult * 10 + (in[i] - ASCII_ZERO) < tempResult) {
				retVal = false;
			}
			else {
				tempResult *= 10;
				tempResult += (in[i] - ASCII_ZERO);
			}
		}
		++i;
	}

	return retVal;
}

// Converts a string to an integer, which is exported in toConvert
// This conversion assumes that the input has been verified with 
// checkIsInt above, and so does no error-checking.
int SafeStringConversion::stringToInt(string in) {

	// Ints may start with a '-' for negative
	// Other characters must be digits, and so fall within
	// the ASCII range 48-57
	unsigned int i = 0;
	bool isNegative = false;
	int tempResult = 0;

	if (in[0] == '-') {
		i++;
		isNegative = true;
	}

	while (i < in.size()) {
		tempResult *= 10;
		tempResult += (in[i] - ASCII_ZERO);
		++i;
	}

	if (isNegative)
		tempResult = -tempResult;

	return tempResult;
}

// Verifies that string in is of a form that can be readily
// interpreted as a boolean value.
bool SafeStringConversion::checkIsBool(string in) {

	bool retValue = true;

	if (in.compare("True") == 0 ||
		in.compare("true") == 0 ||
		in.compare("T") == 0 ||
		in.compare("False") == 0 ||
		in.compare("false") == 0 ||
		in.compare("F") == 0)
		retValue = true;
	else
		retValue = false;

	return retValue;
}

// Safely converts a string to a boolean value. It is assumed
// that string in has already been verified by checkIsBool above,
// and so no error-checking is done.
bool SafeStringConversion::stringToBool(string in) {

	bool retValue = true;

	if (in.compare("True") == 0 ||
		in.compare("true") == 0 ||
		in.compare("T") == 0)
		retValue = true;
	else if (in.compare("False") == 0 ||
		in.compare("false") == 0 ||
		in.compare("F") == 0)
		retValue = false;

	return retValue;
}

bool SafeStringConversion::checkIsFloat(string in) {
	
	// TODO: Implement this.
	return false;
}

float SafeStringConversion::stringToFloat(string in) {

	// TODO: This method is not needed for the present application, and is
	// a trickier problem after all, so I will work on it later.
	return false;
}

// Replaces ASCII capitals with ASCII lowercase.
// Ignores non-letter characters.
void SafeStringConversion::toLowerCase(string &in) {

	for (unsigned int i = 0; i < in.length(); ++i) {
		if (in[i] >= 65 && in[i] <= 90) {
			in[i] += 32;
		}
	}
}

// Replaces ASCII lowercase letters with ASCII capitals.
// Ignores non-letter characters.
void SafeStringConversion::toUpperCase(string &in) {

	for (unsigned int i = 0; i < in.length(); ++i) {
		if (in[i] >= 97 && in[i] <= 122) {
			in[i] -= 32;
		}
	}
}