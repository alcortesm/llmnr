#include "util.h"
#include "rr.h"
#include "type.h"
#include "klass.h"
#include "rdata.h"
#include "rdataA.h"
#include "rdataNS.h"
#include "rdataMX.h"

#include <iostream>

using std::string;
using rr::Rr;
using rr::Type;
using rr::Klass;
using rr::Rdata;
using rr::RdataA;
using rr::RdataNS;
using rr::RdataMX;

Rr const *
Rr::parse(string const & s) throw (Rr::ExNoContent, Rr::ExBadSyntax) {
    Rr const * rrp;

    string space = " \t"; // space or tab
    
    size_t first_non_space;
    first_non_space = s.find_first_not_of(space, 0);
    if (first_non_space == string::npos)
        throw Rr::ExNoContent();
    if (s.at(first_non_space) == '#')
        throw Rr::ExNoContent();

    size_t name_head =  first_non_space;
    size_t space_after_name = s.find_first_of(space, name_head);
    if (space_after_name == string::npos)
        throw Rr::ExBadSyntax();
    size_t name_size = space_after_name - name_head;

    size_t ttl_head = s.find_first_not_of(space, space_after_name);
    if (ttl_head == string::npos)
        throw Rr::ExBadSyntax();
    size_t space_after_ttl = s.find_first_of(space, ttl_head);
    if (space_after_ttl == string::npos)
        throw Rr::ExBadSyntax();
    size_t ttl_size = space_after_ttl - ttl_head;
    
    size_t klass_head = s.find_first_not_of(space, space_after_ttl);
    if (klass_head == string::npos)
        throw Rr::ExBadSyntax();
    size_t space_after_klass = s.find_first_of(space, klass_head);
    if (space_after_klass == string::npos)
        throw Rr::ExBadSyntax();
    size_t klass_size = space_after_klass - klass_head;
    
    size_t type_head = s.find_first_not_of(space, space_after_klass);
    if (type_head == string::npos)
        throw Rr::ExBadSyntax();
    size_t space_after_type = s.find_first_of(space, type_head);
    if (space_after_type == string::npos)
        throw Rr::ExBadSyntax();
    size_t type_size = space_after_type - type_head;
    
    size_t rdata_head = s.find_first_not_of(space, space_after_type);
    if (rdata_head == string::npos)
        throw Rr::ExBadSyntax();
    size_t end_of_rdata = s.find_last_not_of(space);
    size_t rdata_size = end_of_rdata - rdata_head + 1;
    if (rdata_size == 0)
        throw Rr::ExBadSyntax();
    
    string const name_str  = s.substr(name_head,  name_size);
    string const type_str  = s.substr(type_head,  type_size);
    string const klass_str = s.substr(klass_head, klass_size);
    string const ttl_str   = s.substr(ttl_head,   ttl_size);
    string const rdata_str = s.substr(rdata_head, rdata_size);

    Type const & type = Type::fromName(type_str);
    Klass const & klass = Klass::fromName(klass_str);
    signed long ttl;
    try {
        ttl = util::str2sint32(ttl_str);
    } catch (string & s) {
        throw Rr::ExBadSyntax();
    }

    Rdata const * rdatap;
    try {
        rdatap = Rdata::parse(klass, type, rdata_str);
    } catch (Rdata::ExBadSyntax & ex) {
        throw Rr::ExBadSyntax();
    }

    rrp = new Rr(name_str, type, klass, ttl, rdatap);
    return rrp;
}

std::string const &
Rr::name() const {
    return d_name;
}

Type const &
Rr::type() const {
    return d_type;
}

Klass const &
Rr::klass() const {
    return d_klass;
}

signed long int
Rr::ttl() const {
    return d_ttl;
}

Rdata const &
Rr::rdata() const {
    return *d_rdatap;
}

Rr::Rr(std::string const & name,
            Type const & type,
            Klass const & klass,
            signed long int ttl,
            Rdata const * const rdatap)
:
    d_name(name),
    d_type(type),
    d_klass(klass),
    d_ttl(ttl),
    d_rdatap(rdatap)
{};

Rr::~Rr()
{
    delete d_rdatap;
}

std::ostream &
rr::operator<< (std::ostream & s, Rr const & rr)
{
    s << rr.name()  << "\t";
    s << rr.ttl()   << "\t";
    s << rr.klass() << "\t";
    s << rr.type()  << "\t";
    s << rr.rdata();
    return s;
}

bool
rr::operator==(Rr const & a, Rr const & b)
{
    if (a.name().compare(b.name()) != 0)
        return false;
    if (a.type() != b.type())
        return false;
    if (a.klass() != b.klass())
        return false;
    if (a.ttl() != b.ttl())
        return false;
    if (a.rdata() != b.rdata())
        return false;
    return true;
}

bool
rr::operator!=(Rr const & a, Rr const & b)
{
    return ! (a == b);
}
