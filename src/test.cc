#include "rr.h"
#include "rdata.h"
#include "rdataA.h"
#include <cassert>
#include <sstream>
#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>


using std::cout;
using std::cerr;
using std::endl;
using std::ostringstream;
using std::string;
using rr::Rr;
using rr::Type;
using rr::Klass;
using rr::RdataA;
using rr::Rdata;

void
type_test(void)
{
    // test operator ==
    Type const & a = Type::A;
    Type const & b = Type::A;
    assert(a == b);
    assert(a == Type::A);

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
        assert(Type::fromName("A") == Type::A);
    } catch (Type::ExNotFound) {
        cerr << "Type::fromName(\"A\") threw an ExNotFoud" << endl; 
        exit(EXIT_FAILURE);
    }
    try {
        assert(Type::fromValue(1) == Type::A);
    } catch (Type::ExNotFound) {
        cerr << "Type::fromValue(1) threw an ExNotFoud" << endl; 
        exit(EXIT_FAILURE);
    }
    try {
        assert(Type::fromName("NS") == Type::NS);
    } catch (Type::ExNotFound) {
        cerr << "Type::fromName(\"NS\") threw an ExNotFoud" << endl; 
        exit(EXIT_FAILURE);
    }
    try {
        assert(Type::fromValue(2) == Type::NS);
    } catch (Type::ExNotFound) {
        cerr << "Type::fromValue(2) threw an ExNotFoud" << endl; 
        exit(EXIT_FAILURE);
    }
    try {
        assert(Type::fromName("CNAME") == Type::CNAME);
    } catch (Type::ExNotFound) {
        cerr << "Type::fromName(\"CNAME\") threw an ExNotFoud" << endl; 
        exit(EXIT_FAILURE);
    }
    try {
        assert(Type::fromValue(5) == Type::CNAME);
    } catch (Type::ExNotFound) {
        cerr << "Type::fromValue(5) threw an ExNotFoud" << endl; 
        exit(EXIT_FAILURE);
    }
    try {
        assert(Type::fromName("SOA") == Type::SOA);
    } catch (Type::ExNotFound) {
        cerr << "Type::fromName(\"SOA\") threw an ExNotFoud" << endl; 
        exit(EXIT_FAILURE);
    }
    try {
        assert(Type::fromValue(6) == Type::SOA);
    } catch (Type::ExNotFound) {
        cerr << "Type::fromValue(6) threw an ExNotFoud" << endl; 
        exit(EXIT_FAILURE);
    }
    try {
        assert(Type::fromName("PTR") == Type::PTR);
    } catch (Type::ExNotFound) {
        cerr << "Type::fromName(\"PTR\") threw an ExNotFoud" << endl; 
        exit(EXIT_FAILURE);
    }
    try {
        assert(Type::fromValue(12) == Type::PTR);
    } catch (Type::ExNotFound) {
        cerr << "Type::fromValue(12) threw an ExNotFoud" << endl; 
        exit(EXIT_FAILURE);
    }
    try {
        assert(Type::fromName("MX") == Type::MX);
    } catch (Type::ExNotFound) {
        cerr << "Type::fromName(\"MX\") threw an ExNotFoud" << endl; 
        exit(EXIT_FAILURE);
    }
    try {
        assert(Type::fromValue(15) == Type::MX);
    } catch (Type::ExNotFound) {
        cerr << "Type::fromValue(15) threw an ExNotFoud" << endl; 
        exit(EXIT_FAILURE);
    }

    // test the not-found exception of fromName() and fromValue()
    try {
        Type::fromName("foo");
        cerr << "Type::fromName(\"foo\") did not launched an exception" << endl;
        exit(EXIT_FAILURE);
    } catch (Type::ExNotFound) {}
    
    try {
        Type::fromValue(345);
        cerr << "Type::fromValue(345) did not launched an exception" << endl;
        exit(EXIT_FAILURE);
    } catch (Type::ExNotFound) {}

    // test the stream operator overload
    ostringstream oss;
    oss << Type::PTR ;
    assert(oss.str() == "PTR");
}

