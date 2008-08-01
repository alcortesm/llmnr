// see RFC1035 section 3.3.9 and RFC974

#ifndef INCLUDED_RDATAMX
#define INCLUDED_RDATAMX

#include <iostream>
#include <string>
#include "rdata.h"

namespace rr {

    class RdataMX : public rr::Rdata {

        unsigned short d_preference; // 16 bits, lower numbers have more preference
        std::string const * d_exchangep; // A <domain-name> which specifies a host willing to
                                        // act as a mail exchange for the owner name.
    
    public:
        static RdataMX const * parse(std::string const & s) throw (rr::Rdata::ExBadSyntax);
        RdataMX(RdataMX const &);
        RdataMX const & operator=(RdataMX const &);
        ~RdataMX();
        unsigned short preference()    const;
        std::string const & exchange() const;
        rr::Type  const & type()       const;
        rr::Klass const & klass()      const;
        friend bool rr::operator==(rr::RdataMX const & a, rr::RdataMX const & b);
        friend bool rr::operator!=(rr::RdataMX const & a, rr::RdataMX const & b);
        bool equals(rr::Rdata const & o) const;
        
        void marshall(char * & offset) const; // offset is advanced
        static RdataMX const * unmarshall(char const * & offset) // offset is advanced
            throw (rr::Rdata::ExBadSyntax);
    
    private:
        static short const PREFERENCE_LENGTH = 2; // preference field is 16 bits = 2 octects
        void printOn(std::ostream & s) const ;
        RdataMX(unsigned short preference, std::string const & exchange);
    };

}
#endif
