#include <iostream>
#include "args.h"

int
main(int argc, char ** argv)
{
    Args * argsp;
    argsp = Args::parse(argc, argv);
    argsp->print();

    int port = argsp->port();
    bool responder = argsp->responder();
    std::string const & configFilePath = argsp->configFilePath();
    bool interactive = argsp->interactive();
    bool debug = argsp->debug();
    std::string const & name = argsp->name();
    std::string const & type = argsp->type();
    
    std::cout << std::endl << std::endl;
    std::cout << "argsp->port() = " << port << std::endl;
    std::cout << "argsp->responder() = " << responder << std::endl;
    std::cout << "argsp->configFilePath() = " << configFilePath << std::endl;
    std::cout << "argsp->interactive() = " << interactive << std::endl;
    std::cout << "argsp->debug() = " << debug << std::endl;
    std::cout << "argsp->name() = " << name << std::endl;
    std::cout << "argsp->type() = " << type << std::endl;
    
    delete argsp;
    
    std::cout << "argsp->name() = " << argsp->name() << std::endl;
    
}
