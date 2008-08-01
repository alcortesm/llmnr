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
        virtual bool equals(rr::Rdata const & o) const = 0; // used to virtualize operator==
    public:
        class ExBadSyntax {};
        friend std::ostream & operator<<(std::ostream & s, rr::Rdata const & data);
        friend bool operator==(rr::Rdata const & a, rr::Rdata const & b);
        friend bool operator!=(rr::Rdata const & a, rr::Rdata const & b);
        // parse(std::string s) should be a static function provided by subclasses
        static Rdata const * parse(rr::Klass const & k, rr::Type const & t, std::string const & s) throw (rr::Rdata::ExBadSyntax);
        virtual ~Rdata();
        unsigned short            length() const;
        virtual rr::Type  const & type()   const = 0;
        virtual rr::Klass const & klass()  const = 0;

        virtual void marshall(char * & offset) const = 0; // offset is advanced
        // unmarshall(char const * & offset) should be a static function provided by subclasses
    };
}
#endif
