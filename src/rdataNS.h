// see RFC1035 section 3.3.11

#ifndef INCLUDED_RDATANS
#define INCLUDED_RDATANS

#include <iostream>
#include <string>
#include "rdata.h"

namespace rr {

    class RdataNS : public rr::Rdata {

        std::string * d_nsdnamep; // A <domain-name> which specifies a host which should be
                                  // authoritative for the specified class and domain.

    public:
        static RdataNS const * parse(std::string const & s) throw (rr::Rdata::ExBadSyntax);
        RdataNS(RdataNS const &);
        RdataNS & operator=(RdataNS const &);
        std::string const & nsdname()  const;
        rr::Type  const & type()       const;
        rr::Klass const & klass()      const;
        ~RdataNS();
    
    private:
        void printOn(std::ostream & s) const ;
        RdataNS(std::string const & nsdname);
    };

}
#endif
