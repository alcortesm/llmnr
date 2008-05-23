#include "type.h"
#include <cassert>
#include <sstream>

using std::cout;
using std::cerr;
using std::endl;
using std::ostringstream;
using rr::Type;

int
main(int argc, char ** argv) {

    // test for value() and name() of the static members
    assert(Type::A.value() == 1);
    assert(Type::A.name() == "A");
    assert(Type::NS.value() == 2);
    assert(Type::NS.name() == "NS");
    assert(Type::CNAME.value() == 5);
    assert(Type::CNAME.name() == "CNAME");
    assert(Type::SOA.value() == 6);
    assert(Type::SOA.name() == "SOA");
    assert(Type::PTR.value() == 12);
    assert(Type::PTR.name() == "PTR");
    assert(Type::MX.value() == 15);
    assert(Type::MX.name() == "MX");

    // test for fromName() and fromValue() search methods 
    try {
        assert(&(Type::fromName("A")) == &(Type::A));
    } catch (Type::ExNotFound) {
        cerr << "Type::fromName(\"A\") threw an ExNotFoud" << endl; 
        exit(EXIT_FAILURE);
    }
    try {
        assert(&(Type::fromValue(1)) == &(Type::A));
    } catch (Type::ExNotFound) {
        cerr << "Type::fromValue(1) threw an ExNotFoud" << endl; 
        exit(EXIT_FAILURE);
    }
    try {
        assert(&(Type::fromName("NS")) == &(Type::NS));
    } catch (Type::ExNotFound) {
        cerr << "Type::fromName(\"NS\") threw an ExNotFoud" << endl; 
        exit(EXIT_FAILURE);
    }
    try {
        assert(&(Type::fromValue(2)) == &(Type::NS));
    } catch (Type::ExNotFound) {
        cerr << "Type::fromValue(2) threw an ExNotFoud" << endl; 
        exit(EXIT_FAILURE);
    }
    try {
        assert(&(Type::fromName("CNAME")) == &(Type::CNAME));
    } catch (Type::ExNotFound) {
        cerr << "Type::fromName(\"CNAME\") threw an ExNotFoud" << endl; 
        exit(EXIT_FAILURE);
    }
    try {
        assert(&(Type::fromValue(5)) == &(Type::CNAME));
    } catch (Type::ExNotFound) {
        cerr << "Type::fromValue(5) threw an ExNotFoud" << endl; 
        exit(EXIT_FAILURE);
    }
    try {
        assert(&(Type::fromName("SOA")) == &(Type::SOA));
    } catch (Type::ExNotFound) {
        cerr << "Type::fromName(\"SOA\") threw an ExNotFoud" << endl; 
        exit(EXIT_FAILURE);
    }
    try {
        assert(&(Type::fromValue(6)) == &(Type::SOA));
    } catch (Type::ExNotFound) {
        cerr << "Type::fromValue(6) threw an ExNotFoud" << endl; 
        exit(EXIT_FAILURE);
    }
    try {
        assert(&(Type::fromName("PTR")) == &(Type::PTR));
    } catch (Type::ExNotFound) {
        cerr << "Type::fromName(\"PTR\") threw an ExNotFoud" << endl; 
        exit(EXIT_FAILURE);
    }
    try {
        assert(&(Type::fromValue(12)) == &(Type::PTR));
    } catch (Type::ExNotFound) {
        cerr << "Type::fromValue(12) threw an ExNotFoud" << endl; 
        exit(EXIT_FAILURE);
    }
    try {
        assert(&(Type::fromName("MX")) == &(Type::MX));
    } catch (Type::ExNotFound) {
        cerr << "Type::fromName(\"MX\") threw an ExNotFoud" << endl; 
        exit(EXIT_FAILURE);
    }
    try {
        assert(&(Type::fromValue(15)) == &(Type::MX));
    } catch (Type::ExNotFound) {
        cerr << "Type::fromValue(15) threw an ExNotFoud" << endl; 
        exit(EXIT_FAILURE);
    }

    // test the not-found exception of fromName() and fromValue()
    try {
        assert(&(Type::fromName("foo")) == 0 && false);
    } catch (Type::ExNotFound) {}
    
    try {
        assert(&(Type::fromValue(345)) == 0 && false);
    } catch (Type::ExNotFound) {}

    // test the stream operator overload
    ostringstream oss;
    oss << Type::PTR ;
    assert(oss.str() == "(12, PTR)");

    exit(EXIT_SUCCESS);
}
