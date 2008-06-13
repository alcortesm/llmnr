// Abstract class for the different DNS types

#ifndef INCLUDED_RDATA
#define INCLUDED_RDATA

#include <iostream>

namespace rr {

    class Rdata {
    protected:
        unsigned short d_length;   // length in octects of the rdata field, see rfc1035
        Rdata(unsigned short length);
        virtual void printOn(std::ostream & s) const = 0; // used by opeator<< for virtualization
    public:
        friend std::ostream & operator<<(std::ostream & s, rr::Rdata const & data);
        virtual unsigned short length() const = 0;
        virtual ~Rdata();
    };
}
#endif
