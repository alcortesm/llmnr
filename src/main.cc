#include <iostream>
#include "args.h"
#include "type.h"

int
main(int argc, char ** argv)
{
    Args * argsp;
    argsp = Args::parse(argc, argv);
    argsp->print();

    Type::A.print();
}
