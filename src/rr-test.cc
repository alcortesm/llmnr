#include "rr.h"
#include <cassert>
#include <sstream>
#include <string>

using std::cout;
using std::cerr;
using std::endl;
using std::ostringstream;
using rr::Rr;
using std::string;

int
main(int argc, char ** argv) {

    string const * sp;

    // parse of an empty string must throw ExNoContent
    sp = new string();
    Rr const * rrp;
    try {
        rrp = Rr::parse(*sp);
        cerr << "Rr::parse() of an empty string did not launch an exception" << endl ;
        exit(EXIT_FAILURE);
    } catch (Rr::ExNoContent) {
    } catch (Rr::ExBadSyntax) {
        cerr << "Rr::parse() of an empty string launched ExBadSyntax" << endl ;
        exit(EXIT_FAILURE);
    }
    delete sp;


    exit(EXIT_SUCCESS);
}

