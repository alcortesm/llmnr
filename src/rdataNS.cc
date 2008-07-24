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
    string s = this->nsdname();
    char const * ca = s.c_str();
    size_t dot;
    size_t label = 0;
    size_t label_sz;
    size_t len = s.length();

    for (;;) { // for each label...
        dot = s.find_first_of('.', label);
        if (dot == string::npos) { // this is the last label
            label_sz = len - label;
        } else {
            label_sz = dot - label;
        }

        // write label size
        *offset = (char) label_sz;
        offset++;
        
        // write label
        memcpy(offset, ca+label, label_sz);
        offset += label_sz;
        
        label += label_sz + 1 ; // label size plus the dot
        if (label > len) { // this was the last label
            *offset = '\0';
            offset++;
            break;
        }
    }

    return;
}

RdataNS const *
RdataNS::unmarshall(char const * & offset) throw (Rdata::ExBadSyntax)
{
    size_t label_sz;
    char * const s = (char * const) malloc((util::MAX_DNAME_SIZE+1)*sizeof(char));
    if (!s) {
        std::cerr << "Out of memory!" << std::endl ;
        exit (EXIT_FAILURE);
    }
    char * os = s;
    for (;;) { // for each label...
        
        // read label_sz
        label_sz = (size_t) *offset;
        offset++;

        // if end of data change the last dot for a \0 and finish
        if (label_sz == 0) {
            os --;
            *os = '\0';
            break;
        }

        // copy label
        memcpy(os, offset, label_sz);
        offset += label_sz;
        os += label_sz;
        if (os-s > util::MAX_DNAME_SIZE+1)
            throw Rdata::ExBadSyntax();

        // write extra dot
        *os = '.';
        os++;
        if ((os-s) > util::MAX_DNAME_SIZE+1)
            throw Rdata::ExBadSyntax();
    }

    RdataNS const * dp;
    dp = RdataNS::parse(s);
    free(s);
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


