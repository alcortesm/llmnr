#include "rdataA.h"

// for inet_ntop
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

using std::string;
using rr::RdataA;
using rr::Rdata;

RdataA::RdataA(unsigned long addr)
    : Rdata(RdataA::LENGTH),
    d_addr(addr)
{};

RdataA::~RdataA()
{}

RdataA const *
RdataA::parse(string const & s) throw (RdataA::ExBadSyntax)
{
    int r;
    const char * cp = s.c_str();
    struct in_addr in;
    r = inet_aton(cp, &in);
    if (r == 0)
        throw ExBadSyntax();

    RdataA * datap = new RdataA(in.s_addr);
    return datap;
}

unsigned long
RdataA::addr() const
{
    return d_addr;
}

rr::Type const &
RdataA::type() const
{
    return rr::Type::A;
}

rr::Klass const &
RdataA::klass() const
{
    return rr::Klass::IN;
}

void
RdataA::printOn(std::ostream & s) const
{
    char dst[INET_ADDRSTRLEN];
    char const * r;
    unsigned long addr = this->addr();
    const void * src = (const void *) &addr;
    r = inet_ntop(AF_INET, src, dst, INET_ADDRSTRLEN);
    if (r == 0) {
        std::cerr << "Error: inet_atop of " << addr << std::endl;
        exit(EXIT_FAILURE);
    }

    s << dst ;
}