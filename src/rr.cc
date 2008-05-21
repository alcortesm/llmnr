#include "rr.h"
#include "type.h"
#include "clas.h"

#include <iostream>
#include <cerrno>

using std::string;
using rr::Rr;
using rr::Type;
using rr::Clas;
using rr::ExNoContent;
using rr::ExBadSyntax;

// parse a decimal representation of a 32 bit signed integer
// thats between -2147483647 and 2147483647 (- ((1<<31)-1) ... 0 ... (1<<31)-1 )
#define MAX_LONG ((1<<31)-1)
#define MIN_LONG ((-1)*MAX_LONG)
signed long int
str2int32(const char * const a) {
    char *end_ptr;
    long int long_var;

    if (a[0] == 0)
        return (signed long int) 0;

    errno = 0;
    long_var = std::strtol(a, &end_ptr, 0); // decimal conversion

    if (errno == ERANGE) { // number out of range TODO: throw exception
        std::cerr << a << " is out of strtol() range" << std::endl;
        return (signed long int) 0;
    } else if (long_var > MAX_LONG) {
        std::cerr << a << " is too large for a 32 bit signed integer, max is " << MAX_LONG << std::endl;
        return (signed long int) 0;
    } else if (long_var < MIN_LONG) {
        std::cerr << a << " is too small for a 32 bit signed integer, min is " << MIN_LONG << std::endl;
        return (signed long int) 0;
    } else if (end_ptr == a) {
        std::cerr << a << " is not a valid numeric input" << std::endl;
        return (signed long int) 0;
    } else if (*end_ptr != '\0') {
        std::cerr << a << " is not a valid numeric input, it has extra caracters at the end" << std::endl;
        return (signed long int) 0;
    }
    return (signed long int) long_var;
}

Rr const *
Rr::parse(string const & s) throw (ExNoContent, ExBadSyntax) {
    Rr const * rrp;

    string space = " \t"; // space or tab
    
    size_t first_non_space;
    first_non_space = s.find_first_not_of(space, 0);
    if (first_non_space == string::npos)
        throw ExNoContent();
    if (s.at(first_non_space) == '#')
        throw ExNoContent();

    size_t name_head =  first_non_space;
    size_t space_after_name = s.find_first_of(space, name_head);
    if (space_after_name == string::npos)
        throw ExBadSyntax();
    size_t name_size = space_after_name - name_head;

    size_t ttl_head = s.find_first_not_of(space, space_after_name);
    if (ttl_head == string::npos)
        throw ExBadSyntax();
    size_t space_after_ttl = s.find_first_of(space, ttl_head);
    if (space_after_ttl == string::npos)
        throw ExBadSyntax();
    size_t ttl_size = space_after_ttl - ttl_head;
    
    size_t clas_head = s.find_first_not_of(space, space_after_ttl);
    if (clas_head == string::npos)
        throw ExBadSyntax();
    size_t space_after_clas = s.find_first_of(space, clas_head);
    if (space_after_clas == string::npos)
        throw ExBadSyntax();
    size_t clas_size = space_after_clas - clas_head;
    
    size_t type_head = s.find_first_not_of(space, space_after_clas);
    if (type_head == string::npos)
        throw ExBadSyntax();
    size_t space_after_type = s.find_first_of(space, type_head);
    if (space_after_type == string::npos)
        throw ExBadSyntax();
    size_t type_size = space_after_type - type_head;
    
    size_t rdata_head = s.find_first_not_of(space, space_after_type);
    if (rdata_head == string::npos)
        throw ExBadSyntax();
    size_t end_of_rdata = s.size()-1;
    size_t rdata_size = end_of_rdata - rdata_head +1;
    if (rdata_size == 0)
        throw ExBadSyntax();
    
    string name_str  = s.substr(name_head,  name_size);
    string type_str  = s.substr(type_head,  type_size);
    string clas_str  = s.substr(clas_head,  clas_size);
    string ttl_str   = s.substr(ttl_head,   ttl_size);
    string rdata_str = s.substr(rdata_head, rdata_size);

    Type const & type = Type::fromName(type_str);
    Clas const & clas = Clas::IN;
    signed long int ttl = str2int32(ttl_str.c_str());
    
    rrp = new Rr(name_str, type, clas, ttl, rdata_str);
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

Clas const &
Rr::clas() const {
    return d_clas;
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
            Clas const & clas,
            signed long int ttl,
            std::string const & rdata)
:
    d_name(name),
    d_type(type),
    d_clas(clas),
    d_ttl(ttl),
    d_rdata(rdata)
{};

void
Rr::print() const {
    std::cout << "rr{name=" << d_name;
    std::cout << ", ttl="  << d_ttl;
    std::cout << ", clas=" << d_clas.name();
    std::cout << ", type=" << d_type.name();
    std::cout << ", rdata=" << d_rdata;
    std::cout << "}" << std::endl;
}
