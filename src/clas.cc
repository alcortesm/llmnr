#include <iostream>
#include "clas.h"

using rr::Clas;

Clas const Clas::IN = Clas( 1, "IN"); //RFC 1035 - the Internet

Clas::Clas(unsigned short int const value, std::string const &name)
    : d_value(value), d_name(name) {};

unsigned short int
Clas::value() const {
    return d_value;
}

std::string const &
Clas::name() const {
    return d_name;
}

void
Clas::print() const {
    std::cout << "clas{value=" << d_value;
    std::cout << ", name=" << d_name;
    std::cout << "}" << std::endl;
}

