#include "rr.h"
#include "type.h"
#include "klass.h"

#include <iostream>
#include <cerrno>

using std::string;
using rr::Rr;
using rr::Type;
using rr::Klass;

// parse a decimal representation of a 32 bit signed integer
// thats between -2147483647 and 2147483647 (- ((1<<31)-1) ... 0 ... (1<<31)-1 )
#define MAX_LONG ((1<<31)-1)
#define MIN_LONG ((-1)*MAX_LONG)
signed long
str2int32(const char * const a) throw (string) {
    char *end_ptr;
    long int long_var;

    if (a[0] == 0)
        throw string("null pointer");

    errno = 0;
    long_var = std::strtol(a, &end_ptr, 0); // decimal conversion

    if (errno == ERANGE) {
        throw string("number out of range");
    } else if (long_var > MAX_LONG) {
        throw string("number too large for a 32 bit signed integer");
    } else if (long_var < MIN_LONG) {
        throw string("number too small for a 32 bit signed integer");
    } else if (end_ptr == a) {
        throw string("not a valid numeric input");
    } else if (*end_ptr != '\0') {
        throw string("not a valid numeric input, it has extra characters at the end");
    }
    return (signed long int) long_var;
}

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
    
    string name_str  = s.substr(name_head,  name_size);
    string type_str  = s.substr(type_head,  type_size);
    string klass_str  = s.substr(klass_head,  klass_size);
    string ttl_str   = s.substr(ttl_head,   ttl_size);
    string rdata_str = s.substr(rdata_head, rdata_size);

    Type const & type = Type::fromName(type_str);
    Klass const & klass = Klass::fromName(klass_str);
    signed long ttl;
    try {
        ttl = str2int32(ttl_str.c_str());
    } catch (string & s) {
        throw Rr::ExBadSyntax();
    }
    
    rrp = new Rr(name_str, type, klass, ttl, rdata_str);
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

std::string const &
Rr::rdata() const {
    return d_rdata;
}

unsigned short int
Rr::rdlength() const {
    return (unsigned short int) d_rdata.size();
}

Rr::Rr(std::string const & name,
            Type const & type,
            Klass const & klass,
            signed long int ttl,
            std::string const & rdata)
:
    d_name(name),
    d_type(type),
    d_klass(klass),
    d_ttl(ttl),
    d_rdata(rdata)
{};

void
Rr::print() const {
    std::cout << "rr{name=" << d_name;
    std::cout << ", ttl="   << d_ttl;
    std::cout << ", klass=" << d_klass.name();
    std::cout << ", type="  << d_type.name();
    std::cout << ", rdata=" << d_rdata;
    std::cout << "}" << std::endl;
}
