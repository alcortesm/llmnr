#ifndef INCLUDED_UTIL
#define INCLUDED_UTIL

#include <string>

namespace util {

    const long MAX_LONG = ((1<<31)-1);
    const long MIN_LONG = ((-1)*MAX_LONG);

    signed long    str2sint32(const char * const a) throw (std::string);
    unsigned short str2uint16(const char * const a) throw (std::string);
}
#endif
