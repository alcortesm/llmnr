// resource record data base: comes from the configuration file
//
// Each record comes with an additional "tentative" bit.
// The maximun size of the DB is given by the index used, that is
// unsigned ints (at least (2^16)-1).

#ifndef INCLUDED_RRDB
#define INCLUDED_RRDB

namespace rr {
    
    struct record {
        rr::Rr  rr;
        bool    tentative;
    };

    class RrDb {
    public:
        class ExNoSuchRecord {};
        class ExBadIndex {};
        RrDb(string & path) throw (ExBadSyntax);
        ~RrDb();
        bool isEmpty();
        bool isTentative(unsigned int index); throw (ExBadIndex)
        void setTentative(unsigned int index, bool tentative = true) throw (ExBadIndex);
    private:
        unsigned int size;
        std::vector<rr::record>;
    };
}
#endif
