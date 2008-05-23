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
// As class is a reserved word for C++, I will use clas
// instead

#ifndef INCLUDED_CLAS
#define INCLUDED_CLAS

#include <string>
#include <map>
#include <iostream>

namespace rr {

    class Clas {

        unsigned short const d_value;
        std::string    const d_name;

        static std::map<unsigned short, Clas const *>      const valueMap;
        static const std::map<unsigned short, Clas const *>::value_type valueMapInitializer[];
        static std::map<std::string const, Clas const *> const nameMap;
        static const std::map<std::string const, Clas const *>::value_type nameMapInitializer[];

        public:
        unsigned short      value()  const;
        std::string const & name()   const;

        static const Clas IN;

        class ExNotFound {};
        static const Clas & fromValue(unsigned short     value) throw (ExNotFound);
        static const Clas & fromName(std::string const & name)  throw (ExNotFound);

        private:
        friend std::ostream & operator<<(std::ostream & s, Clas const & t);
        Clas(unsigned short const value, std::string const &name);
    };

}
#endif

