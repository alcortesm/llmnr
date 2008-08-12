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

bool
util::isFQDN(string const & s)
{
    string sub;
    string::size_type last;
    string::size_type nchars;

    last = s.size() - 1 ;
    nchars = s.size();

    if (s[last] != '.')
        return false;

    sub = s.substr(0, nchars-1); // strip the last char (the trailing '.')
    return isDomainName(sub);
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

string const *
util::fqdn2dname(string const & fqdn)
{
    string * dnamep = new string(fqdn.substr(0, fqdn.size()-1));
    return dnamep;
}

string const *
util::dname2fqdn(string const & dname)
{
    string * fqdnp = new string(dname + ".");
    return fqdnp;
}

void
util::dnsname2buf(string const & s, char * & offset)
{
    char const * ca = s.c_str();
    size_t dot;
    size_t label = 0;
    size_t label_sz;
    size_t len = s.length();

    for (;;) { // for each label...
        dot = s.find_first_of('.', label);
        if (dot == string::npos) { // this is the last label
            label_sz = len - label;
        } else {
            label_sz = dot - label;
        }

        // write label size
        *offset = (char) label_sz;
        offset++;
        
        // write label
        memcpy(offset, ca+label, label_sz);
        offset += label_sz;
        
        label += label_sz + 1 ; // label size plus the dot
        if (label > len) { // this was the last label
            *offset = '\0';
            offset++;
            break;
        }
    }

    return;
}

string *
util::buf2dnsname(char const * & offset) throw (string)
{
    size_t label_sz;
    char * const s = (char * const) malloc((util::MAX_DNAME_SIZE+1)*sizeof(char));
    if (!s) {
        std::cerr << "Out of memory!" << std::endl ;
        exit (EXIT_FAILURE);
    }
    char * os = s;
    for (;;) { // for each label...
        
        // read label_sz
        label_sz = (size_t) *offset;
        offset++;

        // if end of data change the last dot for a \0 and finish
        if (label_sz == 0) {
            os --;
            *os = '\0';
            break;
        }

        // copy label
        memcpy(os, offset, label_sz);
        offset += label_sz;
        os += label_sz;
        if (os-s >= util::MAX_DNAME_SIZE+1) {
            free(s);
            throw string("data too long");
        }

        // write extra dot
        *os = '.';
        os++;
        if ((os-s) > util::MAX_DNAME_SIZE+1) {
            free(s);
            throw string("data too long");
        }
    }

    string * sp = new string(s);
    free(s);
    return sp;
}