void
klass_test(void)
{
    // operator ==
    Klass const & a = Klass::IN;
    assert(a == Klass::IN);
    Klass const & b = a;
    assert(a == b);

    // test for value() and name() of the static members
    assert(Klass::IN.value() == 1);
    assert(Klass::IN.name() == "IN");

    // test for fromName() and fromValue() search methods 
    try {
        assert(Klass::fromName("IN") == Klass::IN);
    } catch (Klass::ExNotFound) {
        cerr << "Klass::fromName(\"IN\") threw an ExNotFoud" << endl; 
        exit(EXIT_FAILURE);
    }
    try {
        assert(Klass::fromValue(1) == Klass::IN);
    } catch (Klass::ExNotFound) {
        cerr << "Klass::fromValue(1) threw an ExNotFoud" << endl; 
        exit(EXIT_FAILURE);
    }

    // test the not-found exception of fromName() and fromValue()
    try {
        Klass::fromName("foo");
        cerr << "Klass::fromName(\"foo\") did not throw an exception" << endl;
        exit(EXIT_FAILURE);
    } catch (Klass::ExNotFound) {}
    
    try {
        Klass::fromValue(345);
        cerr << "Klass::fromValue(345) did not throw an exception" << endl;
        exit(EXIT_FAILURE);
    } catch (Klass::ExNotFound) {}

    // test the stream operator overload
    ostringstream oss;
    oss << Klass::IN ;
    assert(oss.str() == "IN");
}

void
rr_test(void)
{
    string const * sp;
    Rr     const * rrp;

    // parse of an empty string must throw ExNoContent
    sp = new string();
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

    // blank string must throw ExNoContent
    sp = new string(" ");
    try {
        rrp = Rr::parse(*sp);
        cerr << "Rr::parse() of a string a space did not launch an exception" << endl ;
        exit(EXIT_FAILURE);
    } catch (Rr::ExNoContent) {
    } catch (Rr::ExBadSyntax) {
        cerr << "Rr::parse() of a string with a space launched ExBadSyntax" << endl ;
        exit(EXIT_FAILURE);
    }
    delete sp;

    sp = new string("	");
    try {
        rrp = Rr::parse(*sp);
        cerr << "Rr::parse() of a string with a tab did not launch an exception" << endl ;
        exit(EXIT_FAILURE);
    } catch (Rr::ExNoContent) {
    } catch (Rr::ExBadSyntax) {
        cerr << "Rr::parse() of a string with a tab launched ExBadSyntax" << endl ;
        exit(EXIT_FAILURE);
    }
    delete sp;

    sp = new string("  	 			   		    	");
    try {
        rrp = Rr::parse(*sp);
        cerr << "Rr::parse() of a string with blanks did not launch an exception" << endl ;
        exit(EXIT_FAILURE);
    } catch (Rr::ExNoContent) {
    } catch (Rr::ExBadSyntax) {
        cerr << "Rr::parse() of a string with blanks launched ExBadSyntax" << endl ;
        exit(EXIT_FAILURE);
    }
    delete sp;

    
    // comments must throw ExNoContent
    sp = new string("#");
    try {
        rrp = Rr::parse(*sp);
        cerr << "Rr::parse() of string \"#\" did not launch an exception" << endl ;
        exit(EXIT_FAILURE);
    } catch (Rr::ExNoContent) {
    } catch (Rr::ExBadSyntax) {
        cerr << "Rr::parse() of string \"#\" launched ExBadSyntax" << endl ;
        exit(EXIT_FAILURE);
    }
    delete sp;

    sp = new string("  	 	#		   		    	");
    try {
        rrp = Rr::parse(*sp);
        cerr << "Rr::parse() of a string with blanks and # did not launch an exception" << endl ;
        exit(EXIT_FAILURE);
    } catch (Rr::ExNoContent) {
    } catch (Rr::ExBadSyntax) {
        cerr << "Rr::parse() of a string with blanks and # launched ExBadSyntax" << endl ;
        exit(EXIT_FAILURE);
    }
    delete sp;

    sp = new string("# this is a comment");
    try {
        rrp = Rr::parse(*sp);
        cerr << "Rr::parse() of a string \"this is a comment\" did not launch an exception" << endl ;
        exit(EXIT_FAILURE);
    } catch (Rr::ExNoContent) {
    } catch (Rr::ExBadSyntax) {
        cerr << "Rr::parse() of a string \"this is a comment\" launched ExBadSyntax" << endl ;
        exit(EXIT_FAILURE);
    }
    delete sp;

    sp = new string(" 	#this is an indented comment");
    try {
        rrp = Rr::parse(*sp);
        cerr << "Rr::parse() of a string \" 	this is an indented comment\" did not launch an exception" << endl ;
        exit(EXIT_FAILURE);
    } catch (Rr::ExNoContent) {
    } catch (Rr::ExBadSyntax) {
        cerr << "Rr::parse() of a string \" 	this is an indented comment\" launched ExBadSyntax" << endl ;
        exit(EXIT_FAILURE);
    }
    delete sp;

    // valid rr
    sp = new string(" 	www.l.google.com.   200 IN  A   64.233.183.99  	");
    try {
        rrp = Rr::parse(*sp);
    } catch (Rr::ExNoContent) {
        cerr << "Rr::parse() of valid string \"   www.l.google.com.   200 IN  A   64.233.183.99   \" launched an ExNoContent" << endl ;
        exit(EXIT_FAILURE);
    } catch (Rr::ExBadSyntax) {
        cerr << "Rr::parse() of a string \"   www.l.google.com.   200 IN  A   64.233.183.99   \" launched ExBadSyntax" << endl ;
        exit(EXIT_FAILURE);
    }
    assert(rrp->name()     == "www.l.google.com.");
    assert(&(rrp->klass()) == &(rr::Klass::IN));
    assert(&(rrp->type())  == &(rr::Type::A));
    assert(rrp->ttl()      == 200);
    assert(rrp->rdata()    == "64.233.183.99");
    
    // test the stream operator overload
    ostringstream oss;
    oss << *rrp;
    assert(oss.str() == "www.l.google.com.\t200\tIN\tA\t64.233.183.99");

    delete rrp;
    delete sp;
}

