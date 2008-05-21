#include <iostream>
#include "args.h"
#include "type.h"
#include "clas.h"
#include "rr.h"

using std::cout;
using std::endl;
using rr::Rr;

int
main(int argc, char ** argv)
{
    Args * argsp;
    argsp = Args::parse(argc, argv);
    argsp->print();
    delete argsp;

    cout << endl;

    rr::Type::A.print();
    rr::Type::NS.print();
    rr::Type::CNAME.print();
    rr::Type::SOA.print();
    rr::Type::PTR.print();
    rr::Type::MX.print();
    
    cout << endl;

    rr::Clas::IN.print();

    cout << endl;

    Rr const * rr;
    try {
        rr = Rr::parse(" 	 rrname 132 rrclass		rrtype rdata1 rdata2");
        rr->print();
        delete rr;
    } catch (rr::ExNoContent e) {
        std::cerr << "pasing failed" << endl;
        exit(EXIT_FAILURE);
    } catch (rr::ExBadSyntax e) {
        std::cerr << "pasing failed" << endl;
        exit(EXIT_FAILURE);
    }
    try {
        rr = Rr::parse(" #	 rrname 132 rrclass		rrtype	 rdata1 rdata2");
        delete rr;
        std::cerr << "parsing failed, comment not found!" << endl;;
        exit(EXIT_FAILURE);
    } catch (rr::ExNoContent & e) {
        cout << "parse of comment succed!" << endl;
        // test passed
    } catch (rr::ExBadSyntax e) {
        std::cerr << "pasing failed" << endl;;
        exit(EXIT_FAILURE);
    }
    exit(EXIT_SUCCESS);
}
