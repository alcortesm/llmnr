// This class represents a resource record defined by rfc1035

#ifndef INCLUDED_RR
#define INCLUDED_RR

#include <string>

#include "llmnr.h"
#include "type.h"
#include "clas.h"

namespace rr {

    
    class Rr {

        std::string         const d_name;
        Type                const d_type;
        Clas                const d_clas;
        signed long int     const d_ttl; // seconds that the resource may be cached
        std::string         const d_rdata;

        public:

        class ExNoContent {};
        class ExBadSyntax {};
        static Rr       const *  parse(std::string const & s) throw (ExNoContent, ExBadSyntax);

        std::string     const &  name()     const;
        Type            const &  type()     const;
        Clas            const &  clas()     const;
        signed long int          ttl()      const;
        std::string     const &  rdata()    const;
        unsigned short int       rdlength() const; 

        void                     print()    const;

        private:

        Rr(std::string const & name,
                Type const & type,
                Clas const & clas,
                signed long int ttl,
                std::string const & rdata);
    };

}
#endif
