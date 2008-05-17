#ifndef _LLMNR_H
#define _LLMNR_H
enum {
    DEF_PORT = 5355, /* RFC */
    MIN_PORT = 1,
    MAX_PORT = (1<<16) -1 /* 65535 */
};
#endif
