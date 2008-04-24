#include "args.h"

using std::string;

Args::Args(unsigned int const port,
           bool         const responder,
           string       const configFilePath,
           bool         const interactive,
           bool         const debug,
           string       const name,
           string       const type)
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
}

int
Args::port() const {
    return d_port;
}

bool
Args::responder() const {
    return d_responder;
}

string const
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

string const
Args::name() const {
    return d_name;
}

string const
Args::type() const {
    return d_type; 
}