void
rdataA_test(void)
{
    RdataA const * datap;

    // bac sintax must throw an exception
    try {
        datap = RdataA::parse("hola");
        cerr << "RdataA::parse(\"hola\") did not throw any Exception" << endl;
        exit(EXIT_FAILURE);
    } catch (RdataA::ExBadSyntax) {}

    // streaming a valid addr must give the same as the string from were it was parsed
    // the addr must be the netwrok byte order version of the string
    string s("163.117.141.12");
    try {
        datap = RdataA::parse(s);
    } catch (RdataA::ExBadSyntax) {
        cerr << "RdataA::parse(\"" << s << "\") throws  Rdata::ExBadSyntax" << endl;
        exit(EXIT_FAILURE);
    }
    ostringstream oss;
    oss << *datap;
    assert(oss.str() == s);
    int r;
    const char * cp = s.c_str();
    struct in_addr in;
    r = inet_aton(cp, &in);
    if (r == 0) {
        cerr << "error in test: inet_aton of " << s << " failed!" << endl;
        exit(EXIT_FAILURE);
    }
    assert(in.s_addr == datap->addr());
    assert(Type::A == datap->type());
    assert(Klass::IN == datap->klass());
    assert(RdataA::LENGTH == datap->length());
    delete datap;
}

void
rdata_test(void)
{
    // A records always have 4 octects
    string s("163.117.141.15");
    Rdata const * datap;
    try {
        datap = RdataA::parse(s);
    } catch (RdataA::ExBadSyntax) {
        cerr << "RdataA::parse(\"" << s << "\") throws  Rdata::ExBadSyntax" << endl;
        exit(EXIT_FAILURE);
    }
    assert(datap->length() == RdataA::LENGTH);
    assert(datap->type() == Type::A);
    assert(datap->klass() == Klass::IN);

    // streaming thorugh base class must be the same as through derived calss
    ostringstream oss;
    oss << *datap;
    assert(oss.str() == s);
    delete datap;
}

int
main(int argc, char ** argv) {

    type_test();
    klass_test();
    rdataA_test();
    rdata_test();
    rr_test();

    exit(EXIT_SUCCESS);
}

