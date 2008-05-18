#ifndef INCLUDED_CLASS
#define INCLUDED_CLASS

#include <string>

namespace rr {

class Clas {
    unsigned short int  const d_value;
    std::string         const d_name;
    Clas(unsigned short int const value, std::string const &name);
    
public:
    static const Clas IN;

    unsigned short int  value() const;
    std::string const & name()  const;
    void                print() const;
};

}
#endif

