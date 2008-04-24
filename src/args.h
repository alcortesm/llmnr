#ifndef _ARGS_H
#define _ARGS_H

#include <string>
#include <iostream>

#include "llmnr.h"

class Args {
    unsigned int const d_port;
    bool         const d_responder;
    std::string  const d_configFilePath;
    bool         const d_interactive;
    bool         const d_debug;
    std::string  const d_name;
    std::string  const d_type;
    
public:

    Args(unsigned int const port,
         bool         const responder,
         std::string  const configFilePath,
         bool         const interactive,
         bool         const debug,
         std::string  const name,
         std::string  const type);

    static Args * parse(int const argc, char ** const argv);
    void          print() const;

    int               port()           const;
    bool              responder()      const;
    std::string const configFilePath() const;
    bool              interactive()    const;
    bool              debug()          const;
    std::string const name()           const;
    std::string const type()           const;
};

#endif
