#include "rdata.h"

rr::Rdata::Rdata(unsigned short length)
    : d_length(length)
{};

rr::Rdata::~Rdata()
{}

unsigned short
rr::Rdata::length() const
{
    return d_length;
}

std::ostream &
rr::operator<<(std::ostream & s, rr::Rdata const & data)
{
    data.printOn(s);
    return s;
}
