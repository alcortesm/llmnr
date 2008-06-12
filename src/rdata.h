// Abstract class for the different DNS types

#ifndef INCLUDED_RDATA
#define INCLUDED_RDATA

namespace rr {

    class Rdata {
    protected:
        unsigned short d_length;
    public:
        virtual unsigned short length() = 0;
    };
}
#endif
