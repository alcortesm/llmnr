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
        class ExBadSyntax {};
        static RdataA const * parse(std::string const & s) throw (ExBadSyntax);
        unsigned long  addr()   const;
        unsigned short length() const;
        ~RdataA();
    
    private:
        friend std::ostream & operator<<(std::ostream & s, RdataA const & data);
        RdataA(unsigned long addr);
    };

}
#endif
