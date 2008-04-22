#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <getopt.h>
#include <error.h>
#include <errno.h>

#include "args.h"
#include "llmnr.h"

struct args {
	int   port;
	int   isresponder;
	char* configfile;
	int   interactive;
	int   debug;
	char* name;
	char* type;
};

void
Usage()
{
	fprintf(stderr, "usage:\n");
	fprintf(stderr, "   llmnr [-p port] [-r file] [-i] [-d] [name [type]]\n");
	exit(EXIT_FAILURE);
}

void
InitArgs(Args* a)
{
	a->port        = DEF_PORT;
	a->isresponder = 0;
	a->configfile  = NULL;
	a->interactive = 0;
	a->debug       = 0;
	a->name        = NULL;
	a->type        = NULL;
	return;
}


// exits on errors
Args *
ArgsCreate(int argc, char** argv) {
	if (argc < 1) {
        errno = EINVAL;
        return NULL;
    }
	if (argv == NULL) {
        errno = EINVAL;
        return NULL;
    }

	int i;
	for (i = 0; i<argc; i++) {
		if (!argv[i]) {
            errno = EINVAL;
            return NULL;
        }
	}

    Args * a = malloc(sizeof(Args));
    if (!a)
        return NULL;
    InitArgs(a);

	int c;
	while (1) {
		opterr = 0; /* don't print errors */
		c = getopt(argc, argv, "p:r:di");

		if (c == -1) { /* end of options */
			break;
		}

		switch (c) {
		case 'p':
			a->port = atoi(optarg);
			if (a->port < MIN_PORT || a->port > MAX_PORT)
				Usage();
			break;

		case 'r':
			a->isresponder = 1;
			if (optarg)
				a->configfile = optarg;
			break;

		case 'd':
			a->debug = 1;
			break;

		case 'i':
			a->interactive = 1;
			break;

		case '?': /* error found */
			Usage();
			break;

		default:
			exit(EXIT_FAILURE);
		}
	}

	if (argc - optind > 2) /* more than 2 arguments */
		Usage();

	if (optind < argc)
		a->name = argv[optind++];

	if (optind < argc)
		a->type = argv[optind];

	return a;
}

void
ArgsPrint(Args* a)
{
	fprintf(stderr, "port        = %d\n", a->port);

	if (a->isresponder) {
		fprintf(stderr, "isresponder = true\n");
	} else {
		fprintf(stderr, "isresponder = false\n");
	}

	if (a->configfile) {
		fprintf(stderr, "configfile  = %s\n", a->configfile);
	} else {
		fprintf(stderr, "configfile  = NULL\n");
	}

	if (a->interactive)
		fprintf(stderr, "interactive = true\n");
	else
		fprintf(stderr, "interactive = false\n");

	if (a->debug)
		fprintf(stderr, "debug       = true\n");
	else
		fprintf(stderr, "debug       = false\n");

	if (a->name) {
		fprintf(stderr, "name        = %s\n", a->name);
	} else {
		fprintf(stderr, "name        = NULL\n");
	}

	if (a->type) {
		fprintf(stderr, "type        = %s\n", a->type);
	} else {
		fprintf(stderr, "type        = NULL\n");
	}
	
	return;
}

int
ArgsGetPort(Args * a) {
    if (!a) {
        errno = EINVAL;
        return -1;
    }
    return (a->port); 
}

int
ArgsIsResponder(Args * a) {
    if (!a) {
        errno = EINVAL;
        return -1;
    }
    return (a->isresponder); 
}

char *
ArgsGetConfigFile(Args * a) {
    if (!a) {
        errno = EINVAL;
        return NULL;
    }
    return (a->configfile); 
}

int
ArgsIsIteractive(Args * a) {
    if (!a) {
        errno = EINVAL;
        return -1;
    }
    return (a->interactive); 
}

int
ArgsIsDebug(Args * a) {
    if (!a) {
        errno = EINVAL;
        return -1;
    }
    return (a->debug); 
}

char *
ArgsGetName(Args * a) {
    if (!a) {
        errno = EINVAL;
        return NULL;
    }
    return (a->name); 
}

char *
ArgsGetType(Args * a) {
    if (!a) {
        errno = EINVAL;
        return NULL;
    }
    return (a->type); 
}
