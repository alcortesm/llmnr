#include "args.h"
#include <getopt.h>
#include <cstdlib>
#include <cerrno>

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

// parse a decimal representation of a 16 bit unsigned integer
// thats between 0 and 65535 ((1<<16) -1)
unsigned short
str2uint16(const char * a) throw (string)
{
    char *end_ptr;
    long int long_var;

    if (a[0] == 0)
        throw string("null input pointer");

    errno = 0;
    long_var = std::strtol(a, &end_ptr, 0); // decimal conversion

    if (errno == ERANGE) {
        throw string("number out of range");
    } else if (long_var > ((1<<16) -1)) {
        throw string("number too large for a 16 bits unsigned integer");
    } else if (long_var < 0) {
        throw string("negative number");
    } else if (end_ptr == a) {
        throw string("not valid numeric input");
    } else if (*end_ptr != '\0') {
        throw string("not valid numeric input, it has extra characters at the end");
    }
    return (unsigned short int) long_var;
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
			    port = str2uint16(optarg);
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
