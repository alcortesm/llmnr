#ifndef INCLUDED_RR
#define INCLUDED_RR

#include <string>

#include "llmnr.h"
#include "type.h"

namespace rr {

class Rr {

    std::string         const d_name;
    Type                const d_type;
    unsigned short int  const d_class;
    signed long int     const d_ttl;
    unsigned short int  const d_rdlength;
    std::string         const d_rdata;

public:

    Rr(std::string const & name);
    std::string const & name()  const;
    void                print() const;
};

}
#endif
