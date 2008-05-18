#include <iostream>
#include "args.h"
#include "type.h"

using std::cout;
using std::endl;

int
main(int argc, char ** argv)
{
    Args * argsp;
    argsp = Args::parse(argc, argv);
    argsp->print();

    cout << endl;

    Type::A.print();
    Type::NS.print();
    Type::CNAME.print();
    Type::SOA.print();
    Type::PTR.print();
    Type::MX.print();
}
