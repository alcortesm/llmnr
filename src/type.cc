#include "type.h"

using rr::Type;
using std::string;
using std::map;

typedef std::map<std::string const, Type const *> NameMap;
typedef NameMap::value_type NameMapPair;
typedef std::map<unsigned short, Type const *> ValueMap;
typedef ValueMap::value_type ValueMapPair;

Type const Type::A     = Type( 1, "A");     //RFC 1035 - host address
Type const Type::NS    = Type( 2, "NS");    //RFC 1035 - an authoritative name server
Type const Type::CNAME = Type( 5, "CNAME"); //RFC 1035 - the canonical name for an alias
Type const Type::SOA   = Type( 6, "SOA");   //RFC 1035 - marks the start of a zone of authority
Type const Type::PTR   = Type(12, "PTR");   //RFC 1035 - a domain name pointer
Type const Type::MX    = Type(15, "MX");    //RFC 1035 - mail exchange

template<typename T, std::size_t z>
std::size_t size(T const (&a)[z]) {
    return z;
}

ValueMapPair const Type::valueMapInitializer[] = {
    ValueMapPair(Type::A.value(),     &(Type::A)),
    ValueMapPair(Type::NS.value(),    &(Type::NS)),
    ValueMapPair(Type::CNAME.value(), &(Type::CNAME)),
    ValueMapPair(Type::SOA.value(),   &(Type::SOA)),
    ValueMapPair(Type::PTR.value(),   &(Type::PTR)),
    ValueMapPair(Type::MX.value(),    &(Type::MX))
};
ValueMap const Type::valueMap(valueMapInitializer, valueMapInitializer + size(valueMapInitializer));

NameMapPair const Type::nameMapInitializer[] = {
    NameMapPair(Type::A.name(),     &(Type::A)),
    NameMapPair(Type::NS.name(),    &(Type::NS)),
    NameMapPair(Type::CNAME.name(), &(Type::CNAME)),
    NameMapPair(Type::SOA.name(),   &(Type::SOA)),
    NameMapPair(Type::PTR.name(),   &(Type::PTR)),
    NameMapPair(Type::MX.name(),    &(Type::MX)),
};
NameMap const Type::nameMap(nameMapInitializer, nameMapInitializer + size(nameMapInitializer)); 

Type::Type(unsigned short const value, string const & name)
    : d_value(value), d_name(name)
{
};

Type const &
Type::fromName(string const & name) throw (Type::ExNotFound) {
    NameMap::const_iterator it;
    it = Type::nameMap.find(name);
    if (it == Type::nameMap.end())
        throw Type::ExNotFound();
    return *(it->second);
}

Type const &
Type::fromValue(unsigned short value) throw (Type::ExNotFound) {
    ValueMap::const_iterator it;
    it = Type::valueMap.find(value);
    if (it == Type::valueMap.end())
        throw Type::ExNotFound();
    return *(it->second);
}

unsigned short
Type::value() const {
    return d_value;
}

string const &
Type::name() const {
    return d_name;
}

std::ostream &
rr::operator<<(std::ostream & s, Type const & t){
    s << "(" << t.value() << ", " << t.name() << ")";
    return s;
}
