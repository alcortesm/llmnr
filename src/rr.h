// This class represents a resource record defined by rfc1035

#ifndef INCLUDED_RR
#define INCLUDED_RR

#include <string>
#include <iostream>

#include "llmnr.h"
#include "type.h"
#include "klass.h"

namespace rr {

    class Rr {

        std::string         const   d_name;
        Type                const & d_type;
        Klass               const & d_klass;
        signed long int     const   d_ttl; // seconds that the resource may be cached
        std::string         const   d_rdata;

        public:

        class ExNoContent {};
        class ExBadSyntax {};
        static Rr       const *  parse(std::string const & s) throw (ExNoContent, ExBadSyntax);

        std::string     const &  name()     const;
        Type            const &  type()     const;
        Klass           const &  klass()    const;
        signed long int          ttl()      const;
        std::string     const &  rdata()    const;
        unsigned short int       rdlength() const; 

        private:
        friend std::ostream & operator<<(std::ostream & s, Rr const & rr);
        Rr(std::string const & name,
                Type const & type,
                Klass const & klass,
                signed long int ttl,
                std::string const & rdata);
    };

}
#endif
