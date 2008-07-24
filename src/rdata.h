// Abstract class for the different DNS types

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
        // friend bool operator==(rr::Rdata const & a, rr::Rdata const & b); should be provided by subclasses
        // friend bool operator!=(rr::Rdata const & a, rr::Rdata const & b); should be provided by subclasses
        // parse(std::string s) should be a static function provided by subclasses
        virtual ~Rdata();
        unsigned short            length() const;
        virtual rr::Type  const & type()   const = 0;
        virtual rr::Klass const & klass()  const = 0;

        virtual void marshall(char * & offset) const = 0; // offset is advanced
        // unmarshall(char const * & offset) should be a static function provided by subclasses
    };
}
#endif
