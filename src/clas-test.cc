#include "clas.h"
#include <cassert>
#include <sstream>

using std::cout;
using std::cerr;
using std::endl;
using std::ostringstream;
using rr::Clas;

int
main(int argc, char ** argv) {

    // test for value() and name() of the static members
    assert(Clas::IN.value() == 1);
    assert(Clas::IN.name() == "IN");

    // test for fromName() and fromValue() search methods 
    try {
        assert(&(Clas::fromName("IN")) == &(Clas::IN));
    } catch (Clas::ExNotFound) {
        cerr << "Clas::fromName(\"IN\") threw an ExNotFoud" << endl; 
        exit(EXIT_FAILURE);
    }
    try {
        assert(&(Clas::fromValue(1)) == &(Clas::IN));
    } catch (Clas::ExNotFound) {
        cerr << "Clas::fromValue(1) threw an ExNotFoud" << endl; 
        exit(EXIT_FAILURE);
    }

    // test the not-found exception of fromName() and fromValue()
    try {
        assert(&(Clas::fromName("foo")) == 0 && false);
    } catch (Clas::ExNotFound) {}
    
    try {
        assert(&(Clas::fromValue(345)) == 0 && false);
    } catch (Clas::ExNotFound) {}

    // test the stream operator overload
    ostringstream oss;
    oss << Clas::IN ;
    assert(oss.str() == "(1, IN)");

    exit(EXIT_SUCCESS);
}
