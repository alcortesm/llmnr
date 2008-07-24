#include "util.h"
#include "rdataMX.h"

using std::string;
using rr::RdataMX;
using rr::Rdata;

RdataMX::RdataMX(unsigned short preference, string const & exchange)
    : Rdata::Rdata(RdataMX::PREFERENCE_LENGTH + (int) exchange.length()),
    d_preference(preference)
{
    d_exchangep = new string(exchange);
}

RdataMX::RdataMX(RdataMX const & data)
    : Rdata::Rdata(RdataMX::PREFERENCE_LENGTH + (int) data.exchange().length()),
    d_preference(data.preference())
{
        d_exchangep = new string(data.exchange());
}

RdataMX const &
RdataMX::operator=(RdataMX const & data)
{
    RdataMX * rp = new RdataMX(data);
    return *rp;
}

RdataMX::~RdataMX()
{
    delete this->d_exchangep;
}

RdataMX const *
RdataMX::parse(string const & s) throw (Rdata::ExBadSyntax)
{
    string space = " ";

    if (s.length() < 3) // minimun is like "0 a"
        throw Rdata::ExBadSyntax();

    size_t first_space;
    first_space = s.find_first_of(space, 0);
    if (first_space == string::npos)
        throw Rdata::ExBadSyntax();
    size_t preference_head = 0;
    size_t preference_size = first_space - preference_head;

    size_t exchange_head = s.find_first_not_of(space, first_space);
    if (exchange_head == string::npos)
        throw Rdata::ExBadSyntax();
    if (exchange_head != first_space + 1)
        throw Rdata::ExBadSyntax();
    size_t exchange_size = s.length() - exchange_head;
    
    size_t more_space;
    more_space = s.find_first_of(space, exchange_head);
    if (more_space != string::npos)
        throw Rdata::ExBadSyntax();

    string preference_str = s.substr(preference_head, preference_size);
    string exchange_str   = s.substr(exchange_head,   exchange_size);

    unsigned short preference;
    try {
        preference = util::str2uint16(preference_str);
    } catch (string & s) {
        throw Rdata::ExBadSyntax();
    }
    
    RdataMX * datap = new RdataMX(preference, exchange_str);
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
    return *d_exchangep;
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
    s << d_preference << " " << *d_exchangep ;
}

void
RdataMX::marshall(char * & offset) const
{
    if (this->length() == 0)
        return;

    char * last = offset + this->length() - 1;
    for (; offset<=last; offset++)
        *offset = 'a';

    return;
}

RdataMX const *
RdataMX::unmarshall(char const * & offset) throw (Rdata::ExBadSyntax)
{
    if (*offset != 'a')
        throw Rdata::ExBadSyntax();

    RdataMX const * dp = RdataMX::parse("127.0.0.1");

    offset += 5;

    return dp;
}

bool
rr::operator==(rr::RdataMX const & a, rr::RdataMX const & b)
{
    if (a.preference() != b.preference())
        return false;
    if (a.exchange().compare(b.exchange()) != 0)
        return false;
    return true;
}

bool
rr::operator!=(rr::RdataMX const & a, rr::RdataMX const & b)
{
    return ! (a == b);
}


