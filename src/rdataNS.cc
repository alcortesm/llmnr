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
    if (!util::isFQDN(s))
        throw Rdata::ExBadSyntax(s + ": bad FQDN");
    string const * dnamep = util::fqdn2dname(s);
    RdataNS * datap = new RdataNS(*dnamep);
    delete dnamep;
    return datap;
}

string const &
RdataNS::nsdname() const
{
    return *d_nsdnamep;
}

rr::Type const & RdataNS::type() const
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
    string const * fqdnp = util::dname2fqdn(*d_nsdnamep);
    s << *fqdnp ;
    delete fqdnp;
}

void
RdataNS::marshall(char * & offset) const
{
    util::dnsname2buf(this->nsdname(), offset);
    return;
}

RdataNS const *
RdataNS::unmarshall(char const * & offset) throw (Rdata::ExBadSyntax)
{
    string * sp;
    try {
        sp = util::buf2dnsname(offset);
    } catch (string & e) {
        throw Rdata::ExBadSyntax("unmarshalling error for NS RR: " + e);
    }

    string const * fqdnp = util::dname2fqdn(*sp);
    delete sp;

    RdataNS const * dp;
    dp = RdataNS::parse(*fqdnp);
    delete fqdnp;

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

bool
RdataNS::equals(rr::Rdata const & o) const
{
    if (this->klass() != o.klass())
        return false;
    if (this->type() != o.type())
        return false;
    RdataNS const * dp = (RdataNS const *) &o;
    return (*this == *dp);
}
