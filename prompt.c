#include "headers.h"
#include "prompt.h"


void prompt() {
    // Do not hardcode the prmopt
    // printf("S");
    char *user=getenv("USER");
struct utsname systeminfo;
int a=uname(&systeminfo);
// uname(sty)
    char directory[100];
    getcwd(directory,sizeof(directory));
    printf("<%s@%s:%s>",user,systeminfo.nodename,directory);    
    // return;
}


