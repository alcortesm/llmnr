#include <iostream>
#include "type.h"

Type const Type::A = Type(1, "A");

Type::Type(unsigned short int const value, std::string const &name)
    : d_value(value), d_name(name) {};

unsigned short int
Type::value() const {
    return d_value;
}

std::string const &
Type::name() const {
    return d_name;
}

void
Type::print() const {
    std::cout << "type{value=" << d_value;
    std::cout << ", name=" << d_name;
    std::cout << "}" << std::endl;
}
