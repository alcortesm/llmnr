#include "rrdb.h"
#include "rr.h"

#include <fstream>
#include <string>
#include <iostream>

using std::string;
using rr::Rr;
using rr::RrDb;

RrDb::ExBadSyntax::ExBadSyntax(unsigned int line)
    : d_line(line)
{}

unsigned int const
RrDb::ExBadSyntax::line()
{
    return d_line;
}

RrDb::ExCanNotReadFile::ExCanNotReadFile(string const & diag)
    : d_diag(diag)
{}

string const &
RrDb::ExCanNotReadFile::diag()
{
    return d_diag;
}

RrDb::RrDb(string const & path) throw(ExBadSyntax, ExCanNotReadFile)
    : d_size(0), d_db()
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
        std::clog << ln << ": " << line << std::endl ;
        try {
            rrp = Rr::parse(line);
        } catch (Rr::ExNoContent & e) { // blank line
            continue;
        } catch (Rr::ExBadSyntax & e) {
            throw ExBadSyntax(ln);
        }
        record.rrp = rrp;
        record.tentative = true;
        d_db.push_back(&record);
        delete(rrp);
    }

    ifs.close();
}

RrDb::~RrDb()
{}

Rr const &
RrDb::operator[](unsigned int i) const
{
    return *((d_db[i])->rrp);
}

unsigned int
RrDb::size() const
{
    return d_db.size();
}

std::ostream &
operator<<(std::ostream & s, RrDb const & rrdb)
{
    for (unsigned int i=0; i<rrdb.size(); i++)
        s << rrdb[i] << std::endl ;
    return s;
}
