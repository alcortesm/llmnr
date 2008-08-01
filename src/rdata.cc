#include "rdata.h"
#include "rdataA.h"
#include "rdataNS.h"
#include "rdataMX.h"
#include "klass.h"
#include "type.h"

using rr::Rdata;
using rr::RdataA;
using rr::RdataNS;
using rr::RdataMX;
using rr::Klass;
using rr::Type;

rr::Rdata::Rdata(unsigned short length)
    : d_length(length)
{}

Rdata const *
Rdata::parse(Klass const & k, Type const & t, std::string const & s) throw (Rdata::ExBadSyntax)
{
    Rdata const * rdatap;
    if (k == Klass::IN) {
        if (t == Type::A) {
            rdatap = (Rdata *) RdataA::parse(s);
        } else if (t == Type::NS) {
            RdataNS const * rdataNSp;
            rdataNSp = RdataNS::parse(s);
            rdatap = (Rdata *) rdataNSp;
        } else if (t == Type::MX) {
            RdataMX const * rdataMXp;
            rdataMXp = RdataMX::parse(s);
            rdatap = (Rdata *) rdataMXp;
        } else { // CNAME, SOA, PTR
            throw Rdata::ExBadSyntax();
        }
    } else { // not Klass::IN
        throw Rdata::ExBadSyntax();
    }
    return rdatap;
}

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

bool
rr::operator==(rr::Rdata const & a, rr::Rdata const & b)
{
    if (a.klass() != b.klass())
        return false;
    if (a.type()  != b.type())
        return false;
    return a.equals(b);
}

bool
rr::operator!=(rr::Rdata const & a, rr::Rdata const & b)
{
    return ! (a==b);
}
