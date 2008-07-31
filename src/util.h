#ifndef INCLUDED_UTIL
#define INCLUDED_UTIL

#include <string>

namespace util {
    
    /*
     * decimal number to int and viceversa
     */
    signed long    const MAX_SLONG  = ((1<<31) - 1);      //  2147483647
    signed long    const MIN_SLONG  = ((-1) * MAX_SLONG); // -2147483647
    unsigned short const MAX_USHORT = ((1<<16) - 1);      //  65535
    unsigned short const MIN_USHORT = 0;                  //  0

    signed long    str2sint32(std::string const & s) throw (std::string);
    unsigned short str2uint16(std::string const & s) throw (std::string);


    /*
     * DNS definitions and tests
     */

    // see RFC1035 section 2.3.4.
    unsigned short const MIN_DNAME_SIZE = 1;
    unsigned short const MAX_DNAME_SIZE = 255;
    unsigned short const MIN_LABEL_SIZE = 1;
    unsigned short const MAX_LABEL_SIZE = 63;

    // see RFC1035 section 2.3.1.
    std::string const DOT      = ".";
    std::string const HYP      = "-";
    std::string const DIGIT    = "0123456789";
    std::string const LETTER   = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    std::string const LD       = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    std::string const LDH      = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789-";
    std::string const SPACE    = " ";
    std::string const SPACETAB = " \t";

    bool           isDomainName(std::string const & s);
    bool           isLabel(std::string const & s, size_t head, size_t size);
    bool           isLabel(std::string const & s);

    /*
     * DNS names buffer representation
     */
    void dnsname2buf(std::string const & s, char * & offset); // increments offset to the next field
    std::string * buf2dnsname(char const * & offset) throw (std::string); // increments offset to the next field
}
#endif
