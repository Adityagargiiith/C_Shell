#include <stdio.h>
#include <dirent.h>

int main() {
    // Open the /proc directory
    DIR *procDir = opendir("/proc");
    if (procDir == NULL) {
        perror("opendir");
        return 1;
    }

    // Read and print the contents of the /proc directory
    struct dirent *entry;
    while ((entry = readdir(procDir)) != NULL) {
        printf("%s\n", entry->d_name);
    }

    // Close the /proc directory
    closedir(procDir);

    return 0;
}
