#ifndef _SSC_
#define _SSC_

#include <string>
#include <vector>
#include <sstream>

using namespace std;

// This class contains utility functions for working with strings,
// especially strings that have just been parsed from an input stream.
class StringUtility {

private:
    const static int ASCII_ZERO = 48;
    const static int ASCII_NINE = 57;

public:
    // These are the verification functions
    static bool checkIsInt(string in);
    static bool checkIsBool(string in);
    static bool checkIsFloat(string in);
    static bool checkIsPositiveInt(string in);
    // Down here -> maybe add a few more good utility functions

    // These actually do the conversions
    static int stringToInt(string in);
    static bool stringToBool(string in);
    static float stringToFloat(string in);

    // Various other utility functions
    static void toLowerCase(string &in);
    static void toUpperCase(string &in);

    static vector<string> &split(string &s, char delim, vector<string> &elems);
};
#endif // _SSC_