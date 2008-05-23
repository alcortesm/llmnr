#include "clas.h"

using rr::Clas;
using std::string;
using std::map;

typedef std::map<std::string const, Clas const *> NameMap;
typedef NameMap::value_type NameMapPair;
typedef std::map<unsigned short, Clas const *> ValueMap;
typedef ValueMap::value_type ValueMapPair;

Clas const Clas::IN = Clas( 1, "IN");     //RFC 1035 - host address

template<typename T, std::size_t z>
std::size_t size(T const (&a)[z]) {
    return z;
}

ValueMapPair const Clas::valueMapInitializer[] = {
    ValueMapPair(Clas::IN.value(), &(Clas::IN))
};
ValueMap const Clas::valueMap(valueMapInitializer, valueMapInitializer + size(valueMapInitializer));

NameMapPair const Clas::nameMapInitializer[] = {
    NameMapPair(Clas::IN.name(), &(Clas::IN))
};
NameMap const Clas::nameMap(nameMapInitializer, nameMapInitializer + size(nameMapInitializer)); 

Clas::Clas(unsigned short const value, string const & name)
    : d_value(value), d_name(name)
{
};

Clas const &
Clas::fromName(string const & name) throw (Clas::ExNotFound) {
    NameMap::const_iterator it;
    it = Clas::nameMap.find(name);
    if (it == Clas::nameMap.end())
        throw Clas::ExNotFound();
    return *(it->second);
}

Clas const &
Clas::fromValue(unsigned short value) throw (Clas::ExNotFound) {
    ValueMap::const_iterator it;
    it = Clas::valueMap.find(value);
    if (it == Clas::valueMap.end())
        throw Clas::ExNotFound();
    return *(it->second);
}

unsigned short
Clas::value() const {
    return d_value;
}

string const &
Clas::name() const {
    return d_name;
}

std::ostream &
rr::operator<<(std::ostream & s, Clas const & t){
    s << "(" << t.value() << ", " << t.name() << ")";
    return s;
}

