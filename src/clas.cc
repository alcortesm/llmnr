#include <iostream>
#include "class.h"

using rr::Class;

Class const Class::IN     = Class( 1, "IN"); //RFC 1035 - the Internet

Class::Class(unsigned short int const value, std::string const &name)
    : d_value(value), d_name(name) {};

unsigned short int
Class::value() const {
    return d_value;
}

std::string const &
Class::name() const {
    return d_name;
}

void
Class::print() const {
    std::cout << "class{value=" << d_value;
    std::cout << ", name=" << d_name;
    std::cout << "}" << std::endl;
}

