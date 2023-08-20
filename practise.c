#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
       #include <unistd.h>



int main() {
    // int pid;
    printf("Enter the process ID: ");
    // scanf("%d", &pid);
    int pid=getpid();

    char filename[256];
    snprintf(filename, sizeof(filename), "/proc/%d/status", pid);

    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        perror("Error opening file");
        return 1;
    }

    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        printf("%s", buffer);
    }

    fclose(fp);
    return 0;
}
