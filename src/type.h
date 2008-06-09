// This class represents a DNS resource record type, see
// rfc 1035 for the details.
//
// This class is modeled as a typesafe enum. There is no
// public constructor or public copy-constructor. You
// can ONLY use references to the static const members:
//
// Type const & a = rr::Type::A;
// assert(a == rr::Type::A);
//
// You can access the name and value of each static member
// using name() and value().
//
// assert(a.name() == "A");
// assert(a.value() == 1);
//
// You can get a reference to the right types by asking
// the fromName() or fromValue(). They throw an exception
// if the name or value is unknown.
//
// try {
//      Type const & b = rr::Type::fromName("A");
// } catch (rr::Type::ExNotFound) {
//      exit(EXIT_FAILURE);
// }
// assert(a == b);

#ifndef INCLUDED_TYPE
#define INCLUDED_TYPE

#include <string>
#include <map>
#include <iostream>

namespace rr {

    class Type {

        unsigned short const d_value;
        std::string    const d_name;

        static std::map<unsigned short, Type const *> const valueMap;
        static std::map<unsigned short, Type const *>::value_type const valueMapInitializer[];
        static std::map<std::string const, Type const *> const nameMap;
        static std::map<std::string const, Type const *>::value_type const nameMapInitializer[];

        public:
        unsigned short      value()  const;
        std::string const & name()   const;

        static const Type A;
        static const Type NS;
        static const Type CNAME;
        static const Type SOA;
        static const Type PTR;
        static const Type MX;

        class ExNotFound {};
        static const Type & fromValue(unsigned short     value) throw (ExNotFound);
        static const Type & fromName(std::string const & name)  throw (ExNotFound);
        friend int operator==(Type const & a, Type const & b);

        private:
        friend std::ostream & operator<<(std::ostream & s, Type const & t);
        void operator=(Type const & t);
        void operator&(Type const & t);
        Type(unsigned short const value, std::string const &name);
        Type(Type const & t);
    };

}
#endif
