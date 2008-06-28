// Abstract class for the different DNS types

#ifndef INCLUDED_RDATA
#define INCLUDED_RDATA

#include "type.h"
#include "klass.h"
#include <iostream>

namespace rr {

    class Rdata {
    protected:
        unsigned short    d_length;   // length in octects of the rdata field, see rfc1035
        Rdata(unsigned short length);
        virtual void printOn(std::ostream & s) const = 0; // used by opeator<< for virtualization
    public:
        class ExBadSyntax {};
        friend std::ostream & operator<<(std::ostream & s, rr::Rdata const & data);
        unsigned short            length() const;
        virtual rr::Type  const & type()   const = 0;
        virtual rr::Klass const & klass()  const = 0;
        virtual ~Rdata();
    };
}
#endif
