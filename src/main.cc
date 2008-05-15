#include <iostream>
#include "args.h"

int
main(int argc, char ** argv)
{
    Args * argsp;
    argsp = Args::parse(argc, argv);
    argsp->print();
    
}
