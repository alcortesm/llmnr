#include "util.h"
#include "rdataNS.h"

using std::string;
using rr::RdataNS;
using rr::Rdata;

RdataNS::RdataNS(string const & nsdname)
    : Rdata::Rdata((unsigned short) nsdname.length())
{
    d_nsdnamep = new string(nsdname);
}

RdataNS::RdataNS(RdataNS const & data)
    : Rdata::Rdata((unsigned short) data.nsdname().length())
{
        d_nsdnamep = new string(data.nsdname());
}

RdataNS &
RdataNS::operator=(RdataNS const & data)
{
    RdataNS * rp = new RdataNS(data);
    return *rp;
}

RdataNS::~RdataNS()
{
    delete this->d_nsdnamep;
}

RdataNS const *
RdataNS::parse(string const & s) throw (Rdata::ExBadSyntax)
{
    if (!util::isDomainName(s))
        throw Rdata::ExBadSyntax();
    RdataNS * datap = new RdataNS(s);
    return datap;
}

string const &
RdataNS::nsdname() const
{
    return *d_nsdnamep;
}

rr::Type const &
RdataNS::type() const
{
    return rr::Type::NS;
}

rr::Klass const &
RdataNS::klass() const
{
    return rr::Klass::IN;
}

void
RdataNS::printOn(std::ostream & s) const
{
    s << *d_nsdnamep ;
}
