#include "klass.h"

using rr::Klass;
using std::string;
using std::map;

typedef std::map<std::string const, Klass const *> NameMap;
typedef NameMap::value_type NameMapPair;
typedef std::map<unsigned short, Klass const *> ValueMap;
typedef ValueMap::value_type ValueMapPair;

Klass const Klass::IN = Klass( 1, "IN");     //RFC 1035 - host address

template<typename T, std::size_t z>
std::size_t size(T const (&a)[z]) {
    return z;
}

ValueMapPair const Klass::valueMapInitializer[] = {
    ValueMapPair(Klass::IN.value(), &(Klass::IN))
};
ValueMap const Klass::valueMap(valueMapInitializer, valueMapInitializer + size(valueMapInitializer));

NameMapPair const Klass::nameMapInitializer[] = {
    NameMapPair(Klass::IN.name(), &(Klass::IN))
};
NameMap const Klass::nameMap(nameMapInitializer, nameMapInitializer + size(nameMapInitializer)); 

Klass::Klass(unsigned short const value, string const & name)
    : d_value(value), d_name(name)
{
};

Klass const &
Klass::fromName(string const & name) throw (Klass::ExNotFound) {
    NameMap::const_iterator it;
    it = Klass::nameMap.find(name);
    if (it == Klass::nameMap.end())
        throw Klass::ExNotFound();
    return *(it->second);
}

Klass const &
Klass::fromValue(unsigned short value) throw (Klass::ExNotFound) {
    ValueMap::const_iterator it;
    it = Klass::valueMap.find(value);
    if (it == Klass::valueMap.end())
        throw Klass::ExNotFound();
    return *(it->second);
}

unsigned short
Klass::value() const {
    return d_value;
}

string const &
Klass::name() const {
    return d_name;
}

std::ostream &
rr::operator<<(std::ostream & s, Klass const & t){
    s << "(" << t.value() << ", " << t.name() << ")";
    return s;
}

