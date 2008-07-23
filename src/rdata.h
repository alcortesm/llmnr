// Abstract class for the different DNS types
//
// There are two public constructors:

#ifndef INCLUDED_RDATA
#define INCLUDED_RDATA

#include "type.h"
#include "klass.h"
#include <iostream>

namespace rr {

    class Rdata {
    protected:
        unsigned short d_length;   // length in octects of the rdata field, see rfc1035
        Rdata(unsigned short length);
        virtual void printOn(std::ostream & s) const = 0; // used to virtualize opeator<<
    public:
        class ExBadSyntax {};
        friend std::ostream & operator<<(std::ostream & s, rr::Rdata const & data);
        virtual ~Rdata();
        unsigned short            length() const;
        virtual rr::Type  const & type()   const = 0;
        virtual rr::Klass const & klass()  const = 0;

        virtual void marshalling(char * & offset) const = 0; // offset is advanced
        static Rdata const * unmarshalling(char const * & offset) // offset is advanced
            throw (rr::Rdata::ExBadSyntax);
    };
}
#endif
