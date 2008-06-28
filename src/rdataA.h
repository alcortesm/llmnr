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
        unsigned long  addr()   const;
        rr::Type  const & type() const;
        rr::Klass const & klass() const;
        ~RdataA();
    
    private:
        void printOn(std::ostream & s) const ;
        RdataA(unsigned long addr);
    };

}
#endif
