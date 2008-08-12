#include "rrdb.h"
#include "rr.h"

#include <fstream>
#include <string>
#include <iostream>

using std::string;
using rr::Rr;
using rr::RrDb;

RrDb::ExBadSyntax::ExBadSyntax(string const & s)
    : invalid_argument(s)
{}

RrDb::ExBadIndex::ExBadIndex(string const & s)
    : invalid_argument(s)
{}

RrDb::ExCanNotReadFile::ExCanNotReadFile(string const & s)
    : invalid_argument(s)
{}


RrDb::RrDb(string const & path) throw(ExBadSyntax, ExCanNotReadFile)
    : d_db()
{
    using std::ifstream;
    ifstream ifs;
    
    ifs.open(path.c_str());
    if (ifs.fail())
        throw ExCanNotReadFile("can not open file");
    
    string line;
    unsigned int ln=0;
    Rr const * rrp;
    struct record record;
    while (true) {
        std::getline(ifs, line);
        if (ifs.eof()) {
            if (! line.size()) break;
        } else if (ifs.fail()) {
            throw ExCanNotReadFile("input error after reading line " + ln);
        }
        ln++;
        try {
            rrp = Rr::parse(line);
        } catch (Rr::ExNoContent & e) { // blank line
            continue;
        } catch (Rr::ExBadSyntax & e) {
            throw RrDb::ExBadSyntax(e.what());
        }
        record.rrp = rrp;
        record.tentative = true;
        d_db.push_back(record);
    }

    ifs.close();
}

RrDb::~RrDb()
{
    for (size_t i=0; i<d_db.size(); i++) {
        delete d_db[i].rrp;
    }
}

Rr const &
RrDb::operator[](uint16_t i) const
{
    return *(d_db[i].rrp);
}

bool
RrDb::isTentative(uint16_t i) const throw (RrDb::ExBadIndex)
{
    if (i > d_db.size()-1)
        throw RrDb::ExBadIndex("index bigger than size");
    return (d_db[i].tentative);
}

size_t
RrDb::size() const
{
    return (size_t) d_db.size();
}

std::ostream &
rr::operator<<(std::ostream & s, RrDb const & rrdb)
{
    for (size_t i=0; i<rrdb.size(); i++) {
        if (rrdb.isTentative(i))
            s << "T : ";
        else
            s << "U : ";
        s << rrdb[i] << std::endl ;
    }
    return s;
}
