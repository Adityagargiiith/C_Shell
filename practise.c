#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
// #define PATH_MAX 100

void peek_directory(const char *path) {
    DIR *dir = opendir(path);
    if (dir == NULL) {
        perror("opendir");
        return;
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_name[0] == '.') {
            continue; // Skip hidden files/directories
        }

        char full_path[1000];
        snprintf(full_path, sizeof(full_path), "%s/%s", path, entry->d_name);

        struct stat file_stat;
        if (stat(full_path, &file_stat) == -1) {
            perror("stat");
            continue;
        }

        printf("Name: %s\n", entry->d_name);
        printf("Type: %s\n", S_ISDIR(file_stat.st_mode) ? "Directory" : "File");
        printf("Size: %ld bytes\n", (long)file_stat.st_size);

        struct passwd *pw = getpwuid(file_stat.st_uid);
        struct group *gr = getgrgid(file_stat.st_gid);
        printf("Owner: %s\n", pw ? pw->pw_name : "unknown");
        printf("Group: %s\n", gr ? gr->gr_name : "unknown");

        struct tm *timeinfo = localtime(&file_stat.st_mtime);
        char time_str[80];
        strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", timeinfo);
        printf("Last Modified: %s\n", time_str);

        printf("Permissions: %o\n", file_stat.st_mode & 0777);

        printf("\n");
    }

    closedir(dir);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <directory>\n", argv[0]);
        return 1;
    }

    peek_directory(argv[1]);

    return 0;
}
