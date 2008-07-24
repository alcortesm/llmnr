#include "klass.h"

using rr::Klass;
using std::string;
using std::map;

typedef std::map<std::string const, Klass const *> NameMap;
typedef NameMap::value_type NameMapPair;
typedef std::map<unsigned short, Klass const *> ValueMap;
typedef ValueMap::value_type ValueMapPair;

Klass const Klass::IN = Klass( 1, "IN");
Klass const Klass::CS = Klass( 2, "CS");
Klass const Klass::CH = Klass( 3, "CH");
Klass const Klass::HS = Klass( 4, "HS");

template<typename T, std::size_t z>
std::size_t size(T const (&a)[z]) {
    return z;
}

ValueMapPair const Klass::valueMapInitializer[] = {
    ValueMapPair(Klass::IN.value(), &(Klass::IN)),
    ValueMapPair(Klass::CS.value(), &(Klass::CS)),
    ValueMapPair(Klass::CH.value(), &(Klass::CH)),
    ValueMapPair(Klass::HS.value(), &(Klass::HS))
};
ValueMap const Klass::valueMap(valueMapInitializer, valueMapInitializer + size(valueMapInitializer));

NameMapPair const Klass::nameMapInitializer[] = {
    NameMapPair(Klass::IN.name(), &(Klass::IN)),
    NameMapPair(Klass::CS.name(), &(Klass::CS)),
    NameMapPair(Klass::CH.name(), &(Klass::CH)),
    NameMapPair(Klass::HS.name(), &(Klass::HS)),
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
    s << t.name() ;
    return s;
}

int
rr::operator==(Klass const & a, Klass const & b)
{
    return (&a == &b);
}

int
rr::operator!=(Klass const & a, Klass const & b)
{
    return ! (a == b);
}
