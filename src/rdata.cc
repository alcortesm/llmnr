#include "rdata.h"
#include "rdataA.h"
#include "rdataNS.h"
#include "rdataMX.h"
#include "klass.h"
#include "type.h"

#include <stdexcept>

using rr::Rdata;
using rr::RdataA;
using rr::RdataNS;
using rr::RdataMX;
using rr::Klass;
using rr::Type;
using std::string;
using std::ostream;
using std::invalid_argument;

Rdata::ExBadSyntax::ExBadSyntax(string const & s)
    : invalid_argument(s)
{}

Rdata::Rdata(unsigned short length)
    : d_length(length)
{}

Rdata const *
Rdata::parse(Klass const & k, Type const & t, string const & s) throw (Rdata::ExBadSyntax)
{
    Rdata const * rdatap;
    try {
        if (k == Klass::IN) {
            if (t == Type::A) {
                rdatap = (Rdata *) RdataA::parse(s);
            } else if (t == Type::NS) {
                rdatap = (Rdata *) RdataNS::parse(s);
            } else if (t == Type::MX) {
                rdatap = (Rdata *) RdataMX::parse(s);
            } else if (t == Type::CNAME) {
                throw Rdata::ExBadSyntax("CNAME RRs are not supported yet");
            } else if (t == Type::PTR) {
                throw Rdata::ExBadSyntax("PTR RRs are not supported yet");
            } else if (t == Type::SOA) {
                throw Rdata::ExBadSyntax("SOA RRs are not supported yet");
            } else {
                throw Rdata::ExBadSyntax("" + t.name() + ": unknown RR type");
            }
        } else if (k == Klass::CS) {
            throw Rdata::ExBadSyntax("CS class RR are not supported");
        } else if (k == Klass::CH) {
            throw Rdata::ExBadSyntax("CH class RR are not supported");
        } else if (k == Klass::HS) {
            throw Rdata::ExBadSyntax("HS class RR are not supported");
        } else {
            throw Rdata::ExBadSyntax("" + k.name() + ": unknown RR class");
        }
    } catch (Rdata::ExBadSyntax & e) {
        throw Rdata::ExBadSyntax("error parsing RR: " + s + ": " + e.what());
    }
    return rdatap;
}

Rdata::~Rdata()
{}

unsigned short
Rdata::length() const
{
    return d_length;
}

ostream &
rr::operator<<(ostream & s, Rdata const & data)
{
    data.printOn(s);
    return s;
}

bool
rr::operator==(Rdata const & a, Rdata const & b)
{
    if (a.klass() != b.klass())
        return false;
    if (a.type()  != b.type())
        return false;
    return a.equals(b);
}

bool
rr::operator!=(Rdata const & a, Rdata const & b)
{
    return ! (a==b);
}
