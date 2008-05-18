#include <iostream>
#include "args.h"
#include "type.h"
#include "clas.h"
#include "rr.h"

using std::cout;
using std::endl;

int
main(int argc, char ** argv)
{
    Args * argsp;
    argsp = Args::parse(argc, argv);
    argsp->print();

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

    rr::Rr const * rr = rr::Rr::parse("hola");
    rr->print();
}
