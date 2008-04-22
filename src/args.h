typedef struct args Args;

Args * ArgsCreate           (int argc, char** argv);
void   ArgsDestroy          (Args * a);

void   ArgsPrint            (Args* a);

int    ArgsGetPort          (Args * a);
int    ArgsIsResponder      (Args * a);
char * ArgsGetConfigFile    (Args * a);
int    ArgsIsIteractive     (Args * a);
int    ArgsIsDebug          (Args * a);
char * ArgsGetName          (Args * a);
char * ArgsGetType          (Args * a);

