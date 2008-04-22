#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <error.h>
#include <errno.h>

#include "const.h"
#include "args.h"
#include "rr.h"

Args * a;
Rr   * r;

void
ParseArgs(int argc, char* argv[])
{
    a = ArgsCreate(argc, argv);
    if (!a)
        error(1, errno, "ParseArgs(...)");

	if (ArgsIsDebug(a))
		ArgsPrint(a);

	return;
}

void
Conf()
{
	r = RrCreate(strdup("it.uc3m.es"),
			TYPE_A, CLASS_IN, 100,
			strdup("163.117.15.158"));
}

void
LaunchThreads()
{
//	pthread_t * sender;
//	sender = (pthread_t *) xmalloc(sizeof(pthread_t));
//	pthread_create(sender, NULL, pthread_send, NULL);

//	pthread_t * receiver;
//	receiver = (pthread_t *) xmalloc(sizeof(pthread_t));
//	pthread_create(receiver, NULL, pthread_receiver, NULL);

//	pthread_join(*sender, NULL);
//	pthread_join(*receiver, NULL);

//	free(sender);
//	free(receiver);
	return;
}

int
main(int argc, char **argv) {

	ParseArgs(argc, argv);
	Conf();

	RrPrint(r);

	LaunchThreads();

	RrDelete(r);
	exit(EXIT_SUCCESS);
}
