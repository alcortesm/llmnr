#include "util.h"
#include "rr.h"
#include "rdata.h"
#include "rdataA.h"
#include "rdataMX.h"
#include "rdataNS.h"

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
using rr::RdataMX;
using rr::RdataNS;
using rr::Rdata;

void
util_test(void)
{
    { // test for LD consistency
        string ld(util::LETTER);
        ld.append(util::DIGIT);
        assert(ld.compare(util::LD) == 0);
    }
    
    { // test for LDH consistency
        string ldh(util::LD);
        ldh.append(util::HYP);
        assert(ldh.compare(util::LDH) == 0);
    }

    // MIN_SLONG and MIN_SLONG
    assert(util::MIN_SLONG == -2147483647);
    assert(util::MAX_SLONG == 2147483647);

    { // str2sint32
        signed long slong;
        string minslong("-2147483647");
        try {
            slong = util::str2sint32(minslong);
            assert(slong == util::MIN_SLONG);
        } catch (string & s) {
            cerr << "str2sint32(\"" << minslong << "\") throws \"" << s << "\"" << endl;
            exit(EXIT_FAILURE);
        }

        string maxslong("2147483647");
        try {
            slong = util::str2sint32(maxslong);
            assert(slong == util::MAX_SLONG);
        } catch (string & s) {
            cerr << "str2sint32(\"" << maxslong << "\") throws \"" << s << "\"" << endl;
            exit(EXIT_FAILURE);
        }

        try {
            slong = util::str2sint32("-2147483648");
            assert(false && "util::str2sint32(\"-2147483648\") must have throw an exception and did not");
        } catch (string & s) {}
        
        try {
            slong = util::str2sint32("2147483648");
            assert(false && "util::str2sint32(\"2147483648\") must have throw an exception and did not");
        } catch (string & s) {}
        
        try {
            slong = util::str2sint32("0");
            assert(slong == 0);
        } catch (string & s) {
            cerr << "str2sint32(\"0\") throws \"" << s << "\"" << endl;
            exit(EXIT_FAILURE);
        }
    
        try {
            slong = util::str2sint32("234");
            assert(slong == 234);
        } catch (string & s) {
            cerr << "str2sint32(\"234\") throws \"" << s << "\"" << endl;
            exit(EXIT_FAILURE);
        }
    }

    // MIN_USHORT and MIN_USHORT
    assert(util::MIN_USHORT == 0);
    assert(util::MAX_USHORT == 65535);

    { // str2uint16
        unsigned short ushort;
        string minushort("0");
        try {
            ushort = util::str2uint16(minushort);
            assert(ushort == util::MIN_USHORT);
        } catch (string & s) {
            cerr << "str2uint16(\"" << minushort << "\") throws \"" << s << "\"" << endl;
            exit(EXIT_FAILURE);
        }
       
        string maxushort("65535");
        try {
            ushort = util::str2uint16(maxushort);
            assert(ushort == util::MAX_USHORT);
        } catch (string & s) {
            cerr << "str2uint16(\"" << maxushort << "\") throws \"" << s << "\"" << endl;
            exit(EXIT_FAILURE);
        }

        try {
            ushort = util::str2uint16("-1");
            assert(false && "util::str2uint16(\"-1\") must have throw an exception and did not");
        } catch (string & s) {}
        
        try {
            ushort = util::str2uint16("65536");
            assert(false && "util::str2uint16(\"65536\") must have throw an exception and did not");
        } catch (string & s) {}
       
        try {
            ushort = util::str2uint16("234");
            assert(ushort == 234);
        } catch (string & s) {
            cerr << "str2uint16(\"234\") throws \"" << s << "\"" << endl;
            exit(EXIT_FAILURE);
        }
    }

    { // isLabel
        bool r;
        string const * sp;

        sp = new string("hola");
        r = util::isLabel(*sp);
        delete sp;
        assert(r && "isLabel(hola)");
        
        sp = new string("h12o-la");
        r = util::isLabel(*sp);
        delete sp;
        assert(r && "isLabel(h12o-la)");
        
        sp = new string("h12.o-la");
        r = util::isLabel(*sp);
        delete sp;
        assert(!r && "isLabel(h12.o-la)");
        
        sp = new string("2h12o-la");
        r = util::isLabel(*sp);
        delete sp;
        assert(!r && "isLabel(2h12o-la)");
        
        sp = new string("-h12o-la");
        r = util::isLabel(*sp);
        delete sp;
        assert(!r && "isLabel(-12o-la)");
            
        sp = new string("h12o-la-");
        r = util::isLabel(*sp);
        delete sp;
        assert(!r && "isLabel(h12o-la-)");
        
        sp = new string("h12o-la3");
        r = util::isLabel(*sp);
        delete sp;
        assert(r && "isLabel(h12o-la3)");

        sp = new string(" ");
        r = util::isLabel(*sp);
        delete sp;
        assert(!r && "isLabel(\" \")");

        sp = new string("");
        r = util::isLabel(*sp);
        delete sp;
        assert(!r && "isLabel(\"\")");

        sp = new string("a23456789012345678901234567890123456789012345678901234567890123");
        r = util::isLabel(*sp);
        delete sp;
        assert(r && "isLabel(63 octetos)");

        sp = new string("1234567890123456789012345678901234567890123456789012345678901234");
        r = util::isLabel(*sp);
        delete sp;
        assert(!r && "isLabel(64 octetos)");

        sp = new string("it.uc3m.es.foo.bar");
        r = util::isLabel(*sp, 11, 3);
        delete sp;
        assert(r && "isLabel(it.uc3m.es.foo.bar, 11, 3)");
    }

    { // isDomainName
        string * sp;
        sp = new string("");
        int r;
        r = util::isDomainName(*sp);
        delete sp;
        assert(!r && "isDomainName(\"\")");

        sp = new string("a2345678901234567890123456789012345678901234567890123456789.a2345678901234567890123456789012345678901234567890123456789.a2345678901234567890123456789012345678901234567890123456789.a2345678901234567890123456789012345678901234567890123456789.a23456789012345");
        r = util::isDomainName(*sp);
        delete sp;
        assert(r && "isDomainName(255 octetos)");

        sp = new string("a2345678901234567890123456789012345678901234567890123456789.a2345678901234567890123456789012345678901234567890123456789.a2345678901234567890123456789012345678901234567890123456789.a2345678901234567890123456789012345678901234567890123456789.a234567890123456");
        r = util::isDomainName(*sp);
        delete sp;
        assert(!r && "isDomainName(256 octetos)");

        sp = new string(" ");
        r = util::isDomainName(*sp);
        delete sp;
        assert(r && "isDomainName(\" \")");

        sp = new string("it");
        r = util::isDomainName(*sp);
        delete sp;
        assert(r && "isDomainName(it)");

        sp = new string("it.uc3m");
        r = util::isDomainName(*sp);
        delete sp;
        assert(r && "isDomainName(it.uc3m)");

        sp = new string("it.uc3m.es.foo.bar");
        r = util::isDomainName(*sp);
        delete sp;
        assert(r && "isDomainName(it.uc3m.es.foo.bar)");

        sp = new string(".");
        r = util::isDomainName(*sp);
        delete sp;
        assert(!r && "isDomainName(.)");

        sp = new string("it.uc3m.es.");
        r = util::isDomainName(*sp);
        delete sp;
        assert(!r && "isDomainName(it.uc3m.es.)");

        sp = new string("it.uc3m..es");
        r = util::isDomainName(*sp);
        delete sp;
        assert(!r && "isDomainName(it.uc3m..es)");

        sp = new string("it.uc3m.es..");
        r = util::isDomainName(*sp);
        delete sp;
        assert(!r && "isDomainName(it.uc3m.es..)");

        sp = new string("it.uc3m...es");
        r = util::isDomainName(*sp);
        delete sp;
        assert(!r && "isDomainName(it.uc3m...es)");

        sp = new string("it.uc3m.es...");
        r = util::isDomainName(*sp);
        delete sp;
        assert(!r && "isDomainName(it.uc3m.es...)");

        sp = new string("it.bla.a234567890123456789012345678901234567890123456789012345678901234.uc3m.es");
        r = util::isDomainName(*sp);
        delete sp;
        assert(!r && "isDomainName(it.bla.a234567890123456789012345678901234567890123456789012345678901234.uc3m.es)");

        sp = new string("a234567890123456789012345678901234567890123456789012345678901234.uc3m.es");
        r = util::isDomainName(*sp);
        delete sp;
        assert(!r && "isDomainName(a234567890123456789012345678901234567890123456789012345678901234.uc3m.es)");

        sp = new string("it.bla.a234567890123456789012345678901234567890123456789012345678901234");
        r = util::isDomainName(*sp);
        delete sp;
        assert(!r && "isDomainName(it.bla.a234567890123456789012345678901234567890123456789012345678901234)");
    }

    { // dnsname2buf and buf2dnsname
        {
            string const s = "it.uc3m.es";
            size_t const buf_sz = 12;
            char const buf[buf_sz] = {'\x02', 'i', 't', '\x04', 'u', 'c', '3', 'm', '\x02', 'e', 's', '\x00'};

            char tmp[100];
            char * offset = tmp;
            util::dnsname2buf(s, offset);
            assert(memcmp(buf, tmp, buf_sz) == 0);
            assert(offset-tmp == (ssize_t) buf_sz);

            string * sp;
            char const * oo = tmp;
            try {
                sp = util::buf2dnsname(oo);
            } catch (string & ex) {
                cerr << "util::buf2dnsname throws exception: " << ex << endl;
                exit(EXIT_FAILURE);
            }
            assert(s.compare(*sp) == 0);
            assert(oo-tmp == (ssize_t) buf_sz);
            delete sp;
        }
        {
            string const s("a2345678901234567890123456789012345678901234567890123456789.a2345678901234567890123456789012345678901234567890123456789.a2345678901234567890123456789012345678901234567890123456789.a2345678901234567890123456789012345678901234567890123456789.a23456789012345");
            char tmp[500];
            char * offset = tmp;
            util::dnsname2buf(s, offset);

            string const aux(tmp);
            assert(offset-tmp == (ssize_t) aux.size() + 1);

            string * sp;
            char const * oo = tmp;
            try {
                sp = util::buf2dnsname(oo);
            } catch (string & ex) {
                cerr << "util::buf2dnsname throws exception: " << ex << endl;
                exit(EXIT_FAILURE);
            }
            assert(s.compare(*sp) == 0);
            assert(oo-tmp == (ssize_t) aux.size() + 1);
            delete sp;
        }
        {
            string const s("a2345678901234567890123456789012345678901234567890123456789.a2345678901234567890123456789012345678901234567890123456789.a2345678901234567890123456789012345678901234567890123456789.a2345678901234567890123456789012345678901234567890123456789.a234567890123456");
            char tmp[500];
            char * offset = tmp;
            util::dnsname2buf(s, offset); // s is a bad formed dns name (too long) but we write it anyway

            string const aux(tmp);
            assert(offset-tmp == (ssize_t) aux.size() + 1);

            string * sp;
            char const * oo = tmp;
            try {
                sp = util::buf2dnsname(oo);
                cerr << "util::buf2dnsname didn't throw a 'too long data' exception" << endl;
                exit(EXIT_FAILURE);
            } catch (string & ex) {
                // OK
            }
        }
    }
}

