#include "rr.h"
#include "type.h"
#include "clas.h"

#include <iostream>

using std::string;
using rr::Rr;
using rr::Type;
using rr::Clas;

Rr const *
Rr::parse(string const & s) {
    return new Rr("name", Type::A, Clas::IN, 100, "rdata");
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

signed long int const
Rr::ttl() const {
    return d_ttl;
}

std::string const &
Rr::rdata() const {
    return d_rdata;
}

unsigned short int const
Rr::rdlength() const {
//    return (unsigned short int const) (d_rdata.length);
    return 0;
}

Rr::Rr(std::string const & name,
            Type const & type,
            Clas const & clas,
            signed long int const ttl,
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
    std::cout << ", type=" << d_type.name();
    std::cout << ", clas=" << d_clas.name();
    std::cout << ", ttl="  << d_ttl;
    std::cout << ", rdlength=" << this->rdlength();
    std::cout << ", rdata=" << d_rdata;
    std::cout << "}" << std::endl;
}
