#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <sys/utsname.h>
#include <string.h>

#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_BLUE "\x1b[34m"
#define ANSI_COLOR_RESET "\x1b[0m"

void prompt() {
    uid_t uid = getuid();
    struct passwd *pw = getpwuid(uid);
    struct utsname systeminfo;
    int a = uname(&systeminfo);
    char directory[100];
    getcwd(directory, sizeof(directory));

    char *home_directory = pw->pw_dir;
    char relative_directory[100];
    
    if (strncmp(directory, home_directory, strlen(home_directory)) == 0) {
        snprintf(relative_directory, sizeof(relative_directory), "~%s", directory + strlen(home_directory));
    } else {
        strncpy(relative_directory, directory, sizeof(relative_directory));
    }

    printf("<" ANSI_COLOR_GREEN "%s@" ANSI_COLOR_RESET  ANSI_COLOR_GREEN "%s" ANSI_COLOR_RESET ":" ANSI_COLOR_BLUE "%s" ANSI_COLOR_RESET ">", pw->pw_name, systeminfo.nodename, relative_directory);
}

int main() {
    prompt();
    return 0;
}
