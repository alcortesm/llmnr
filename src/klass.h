// This class represents a DNS resource record class, see
// rfc 1035 for the details.
//
// This class is modeled as a typesafe enum. There are no
// public constructors. You should use the static const
// members instead.
//
// You can access the name and value of each static member
// using name() and value().
//
// You can get a reference to the right class by asking
// the fromName() or fromValue(). They throw an exception
// if the name or value is unknown.
//
// As class is a reserved word for C++, I will use klass
// instead

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
        unsigned short      value()  const;
        std::string const & name()   const;

        static const Klass IN;

        class ExNotFound {};
        static const Klass & fromValue(unsigned short     value) throw (ExNotFound);
        static const Klass & fromName(std::string const & name)  throw (ExNotFound);

        private:
        friend std::ostream & operator<<(std::ostream & s, Klass const & t);
        Klass(unsigned short const value, std::string const &name);
    };

}
#endif

