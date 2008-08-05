// resource record data base: filled from the configuration file
//
// Each record comes with an additional "tentative" bit.
// The maximun size of the DB is given by the index used, that is
// unsigned ints (at least (2^16)-1).

#ifndef INCLUDED_RRDB
#define INCLUDED_RRDB

#include <string>
#include <vector>

#include "rr.h"

namespace rr {
    
    class RrDb {
    public:
        class ExBadSyntax {
        private:
            unsigned int const d_line;
        public:
            ExBadSyntax(unsigned int line);
            unsigned int const line();
        };
        class ExBadIndex {};
        class ExCanNotReadFile {
        private:
            std::string const d_diag;
        public:
            ExCanNotReadFile(std::string const & diag);
            std::string const & diag();
        };

        RrDb(std::string const & path) throw (ExBadSyntax, ExCanNotReadFile);
        ~RrDb();
        bool isEmpty();
        bool isTentative(unsigned int index) throw (ExBadIndex);
        void setTentative(unsigned int index, bool tentative = true) throw (ExBadIndex);
        unsigned int size();
    private:
        unsigned int d_size; // number of records
        struct record {
            rr::Rr * rr;
            bool     tentative;
        };
        std::vector<struct record *> d_db;
    };
}
#endif
