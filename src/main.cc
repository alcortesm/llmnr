#include <iostream>
#include "args.h"
#include "type.h"
#include "class.h"

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

    rr::Class::IN.print();
}
