#include "util.h"
#include <cerrno>
#include <iostream>

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
    } else if (long_var > (util::MAX_USHORT)) {
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
    } else if (long_var > util::MAX_SLONG) {
        throw string("number too large for a 32 bit signed integer");
    } else if (long_var < util::MIN_SLONG) {
        throw string("number too small for a 32 bit signed integer");
    } else if (end_ptr == a) {
        throw string("not a valid numeric input");
    } else if (*end_ptr != '\0') {
        throw string("not a valid numeric input, it has extra characters at the end");
    }
    return (signed long int) long_var;
}

// see rfc1035, section 2.3.1
bool
util::isDomainName(string const & s)
{
    if (s.compare(" ") == 0)
        return true;
    
    if (s.size() < util::MIN_DNAME_SIZE)
        return false;
    if (s.size() > util::MAX_DNAME_SIZE)
        return false;

    size_t head = 0;
    size_t size;
    size_t next_dot;

    for (;;) {
        next_dot = s.find_first_of(util::DOT, head);
        if (next_dot == string::npos) { // last label
            size = s.size() - head;
            break;
        }
        size = next_dot - head;
        if (!isLabel(s, head, size))
            return false;
        head = next_dot + 1;
    }
    // last label
    if (!isLabel(s, head, size))
       return false;
    return true;
}

// rfc 1035 section 2.3.1
bool
util::isLabel(string const & s, size_t head, size_t size)
{
    if (size < util::MIN_LABEL_SIZE)
        return false;
    if (size > util::MAX_LABEL_SIZE)
        return false;


    string label(s.substr(head, size));
    size_t first = 0;
    string first_str(label, first, 1);
    size_t last = size - 1;
    string last_str(label, last, 1);

    // check if there is any non ldh
    size_t not_dgh;
    not_dgh = label.find_first_not_of(util::LDH, first);
    if (not_dgh != string::npos)
        return false;
    
    // check if it start with a letter
    size_t letter;
    letter = first_str.find_first_of(util::LETTER);
    if (letter == string::npos)
        return false;
    if (size == 1)
        return true;

    // check if it end with a let-dig
    size_t let_dig;
    let_dig = last_str.find_first_of(util::LD);
    if (let_dig == string::npos)
        return false;
    if (size == 2)
        return true;

    return true;
}

bool
util::isLabel(string const & s) {
    return isLabel(s, 0, s.size());
}
