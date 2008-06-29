#include "util.h"
#include "args.h"
#include <getopt.h>
#include <cstdlib>

using std::string;

Args::Args(unsigned short int   const   port,
           bool                 const   responder,
           string               const & configFilePath,
           bool                 const   interactive,
           bool                 const   debug,
           string               const & name,
           string               const & type)
:
    d_port(port),
    d_responder(responder),
    d_configFilePath(configFilePath),
    d_interactive(interactive),
    d_debug(debug),
    d_name(name),
    d_type(type)
{}

void
usage(void) {
	std::cerr << "Usage:" << std::endl ;
	std::cerr << "	llmnr [-p port] [-r file] [-i] [-d] [name [type]]"
		<< std::endl ;
	std::cerr << MIN_PORT << " <= port <= " << MAX_PORT << std::endl;
	exit(EXIT_FAILURE);
}

Args *
Args::parse(int argc, char** argv)
{
    unsigned short int port = DEF_PORT;
    bool         responder = false;
    string       configFilePath;
    bool         interactive = false;
    bool         debug = false;
    string       name;
    string       type;

    if (argc < 1)
    	usage();


	if (argv == 0)
		usage();

	for (int i=0; i<argc; i++) {
		if (!argv[i])
			usage();
	}
	

	char c;
	while (1) {
		opterr = 0; /* don't print errors */
		c = getopt(argc, argv, "p:r:di");
		if (c == -1) /* end of options */
			break;
		
		switch (c) {
		case 'p':
            try {
			    port = util::str2uint16(optarg);
            } catch (std::string & s) {
                std::cerr << "bad port number: " << s << std::endl;
                usage();
            }
			if (port < MIN_PORT) 
				usage();
            // the following is a comparison for (port > MAX_PORT)
            // It can not be written like that as gcc gives the following warning on
            // systems with 16 bit unsigned shorts:
            // warning: comparison is always false due to limited range of data type
            if (port - MAX_PORT > 0)
                usage();
			break;

		case 'r':
			responder = true;
			if (optarg)
				configFilePath.append(optarg);
			break;

		case 'd':
			debug = true;
			break;

		case 'i':
			interactive = true;
			break;

		case '?': /* error found */
			usage();
			break;

		default:
			exit(EXIT_FAILURE);
		}
	}

	if (argc - optind > 2) /* more than 2 arguments */
		usage();
		
	if (optind < argc)
		name.append(argv[optind++]);

	if (optind < argc)
		type.append(argv[optind]);

    return new Args(port,
            responder,
            configFilePath,
            interactive,
            debug,
            name,
            type);
}

void
Args::print() const
{
    std::cout << "args.port = " << d_port << std::endl ;
    
    if (d_responder == true)
    	std::cout << "args.responder = " << "true" << std::endl ;	
    else
    	std::cout << "args.responder = " << "false" << std::endl ;
    
    std::cout << "args.configFilePath = " << d_configFilePath << std::endl ;

	if (d_interactive)
		std::cout << "args.interactive = " << "true" << std::endl ;
	else
		std::cout << "args.interactive = " << "false" << std::endl ;

	if (d_debug)
		std::cout << "args.debug = " << "true" << std::endl ;
	else
		std::cout << "args.debug = " << "false" << std::endl ;

    std::cout << "args.name = " << d_name << std::endl ;
    std::cout << "args.type = " << d_type << std::endl ;
}

unsigned short int
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
