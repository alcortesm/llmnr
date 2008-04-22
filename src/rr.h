typedef struct rr Rr;

enum {
	TYPE_A       =  1,
	TYPE_NS      =  2,
	TYPE_MD      =  3,
	TYPE_MF      =  4,
	TYPE_CNAME   =  5,
	TYPE_SOA     =  6,
	TYPE_MB      =  7,
	TYPE_MG      =  8,
	TYPE_MR      =  9,
	TYPE_NULL    = 10,
	TYPE_WKS     = 11,
	TYPE_PTR     = 12,
	TYPE_HINFO   = 13,
	TYPE_MINFO   = 14,
	TYPE_MX      = 15,
	TYPE_TXT     = 16
};

enum {
	CLASS_IN  = 1,
	CLASS_CS  = 2,
	CLASS_CH  = 3,
	CLASS_HS  = 4
};

Rr *   RrCreate    (char * name, int type, int class, int ttl, char * rdata);
void    RrDelete    (Rr * rr);
void    RrPrint     (Rr * rr);
