#include "headers.h"
#include "prompt.h"

void printpid() {

    FILE *file = fopen("/proc/sys/kernel/ns_last_pid", "r");
    if (file == NULL) {
        perror("Failed to open");
        return;
    }

    int latest_pid;
    if (fscanf(file, "%d", &latest_pid) == 1) {
        printf("%d\n", latest_pid);
    } else {
        perror("Failed to read file");
    }

    fclose(file);
}



void die(const char *s) {
    perror(s);
    exit(1);
}

struct termios orig_termios;

void disableRawMode() {
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios) == -1)
        die("tcsetattr");
}

void enableRawMode() {
    if (tcgetattr(STDIN_FILENO, &orig_termios) == -1) die("tcgetattr");
    atexit(disableRawMode);
    struct termios raw = orig_termios;
    raw.c_lflag &= ~(ICANON | ECHO);
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1) die("tcsetattr");
}

int stopPrinting = 0;

void handleSignal(int signo) {
    if (signo == SIGINT) {
        stopPrinting = 1;
    }
}

void neonate(char **input) {
    int count=0;
    while(input[count]!=0){
        count++;
    }
    if(count<3){
        printf("invalid neonate command");
        return;
    }
    
    int interval = atoi(input[2]);

    if (interval <= 0) {
        printf("Invalid time interval\n");
        return;
    }

    enableRawMode();
    signal(SIGINT, handleSignal);
    // int i=(*countofprocessids)-1;

        pid_t pid = fork();
        if (pid < 0) {
            die("fork");
        } else if (pid == 0) {
            while (!stopPrinting) {
                printpid();
                sleep(interval);
            }
            exit(0);
        }

else{
    
    char c;
    while (1) {
        read(STDIN_FILENO, &c, 1);
        if (c == 'x') {
                kill(pid, SIGINT); 
                wait(NULL);
            // }
            break;
        }
    }

}
    disableRawMode();
}
