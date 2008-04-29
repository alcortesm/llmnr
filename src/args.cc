#include "args.h"

using std::string;

Args::Args(unsigned int const port,
           bool         const responder,
           string       const &configFilePath,
           bool         const interactive,
           bool         const debug,
           string       const &name,
           string       const &type)
:
    d_port(port),
    d_responder(responder),
    d_configFilePath(configFilePath),
    d_interactive(interactive),
    d_debug(debug),
    d_name(name),
    d_type(type)
{}

Args *
Args::parse(int argc, char** argv)
{
    unsigned int port = DEF_PORT;
    bool         responder = false;
    string       configFilePath = "";
    bool         interactive = false;
    bool         debug = false;
    string       name = "";
    string       type = "";

    if (argc < 1) {
        return 0;
    }

    if (argv == 0) {
        return 0;
    }

    int i;
    for (i=0; i<argc; i++) {
        if (!argv[i]) {
            return 0;
        }
    }

    port = argc;
    configFilePath.append(argv[0]);
    for (int i=1; i<argc; i++) {
        if (i!=1)
            name.append(", ");
        name.append(argv[i]);
    }

    Args * args = new Args(port,
            responder,
            configFilePath,
            interactive,
            debug,
            name,
            type);
    return args;
}

void
Args::print() const
{
    std::cout << "args.port = " << d_port << std::endl ;
    std::cout << "args.responder = " << d_responder << std::endl ;
    std::cout << "args.configFilePath = " << d_configFilePath << std::endl ;
    std::cout << "args.interactive = " << d_interactive << std::endl ;
    std::cout << "args.debug = " << d_debug << std::endl ;
    std::cout << "args.name = " << d_name << std::endl ;
    std::cout << "args.type = " << d_type << std::endl ;
}

int
Args::port() const {
    return d_port;
}

bool
Args::responder() const {
    return d_responder;
}

string const &
Args::configFilePath() const {
    return d_configFilePath;
}

bool
Args::interactive() const {
    return d_interactive;
}

bool
Args::debug() const {
    return d_debug;
}

string const &
Args::name() const {
    return d_name;
}

string const &
Args::type() const {
    return d_type; 
}
