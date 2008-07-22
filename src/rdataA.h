#ifndef INCLUDED_RDATAA
#define INCLUDED_RDATAA

#include <iostream>
#include <string>
#include "rdata.h"

namespace rr {

    class RdataA : public rr::Rdata {

        unsigned long d_addr; // in network byte order
    
    public:
        static const unsigned short LENGTH = 4; // A registers use 4 octects, see rfc1035
        static RdataA const * parse(std::string const & s) throw (rr::Rdata::ExBadSyntax);
        ~RdataA();
        unsigned long     addr() const; // in network byte order
        rr::Type  const & type() const;
        rr::Klass const & klass() const;

        void marshalling(char * & offset) const; // offset is advanced
        static RdataA const * unmarshalling(char const * & offset) // offset is advanced
            throw (rr::Rdata::ExBadSyntax);
    
    private:
        void printOn(std::ostream & s) const ;
        RdataA(unsigned long addr);
    };

}
#endif
