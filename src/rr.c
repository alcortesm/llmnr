#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

#include "rr.h"

enum {
    TYPE_MIN = TYPE_A,
    TYPE_MAX = TYPE_TXT,
    CLASS_MIN = CLASS_IN,
    CLASS_MAX = CLASS_HS
};

struct rr {
	char *  name;
	int     type;
	int     class;
	int     ttl;
	char *  rdata;
};

/*
 * On error returns NULL and sets errno
 */
Rr *
RrCreate(char * name, int type, int class, int ttl, char * rdata)
{
    if (!name) {
        errno = EINVAL;
        return NULL;
    }
    if (type<TYPE_MIN || type>TYPE_MAX) {
        errno = EINVAL;
        return NULL;
    }
    if (class<CLASS_MIN || class>CLASS_MAX) {
        errno = EINVAL;
        return NULL;
    }
    if (!rdata) {
        errno = EINVAL;
        return NULL;
    }

    Rr * new = malloc(sizeof(Rr));
    if (!new)
        return NULL;

	new->name  = name;
	new->type  = type;
	new->class = class;
	new->ttl   = ttl;
	new->rdata = rdata;

	return new;
}

void
RrDelete(Rr * rr)
{
	if (rr->name)
		free(rr->name);
	if (rr->rdata)
		free(rr->rdata);
	free(rr);
}

void
RrPrint(Rr * rr)
{
	fprintf(stdout, "%s ", rr->name);

	switch(rr->type) {
	case TYPE_A:
		fprintf(stdout, "A");
		break;
	case TYPE_NS:
		fprintf(stdout, "NS");
		break;
	case TYPE_MD:
		fprintf(stdout, "MD");
		break;
	case TYPE_MF:
		fprintf(stdout, "MF");
		break;
	case TYPE_CNAME:
		fprintf(stdout, "CNAME");
		break;
	case TYPE_SOA:
		fprintf(stdout, "SOA");
		break;
	case TYPE_MB:
		fprintf(stdout, "MB");
		break;
	case TYPE_MG:
		fprintf(stdout, "MG");
		break;
	case TYPE_MR:
		fprintf(stdout, "MR");
		break;
	case TYPE_NULL:
		fprintf(stdout, "NULL");
		break;
	case TYPE_WKS:
		fprintf(stdout, "WKS");
		break;
	case TYPE_PTR:
		fprintf(stdout, "PTR");
		break;
	case TYPE_HINFO:
		fprintf(stdout, "HINFO");
		break;
	case TYPE_MINFO:
		fprintf(stdout, "MINFO");
		break;
	case TYPE_MX:
		fprintf(stdout, "MX");
		break;
	case TYPE_TXT:
		fprintf(stdout, "TXT");
		break;
	}
	fprintf(stdout, " ");

	switch(rr->class) {
	case CLASS_IN:
		fprintf(stdout, "IN");
		break;
	case CLASS_CS:
		fprintf(stdout, "CS");
		break;
	case CLASS_CH:
		fprintf(stdout, "CH");
		break;
	case CLASS_HS:
		fprintf(stdout, "HS");
		break;
	}

	fprintf(stdout, " %d %s\n", rr->ttl, rr->rdata);
}
 
