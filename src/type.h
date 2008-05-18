#ifndef INCLUDED_TYPE
#define INCLUDED_TYPE

#include <string>

class Type {
    unsigned short int  const d_value;
    std::string         const d_name;
    Type(unsigned short int const value, std::string const &name);
    
public:
    static const Type A;

    unsigned short int  value() const;
    std::string const & name()  const;
    void                print() const;
};

#endif
