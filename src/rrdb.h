// resource record data base: filled from the configuration file
//
// Each record comes with an additional "tentative" bit.
// The maximun size of the DB is given by the index used, that is
// unsigned ints (at least (2^16)-1).

#ifndef INCLUDED_RRDB
#define INCLUDED_RRDB

#include <string>
#include <vector>
#include <stdexcept>

#include "rr.h"

namespace rr {
    
    class RrDb {
    private:
        unsigned int d_size; // number of records
        struct record {
            rr::Rr const * rrp;
            bool     tentative;
        };
        std::vector<struct record *> d_db;
    public:
        class ExBadSyntax : public std::invalid_argument {
            public:
                ExBadSyntax(std::string const & s);
        };
        class ExBadIndex : public std::invalid_argument {
            public:
                ExBadIndex(std::string const & s);
        };
        class ExCanNotReadFile : public std::invalid_argument {
            public:
                ExCanNotReadFile(std::string const & s);
        };

        RrDb(std::string const & path) throw (ExBadSyntax, ExCanNotReadFile);
        ~RrDb();
        bool isEmpty() const;
        bool isTentative(unsigned int index) const throw (ExBadIndex);
        void setTentative(unsigned int index, bool tentative = true) throw (ExBadIndex);
        unsigned int size() const;
        rr::Rr const & operator[](unsigned int) const;
    private:
        friend std::ostream & operator<<(std::ostream & s, RrDb const & rrdb);
    };
}
#endif
