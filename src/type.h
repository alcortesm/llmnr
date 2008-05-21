// This class represents a DNS resource record type, see
// rfc 1035 for the details.
//
// There are no public constructors, only the static const
// members can be used (Type::A, Type::NS...)

#ifndef INCLUDED_TYPE
#define INCLUDED_TYPE

#include <string>
#include <vector>

namespace rr {

class Type {

    static Type const db[];
    
    unsigned short int  const d_value;
    std::string         const d_name;
    Type(unsigned short int const value, std::string const &name);
    
public:
    static const Type A;
    static const Type NS;
    static const Type CNAME;
    static const Type SOA;
    static const Type PTR;
    static const Type MX;
    static const Type & fromName(std::string const & name);
    static const Type & fromValue(unsigned short int value);

    unsigned short int  value() const;
    std::string const & name()  const;
    void                print() const;
};

}
#endif
