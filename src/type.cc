#include <iostream>
#include "type.h"

using rr::Type;

Type const Type::A     = Type( 1, "A");     //RFC 1035 - host address
Type const Type::NS    = Type( 2, "NS");    //RFC 1035 - an authoritative name server
Type const Type::CNAME = Type( 5, "CNAME"); //RFC 1035 - the canonical name for an alias
Type const Type::SOA   = Type( 6, "SOA");   //RFC 1035 - marks the start of a zone of authority
Type const Type::PTR   = Type(12, "PTR");   //RFC 1035 - a domain name pointer
Type const Type::MX    = Type(15, "MX");    //RFC 1035 - mail exchange

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
