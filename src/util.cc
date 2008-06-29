#include "util.h"
#include <cerrno>

using std::string;

// parse a decimal representation of a 16 bit unsigned integer
// thats between 0 and 65535 ((1<<16) -1)
unsigned short
util::str2uint16(string const & s) throw (string)
{
    const char * a = s.c_str();
    char *end_ptr;
    long int long_var;

    if (a[0] == 0)
        throw string("null input pointer");

    errno = 0;
    long_var = std::strtol(a, &end_ptr, 0); // decimal conversion

    if (errno == ERANGE) {
        throw string("number out of range");
    } else if (long_var > ((1<<16) -1)) {
        throw string("number too large for a 16 bits unsigned integer");
    } else if (long_var < 0) {
        throw string("negative number");
    } else if (end_ptr == a) {
        throw string("not valid numeric input");
    } else if (*end_ptr != '\0') {
        throw string("not valid numeric input, it has extra characters at the end");
    }
    return (unsigned short int) long_var;
}

// parse a decimal representation of a 32 bit signed integer
// thats between -2147483647 and 2147483647 (- ((1<<31)-1) ... 0 ... (1<<31)-1 )
signed long
util::str2sint32(string const & s) throw (string)
{
    const char * a = s.c_str();
    char *end_ptr;
    long int long_var;

    if (a[0] == 0)
        throw string("null pointer");

    errno = 0;
    long_var = std::strtol(a, &end_ptr, 0); // decimal conversion

    if (errno == ERANGE) {
        throw string("number out of range");
    } else if (long_var > util::MAX_LONG) {
        throw string("number too large for a 32 bit signed integer");
    } else if (long_var < util::MIN_LONG) {
        throw string("number too small for a 32 bit signed integer");
    } else if (end_ptr == a) {
        throw string("not a valid numeric input");
    } else if (*end_ptr != '\0') {
        throw string("not a valid numeric input, it has extra characters at the end");
    }
    return (signed long int) long_var;
}

