// This class represents a DNS resource record type, see
// rfc 1035 for the details.
//
// There are no public constructors, only the static const
// members can be used (Type::A, Type::NS...)

#ifndef INCLUDED_TYPE
#define INCLUDED_TYPE

#include <string>
#include <map>
#include <iostream>

namespace rr {

    class Type {

        unsigned short const d_value;
        std::string    const d_name;

        static std::map<unsigned short, Type const *>      const valueMap;
        static std::map<std::string const, Type const *> const nameMap;

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

        private:
        friend std::ostream & operator<<(std::ostream & s, Type const & t);
        Type(unsigned short const value, std::string const &name);
    };

}
#endif
