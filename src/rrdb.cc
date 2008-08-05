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
    ifs.exceptions(ifstream::failbit | ifstream::badbit);
    string line;
    try {
        ifs.open(path.c_str());
    } catch (ifstream::failure & e) {
        throw ExCanNotReadFile("can not open file");
    }
    try {
        while ( ! ifs.eof()) {
            std::getline(ifs, line);
            std::cout << line << std::endl ;
        }
    } catch (ifstream::failure e) {
        throw ExCanNotReadFile(e.what());
    }
    ifs.close();
}

RrDb::~RrDb()
{}
