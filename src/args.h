typedef struct args Args;

Args * ArgsCreate(int argc, char** argv);
void   ArgsDestroy(Args * a);

void   ArgsPrint(Args* a);
int    ArgsIsDebug(Args * a);

