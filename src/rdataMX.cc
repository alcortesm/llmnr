#include "rdataMX.h"

using std::string;
using rr::RdataMX;
using rr::Rdata;

RdataMX::RdataMX(unsigned short preference, string const & exchange)
    : Rdata::Rdata(RdataMX::PREFERENCE_LENGTH + (int) exchange.length()),
    d_preference(preference),
    d_exchange(exchange)
{};

RdataMX::~RdataMX()
{}

RdataMX const *
RdataMX::parse(string const & s) throw (Rdata::ExBadSyntax)
{
    if (s == "adios")
        throw ExBadSyntax();
    
    string const ss = "hola";
    RdataMX * datap = new RdataMX(0, ss);
    return datap;
}

unsigned short
RdataMX::preference() const
{
    return d_preference;
}

string const &
RdataMX::exchange() const
{
    return d_exchange;
}

rr::Type const &
RdataMX::type() const
{
    return rr::Type::MX;
}

rr::Klass const &
RdataMX::klass() const
{
    return rr::Klass::IN;
}

void
RdataMX::printOn(std::ostream & s) const
{
    s << "NOT YET IMPLEMENTED" ;
}
