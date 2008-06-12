// Abstract class for the different DNS types

#ifndef INCLUDED_RDATA
#define INCLUDED_RDATA

#include <iostream>

namespace rr {

    class Rdata {
    protected:
        unsigned short d_length; // length in octects of the rdata field, see rfc1035
        Rdata(unsigned short length);
    public:
        virtual unsigned short length() const = 0;
        virtual ~Rdata();
    private:
        friend virtual std::ostream & operator<<(std::ostream & s, Rdata & data);
    };
}
#endif
