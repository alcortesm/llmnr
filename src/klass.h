// This class represents a DNS resource record class, see
// rfc 1035 for the details.
//
// As class is a reserved word for C++, I will use klass
// instead
//
// This class is modeled as a typesafe enum. There is no
// public constructor or public copy-constructor. You
// can ONLY use references to the static const members:
//
// Klass const & a = rr::Klass::IN;
// assert(a == rr::Klass::IN);
//
// You can access the name and value of each static member
// using name() and value():
//
// assert(a.name()  == "IN");
// assert(a.value() == 1);
//
// You can get a reference to the right class by asking
// the fromName() or fromValue(). They throw an exception
// if the name or value is unknown:
//
// try {
//      Klass const & b = rr::Klass::fromName("IN");
// } catch (rr::Klass::ExNotFound) {
//      exit(EXIT_FAILURE);
// }
// assert(a == b);

#ifndef INCLUDED_KLASS
#define INCLUDED_KLASS

#include <string>
#include <map>
#include <iostream>

namespace rr {

    class Klass {

        unsigned short const d_value;
        std::string    const d_name;

        static std::map<unsigned short, Klass const *>    const valueMap;
        static std::map<std::string const, Klass const *> const nameMap;
        static const std::map<unsigned short, Klass const *>::value_type    valueMapInitializer[];
        static const std::map<std::string const, Klass const *>::value_type nameMapInitializer[];

    public:
        static const Klass IN;

        unsigned short      value()  const;
        std::string const & name()   const;

        class ExNotFound {};
        static const Klass & fromValue(unsigned short     value) throw (ExNotFound);
        static const Klass & fromName(std::string const & name)  throw (ExNotFound);
        friend int operator==(Klass const & a, Klass const & b);

    private:
        friend std::ostream & operator<<(std::ostream & s, Klass const & t);
        void operator=(Klass const & t);
        void operator&(Klass const & t);
        Klass(unsigned short const value, std::string const &name);
        Klass(Klass const & k);
    };

}
#endif

