#include "headers.h"
#include "prompt.h"


void prompt() {
    // Do not hardcode the prompt
    // printf("S");
     uid_t uid = getuid();
    
    // Use the getpwuid function to get user information by UID
    struct passwd *pw = getpwuid(uid);
    // char *user = getenv("USER");
    struct utsname systeminfo;
    int a = uname(&systeminfo);
    // uname(sty)
    char directory[100];
    getcwd(directory, sizeof(directory));

    printf("<" ANSI_COLOR_GREEN "%s@" ANSI_COLOR_RESET  ANSI_COLOR_GREEN "%s" ANSI_COLOR_RESET ":" ANSI_COLOR_BLUE "%s" ANSI_COLOR_RESET ">", pw->pw_name, systeminfo.nodename, directory);
    // return;
}
