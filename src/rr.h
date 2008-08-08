// This class represents a resource record defined by rfc1035

#ifndef INCLUDED_RR
#define INCLUDED_RR

#include <string>
#include <iostream>
#include <stdexcept>

#include "llmnr.h"
#include "type.h"
#include "klass.h"
#include "rdata.h"

using rr::Rdata;

namespace rr {

    class Rr {
    
    private:
        std::string         const   d_name;
        Type                const & d_type;
        Klass               const & d_klass;
        signed long int     const   d_ttl;    // seconds that the resource may be cached
        Rdata               const * d_rdatap; // Rdata is an abstract base class, so a pointer is needed

    public:
        class ExNoContent : public std::invalid_argument {
            public:
                ExNoContent(std::string const & s);
        };
        class ExBadSyntax : public std::invalid_argument {
            public:
                ExBadSyntax(std::string const & s);
        };
        static Rr const * parse(std::string const & s) // Named constructor
            throw (ExNoContent, ExBadSyntax);
        ~Rr();

        std::string     const &  name()     const;
        Type            const &  type()     const;
        Klass           const &  klass()    const;
        signed long int          ttl()      const;
        Rdata           const &  rdata()    const;

        private:
        friend std::ostream & operator<<(std::ostream & s, Rr const & rr);
        friend bool operator==(Rr const & a, Rr const & b);
        friend bool operator!=(Rr const & a, Rr const & b);
        Rr(std::string const & name,
                Type const & type,
                Klass const & klass,
                signed long int ttl,
                Rdata const * const rdata);
    };

}
#endif
