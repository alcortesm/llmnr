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

void
RdataNS::marshall(char * & offset) const
{
    if (this->length() == 0)
        return;

    char * last = offset + this->length() - 1;
    for (; offset<=last; offset++)
        *offset = 'a';

    return;
}

RdataNS const *
RdataNS::unmarshall(char const * & offset) throw (Rdata::ExBadSyntax)
{
    if (*offset != 'a')
        throw Rdata::ExBadSyntax();

    RdataNS const * dp = RdataNS::parse("it.uc3m.es");

    offset += 11;

    return dp;
}

bool
rr::operator==(rr::RdataNS const & a, rr::RdataNS const & b)
{
    if (a.nsdname().compare(b.nsdname()) != 0)
        return false;
    return true;
}

bool
rr::operator!=(rr::RdataNS const & a, rr::RdataNS const & b)
{
    return ! (a == b);
}