void
type_test(void)
{
    { // test operator ==
        Type const & a = Type::A;
        Type const & b = Type::A;
        Type const & c = Type::NS;

        assert(a == a);
        assert(a == b);
        assert(a == Type::A);
        assert((a == c) == false);
        assert((c == a) == false);
        assert((b == c) == false);
        assert((c == b) == false);
        
        assert((a != a) == false);
        assert((a != b) == false);
        assert((a != Type::A) == false);
        assert(a != c);
        assert(c != a);
        assert(b != c);
        assert(c != b);
    }

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

    { // test the stream operator overload
        ostringstream oss;
        oss << Type::PTR ;
        assert(oss.str() == "PTR");
    }
}

void
klass_test(void)
{
    { // operator== and operator !=
        Klass const & a = Klass::IN;
        Klass const & b = a;
        Klass const & c = Klass::CS;

        assert(a == a);
        assert(a == Klass::IN);
        assert(c == Klass::CS);
        assert(Klass::IN == a);
        assert(a == b);
        assert(b == b);
        assert(!(a == c));
        assert(!(c == Klass::IN));

        assert(a != c);
        assert(c != a);
        assert(c != Klass::IN);
        assert(Klass::IN != c);
    }

    // test for value() and name() of the static members
    assert(Klass::IN.value() == 1);
    assert(Klass::IN.name() == "IN");
    assert(Klass::CS.value() == 2);
    assert(Klass::CS.name() == "CS");
    assert(Klass::CH.value() == 3);
    assert(Klass::CH.name() == "CH");
    assert(Klass::HS.value() == 4);
    assert(Klass::HS.name() == "HS");

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
    try {
        assert(Klass::fromName("CS") == Klass::CS);
    } catch (Klass::ExNotFound) {
        cerr << "Klass::fromName(\"CS\") threw an ExNotFoud" << endl; 
        exit(EXIT_FAILURE);
    }
    try {
        assert(Klass::fromValue(2) == Klass::CS);
    } catch (Klass::ExNotFound) {
        cerr << "Klass::fromValue(2) threw an ExNotFoud" << endl; 
        exit(EXIT_FAILURE);
    }
    try {
        assert(Klass::fromName("CH") == Klass::CH);
    } catch (Klass::ExNotFound) {
        cerr << "Klass::fromName(\"CH\") threw an ExNotFoud" << endl; 
        exit(EXIT_FAILURE);
    }
    try {
        assert(Klass::fromValue(3) == Klass::CH);
    } catch (Klass::ExNotFound) {
        cerr << "Klass::fromValue(3) threw an ExNotFoud" << endl; 
        exit(EXIT_FAILURE);
    }
    try {
        assert(Klass::fromName("HS") == Klass::HS);
    } catch (Klass::ExNotFound) {
        cerr << "Klass::fromName(\"HS\") threw an ExNotFoud" << endl; 
        exit(EXIT_FAILURE);
    }
    try {
        assert(Klass::fromValue(4) == Klass::HS);
    } catch (Klass::ExNotFound) {
        cerr << "Klass::fromValue(4) threw an ExNotFoud" << endl; 
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

    { // test the stream operator overload
        {
            ostringstream oss;
            oss << Klass::IN ;
            assert(oss.str() == "IN");
        }
        {
            ostringstream oss;
            oss << Klass::CS ;
            assert(oss.str() == "CS");
        }
        {
            ostringstream oss;
            oss << Klass::CH ;
            assert(oss.str() == "CH");
        }
        {
            ostringstream oss;
            oss << Klass::HS ;
            assert(oss.str() == "HS");
        }
    }
}

void
rr_test(void)
{
    { // parse of an empty string must throw ExNoContent
        string const * sp;
        Rr     const * rrp;
        sp = new string();
        try {
            rrp = Rr::parse(*sp);
            cerr << "Rr::parse() of an empty string did not launch an exception" << endl ;
            exit(EXIT_FAILURE);
        } catch (Rr::ExNoContent) {
            // OK
        } catch (Rr::ExBadSyntax) {
            cerr << "Rr::parse() of an empty string launched ExBadSyntax" << endl ;
            exit(EXIT_FAILURE);
        }
        delete sp;
    }

    { // blank string must throw ExNoContent
        string const * sp;
        Rr     const * rrp;
        sp = new string(" ");
        try {
            rrp = Rr::parse(*sp);
            cerr << "Rr::parse() of a string a space did not launch an exception" << endl ;
            exit(EXIT_FAILURE);
        } catch (Rr::ExNoContent) {
            // OK
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
            // OK
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
            // OK
        } catch (Rr::ExBadSyntax) {
            cerr << "Rr::parse() of a string with blanks launched ExBadSyntax" << endl ;
            exit(EXIT_FAILURE);
        }
        delete sp;
    }

    { // comments must throw ExNoContent
        string const * sp;
        Rr     const * rrp;
        sp = new string("#");
        try {
            rrp = Rr::parse(*sp);
            cerr << "Rr::parse() of string \"#\" did not launch an exception" << endl ;
            exit(EXIT_FAILURE);
        } catch (Rr::ExNoContent) {
            // OK
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
            // OK
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
            // OK
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
            // OK
        } catch (Rr::ExBadSyntax) {
            cerr << "Rr::parse() of a string \" 	this is an indented comment\" launched ExBadSyntax" << endl ;
            exit(EXIT_FAILURE);
        }
        delete sp;
    }

    { // valid rr
        string const * sp;
        Rr     const * rrp;

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
        
        delete sp;
        delete rrp;
    }

    { // test the stream operator overload
        string const * sp;
        Rr     const * rrp;

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
        ostringstream oss;
        oss << *rrp;
        assert(oss.str() == "www.l.google.com.\t200\tIN\tA\t64.233.183.99");
        
        delete sp;
        delete rrp;
    }

}

void
rdataA_test(void)
{
    { // bad sintax must throw an exception
        RdataA const * datap;
        try {
            datap = RdataA::parse("hola");
            cerr << "RdataA::parse(\"hola\") did not throw any Exception" << endl;
            exit(EXIT_FAILURE);
        } catch (Rdata::ExBadSyntax) {}
    }


    { // streaming a valid addr must give the same as the string from were it was parsed
        // the addr must be the netwrok byte order version of the string
        RdataA const * datap;
        string s("163.117.141.12");
        try {
            datap = RdataA::parse(s);
        } catch (Rdata::ExBadSyntax) {
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

    { // comparison
        RdataA const * ap;
        RdataA const * bp;
        RdataA const * cp;
        ap = RdataA::parse("1.2.3.4");
        bp = RdataA::parse("1.2.3.4");
        cp = RdataA::parse("1.5.3.4");

        assert(*ap == *ap);
        assert(*bp == *bp);
        assert(*cp == *cp);
        assert(*ap == *bp);
        assert(*bp == *ap);
        assert((*ap == *cp) == false);
        assert((*cp == *ap) == false);
        assert((*cp == *bp) == false);
        assert((*bp == *cp) == false);

        assert((*ap != *ap) == false);
        assert((*bp != *bp) == false);
        assert((*cp != *cp) == false);
        assert((*ap != *bp) == false);
        assert((*bp != *ap) == false);
        assert(*ap != *cp);
        assert(*cp != *ap);
        assert(*cp != *bp);
        assert(*bp != *cp);

        delete ap;
        delete bp;
        delete cp;
    }


    { //marshalling
        RdataA const * datap;
        string s("163.117.141.12");
        try {
            datap = RdataA::parse(s);
        } catch (Rdata::ExBadSyntax) {
            cerr << "RdataA::parse(\"" << s << "\") throws  Rdata::ExBadSyntax" << endl;
            exit(EXIT_FAILURE);
        }
        char * buf = (char *) calloc(100, sizeof(char));
        if (buf == 0) {
            cerr << "error in test: calloc failed" << endl;
            exit(EXIT_FAILURE);
        }
        char * offset = buf;
        datap->marshall(offset);
        unsigned long na = datap->addr();
        assert(memcmp(buf, &na, sizeof(na)) == 0);
        assert(offset-buf == sizeof(unsigned long));

        //unmarshalling
        char const * coffset = buf;
        RdataA const * ddp = RdataA::unmarshall(coffset);
        na = ddp->addr();
        assert(memcmp(buf, &na, sizeof(na)) == 0);
        assert(*ddp == *datap);
        assert((coffset-buf) == sizeof(unsigned long));
        delete ddp;
        free(buf);

        delete datap;
    }
}

void
rdataMX_test(void)
{
    { // bad sintax must throw an exception
        RdataMX const * datap;

        try {
            datap = RdataMX::parse("0it.uc3m.es");
            cerr << "RdataMX::parse(\"0it.uc3m.es\") did not throw any Exception" << endl;
            exit(EXIT_FAILURE);
        } catch (Rdata::ExBadSyntax) {}
        try {
            datap = RdataMX::parse("-2 it.uc3m.es");
            cerr << "RdataMX::parse(\"-2 it.uc3m.es\") did not throw any Exception" << endl;
            exit(EXIT_FAILURE);
        } catch (Rdata::ExBadSyntax) {}
        try {
            datap = RdataMX::parse("9999999 it.uc3m.es");
            cerr << "RdataMX::parse(\"9999999 it.uc3m.es\") did not throw any Exception" << endl;
            exit(EXIT_FAILURE);
        } catch (Rdata::ExBadSyntax) {}
        try {
            datap = RdataMX::parse("0 it.uc3m. es");
            cerr << "RdataMX::parse(\"0 it.uc3m .es\") did not throw any Exception" << endl;
            exit(EXIT_FAILURE);
        } catch (Rdata::ExBadSyntax) {}
    }

    { // good syntax, basic functions and streaming
        RdataMX const * datap;
        string s("0 it.uc3m.es");
        try {
            datap = RdataMX::parse(s);
        } catch (Rdata::ExBadSyntax) {
            cerr << "RdataMX::parse(\"" << s << "\") throws  Rdata::ExBadSyntax" << endl;
            exit(EXIT_FAILURE);
        }
        ostringstream oss;
        oss << *datap;
        assert(oss.str().compare(s) == 0);
        assert(Type::MX == datap->type());
        assert(Klass::IN == datap->klass());
        assert(datap->preference() == 0);
        assert(datap->exchange().compare("it.uc3m.es") == 0);
        assert(s.length()-2+2 == datap->length());
        delete datap;
    }

    { // comparison
        RdataMX const * ap;
        RdataMX const * cp;
        RdataMX const * dp;

        string s("0 it.uc3m.es");
        try {
            ap = RdataMX::parse(s);
        } catch (Rdata::ExBadSyntax) {
            cerr << "RdataMX::parse(\"" << s << "\") throws  Rdata::ExBadSyntax" << endl;
            exit(EXIT_FAILURE);
        }
        RdataMX const b = *ap;
        string ss("0 lab.it.uc3m.es");
        try {
            cp = RdataMX::parse(ss);
        } catch (Rdata::ExBadSyntax) {
            cerr << "RdataMX::parse(\"" << ss << "\") throws  Rdata::ExBadSyntax" << endl;
            exit(EXIT_FAILURE);
        }
        string sss("10 it.uc3m.es");
        try {
            dp = RdataMX::parse(sss);
        } catch (Rdata::ExBadSyntax) {
            cerr << "RdataMX::parse(\"" << sss << "\") throws  Rdata::ExBadSyntax" << endl;
            exit(EXIT_FAILURE);
        }

        assert(*ap == *ap);
        assert(*ap == b);
        assert(b == *ap);
        assert(!(*ap == *cp));
        assert(!(*cp == *ap));
        assert(!(b == *cp));
        assert(!(*cp == b));
        assert(!(*ap == *dp));
        assert(!(*dp == *ap));

        assert(*ap != *cp);
        assert(*cp != *ap);
        assert(*ap != *dp);
        assert(*dp != *ap);
        assert(!(b != b));
        assert(!(*ap != b));
        assert(!(b != *ap));

        delete ap;
        delete cp;
        delete dp;
    }
    
    { //marshalling
        RdataMX const * beforep;
        string s("23 ns.it.uc3m.es");
        try {
            beforep = RdataMX::parse(s);
        } catch (Rdata::ExBadSyntax) {
            cerr << "RdataMX::parse(\"" << s << "\") throws  Rdata::ExBadSyntax" << endl;
            exit(EXIT_FAILURE);
        }
        char * buf = (char *) calloc(100, sizeof(char));
        if (buf == 0) {
            cerr << "error in test: calloc failed" << endl;
            exit(EXIT_FAILURE);
        }
        char * offset = buf;
        beforep->marshall(offset);
        char mx[17] = {'\x00', '\x00', '\x02', 'n', 's', '\x02', 'i', 't', '\x04', 'u', 'c', '3', 'm', '\x02', 'e', 's', '\x00'};
        uint16_t npref = htons(23);
        memcpy(mx, &npref, 2);
        assert(memcmp(buf, &mx, sizeof(mx)) == 0);
        assert(offset-buf == sizeof(mx));

        //unmarshalling
        char const * coffset = buf;
        RdataMX const * afterp;
        try {
            afterp = RdataMX::unmarshall(coffset);
        } catch (Rdata::ExBadSyntax) {
            cerr << "RdataMX::unmarshall(\"" << coffset << "\") throws  Rdata::ExBadSyntax" << endl;
            exit(EXIT_FAILURE);
        }
        assert(*afterp == *beforep);
        assert((coffset-buf) == sizeof(mx));
        free(buf);

        delete afterp;
        delete beforep;
    }
    
    { // more marshalling, big name
        RdataMX const * beforep;
        string s("36 a2345678901234567890123456789012345678901234567890123456789.a2345678901234567890123456789012345678901234567890123456789.a2345678901234567890123456789012345678901234567890123456789.a2345678901234567890123456789012345678901234567890123456789.a23456789012345");
        try {
            beforep = RdataMX::parse(s);
        } catch (Rdata::ExBadSyntax) {
            cerr << "RdataMX::parse(\"" << s << "\") throws  Rdata::ExBadSyntax" << endl;
            exit(EXIT_FAILURE);
        }
        char * buf = (char *) calloc(300, sizeof(char));
        if (buf == 0) {
            cerr << "error in test: calloc failed" << endl;
            exit(EXIT_FAILURE);
        }
        char * offset = buf;
        beforep->marshall(offset);

        //unmarshalling
        char const * coffset = buf;
        RdataMX const * afterp;
        try {
            afterp = RdataMX::unmarshall(coffset);
        } catch (Rdata::ExBadSyntax) {
            cerr << "RdataMX::unmarshall(\"" << coffset << "\") throws  Rdata::ExBadSyntax" << endl;
            exit(EXIT_FAILURE);
        }
        assert(*afterp == *beforep);
        free(buf);

        delete afterp;
        delete beforep;
    }
}

void
rdataNS_test(void)
{
    { // bad sintax must throw an exception
        RdataNS const * datap;

        try {
            datap = RdataNS::parse("0it.uc3m.es");
            cerr << "RdataNS::parse(\"0it.uc3m.es\") did not throw any Exception" << endl;
            exit(EXIT_FAILURE);
        } catch (Rdata::ExBadSyntax) {}
        try {
            datap = RdataNS::parse("-2 it.uc3m.es");
            cerr << "RdataNS::parse(\"-2 it.uc3m.es\") did not throw any Exception" << endl;
            exit(EXIT_FAILURE);
        } catch (Rdata::ExBadSyntax) {}
    }

    { // good syntax, basic functions and streaming
        RdataNS const * datap;
        string s("a.it.uc3m.es");
        try {
            datap = RdataNS::parse(s);
        } catch (Rdata::ExBadSyntax) {
            cerr << "RdataNS::parse(\"" << s << "\") throws  Rdata::ExBadSyntax" << endl;
            exit(EXIT_FAILURE);
        }
        ostringstream oss;
        oss << *datap;
        assert(oss.str().compare(s) == 0);
        assert(Type::NS == datap->type());
        assert(Klass::IN == datap->klass());
        assert(datap->nsdname().compare("a.it.uc3m.es") == 0);
        assert(s.length() == datap->length());
        delete datap;
    }

    { // comparison
        RdataNS const * ap;
        RdataNS const * cp;

        string s("it.uc3m.es");
        try {
            ap = RdataNS::parse(s);
        } catch (Rdata::ExBadSyntax) {
            cerr << "RdataNS::parse(\"" << s << "\") throws  Rdata::ExBadSyntax" << endl;
            exit(EXIT_FAILURE);
        }
        RdataNS const b = *ap;
        string ss("lab.it.uc3m.es");
        try {
            cp = RdataNS::parse(ss);
        } catch (Rdata::ExBadSyntax) {
            cerr << "RdataNS::parse(\"" << s << "\") throws  Rdata::ExBadSyntax" << endl;
            exit(EXIT_FAILURE);
        }

        assert(*ap == *ap);
        assert(*ap == b);
        assert(b == *ap);
        assert(!(*ap == *cp));
        assert(!(*cp == *ap));
        assert(!(b == *cp));
        assert(!(*cp == b));

        assert(*ap != *cp);
        assert(*cp != *ap);
        assert(!(b != b));
        assert(!(*ap != b));
        assert(!(b != *ap));

        delete ap;
        delete cp;
    }
    
    { //marshalling
        RdataNS const * beforep;
        string s("ns.it.uc3m.es");
        try {
            beforep = RdataNS::parse(s);
        } catch (Rdata::ExBadSyntax) {
            cerr << "RdataNS::parse(\"" << s << "\") throws  Rdata::ExBadSyntax" << endl;
            exit(EXIT_FAILURE);
        }
        char * buf = (char *) calloc(100, sizeof(char));
        if (buf == 0) {
            cerr << "error in test: calloc failed" << endl;
            exit(EXIT_FAILURE);
        }
        char * offset = buf;
        beforep->marshall(offset);
        char ns[15] = { '\x02', 'n', 's', '\x02', 'i', 't', '\x04', 'u', 'c', '3', 'm', '\x02', 'e', 's', '\x00'};
        assert(memcmp(buf, &ns, sizeof(ns)) == 0);
        assert(offset-buf == sizeof(ns));

        //unmarshalling
        char const * coffset = buf;
        RdataNS const * afterp;
        try {
            afterp = RdataNS::unmarshall(coffset);
        } catch (Rdata::ExBadSyntax) {
            cerr << "RdataNS::unmarshall(\"" << coffset << "\") throws  Rdata::ExBadSyntax" << endl;
            exit(EXIT_FAILURE);
        }
        assert(*afterp == *beforep);
        assert((coffset-buf) == sizeof(ns));
        free(buf);

        delete afterp;
        delete beforep;
    }
    
    { // more marshalling, big name
        RdataNS const * beforep;
        string s("a2345678901234567890123456789012345678901234567890123456789.a2345678901234567890123456789012345678901234567890123456789.a2345678901234567890123456789012345678901234567890123456789.a2345678901234567890123456789012345678901234567890123456789.a23456789012345");
        try {
            beforep = RdataNS::parse(s);
        } catch (Rdata::ExBadSyntax) {
            cerr << "RdataNS::parse(\"" << s << "\") throws  Rdata::ExBadSyntax" << endl;
            exit(EXIT_FAILURE);
        }
        char * buf = (char *) calloc(300, sizeof(char));
        if (buf == 0) {
            cerr << "error in test: calloc failed" << endl;
            exit(EXIT_FAILURE);
        }
        char * offset = buf;
        beforep->marshall(offset);

        //unmarshalling
        char const * coffset = buf;
        RdataNS const * afterp;
        try {
            afterp = RdataNS::unmarshall(coffset);
        } catch (Rdata::ExBadSyntax) {
            cerr << "RdataNS::unmarshall(\"" << coffset << "\") throws  Rdata::ExBadSyntax" << endl;
            exit(EXIT_FAILURE);
        }
        assert(*afterp == *beforep);
        free(buf);

        delete afterp;
        delete beforep;
    }
}

void
rdata_test(void)
{
    { // A records
        Rdata const * datap;
        string sa("163.117.141.15");
        try {
            datap = RdataA::parse(sa);
        } catch (Rdata::ExBadSyntax) {
            cerr << "RdataA::parse(\"" << sa << "\") throws  Rdata::ExBadSyntax" << endl;
            exit(EXIT_FAILURE);
        }
        assert(datap->length() == RdataA::LENGTH);
        assert(datap->type() == Type::A);
        assert(datap->klass() == Klass::IN);
        // streaming thorugh base class must be the same as through derived calss
        ostringstream ossa;
        ossa << *datap;
        assert(ossa.str() == sa);
        delete datap;
    }

    { // MX records
        Rdata const * datap;
        string smx("0 saruman.it.uc3m.es");
        try {
            datap = RdataMX::parse(smx);
        } catch (Rdata::ExBadSyntax) {
            cerr << "RdataMX::parse(\"" << smx << "\") throws  Rdata::ExBadSyntax" << endl;
            exit(EXIT_FAILURE);
        }
        assert(datap->length() == smx.length()-2+2);
        assert(datap->type()  == Type::MX);
        assert(datap->klass() == Klass::IN);
        ostringstream ossmx;
        ossmx << *datap;
        assert(ossmx.str().compare(smx) == 0);
        delete datap;
    }

    { // NS records
        Rdata const * datap;
        string sns("saruman.it.uc3m.es");
        try {
            datap = RdataNS::parse(sns);
        } catch (Rdata::ExBadSyntax) {
            cerr << "RdataNS::parse(\"" << sns << "\") throws  Rdata::ExBadSyntax" << endl;
            exit(EXIT_FAILURE);
        }
        assert(datap->length() == sns.length());
        //assert(datap->type()  == Type::NS);
        //assert(datap->klass() == Klass::IN);
        ostringstream ossns;
        ossns << *datap;
        assert(ossns.str().compare(sns) == 0);
        delete datap;
    }
}

int
main(int argc, char ** argv) {

    util_test();
    type_test();
    klass_test();
    rdataA_test();
    rdataMX_test();
    rdataNS_test();
    rdata_test();
    rr_test();

    exit(EXIT_SUCCESS);
}

