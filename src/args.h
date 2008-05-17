#ifndef INCLUDED_ARGS
#define INCLUDED_ARGS

#include <string>
#include <iostream>

#include "llmnr.h"

class Args {
    unsigned short int  const d_port;
    bool                const d_responder;
    std::string         const d_configFilePath;
    bool                const d_interactive;
    bool                const d_debug;
    std::string         const d_name;
    std::string         const d_type;
    
public:

    Args(unsigned short int const port,
         bool               const responder,
         std::string        const &configFilePath,
         bool               const interactive,
         bool               const debug,
         std::string        const &name,
         std::string        const &type);

    static Args *       parse(int const argc, char ** const argv);

    unsigned short int  port()           const;
    bool                responder()      const;
    std::string const & configFilePath() const;
    bool                interactive()    const;
    bool                debug()          const;
    std::string const & name()           const;
    std::string const & type()           const;
    void                print() 		 const;
};

#endif
