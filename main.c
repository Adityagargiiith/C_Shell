#include "headers.h"


    char directory[100];

int ctrl_c_pressed = 0;

void sigint_handler(int sig) {
    // Handle Ctrl-C (SIGINT) here
//    printf("hello"); // Print a newline to go to the next prompt
// ctrl_c_pressed = 1;
if(ctrl_c_pressed){
    prompt(directory);
    // prompt(direectory)
}
printf("\n"); 
// printf("hello");
        // fflush(stdout);
}

void sigtstp_handler(int sig) {
    // Handle Ctrl-Z (SIGTSTP) here
    pid_t fg_pid = getpid(); // Get the current shell's PID
    if (fg_pid != getpid()) {
        kill(fg_pid, SIGTSTP); // Send Ctrl-Z to the foreground process
    }
}

int main()
{
    
    

    // typedef struct Process{
    //     int pid;
    //     char *processname;
    // }Process;
    // Keep accepting commands
    int count_of_history = 0;
    char *history[16];
    Process processids[1000];
    int countofprocessids=0;

    char cwd[1000];
    getcwd(cwd, sizeof(cwd));

    getcwd(directory, sizeof(directory));
    char previous_directory[1000];
    strcpy(previous_directory, directory);
    // printf("%s",cwd);
    char history_file_path[1000];

    // snprintf(history_file_path, sizeof(history_file_path), "%s/", cwd);
    strcpy(history_file_path, cwd);
    strcat(history_file_path, "/");
    strcat(history_file_path, HISTORY_FILE);


    load_history(&count_of_history, history, history_file_path);

        
    // signal(SIGTSTP, sigtstp_handler);
    while (1)
    {
        ctrl_c_pressed=1;
        // if (ctrl_c_pressed) {
        //     ctrl_c_pressed = 0; // Reset the Ctrl-C flag
        //     printf("\n");
        //     fflush(stdout); // Print a newline immediately
            
        //     prompt(directory); // Print the prompt immediately
        // } else {
        //     prompt(directory);
        // }
        // printf("----->%d",ctrl_c_pressed);
        //  if (ctrl_c_pressed) {
        //     ctrl_c_pressed = 0; // Reset the Ctrl-C flag
        //     printf("\n"); // Print a newline
        // }
        // prompt(directory);

        char input[4096];
        char copy_input[4096];
        signal(SIGINT, sigint_handler);  // Register Ctrl-C handler
        fgets(input, 4096, stdin);
        ctrl_c_pressed=0;
        strcpy(copy_input, input);
        char *stringsafterparsing[MAXARGUMENTS];
        char *copystringsafterparsing[MAXARGUMENTS];
        if(strcmp(input,"exit\n")==0){
            break;
        }
          if (ctrl_c_pressed) {
            ctrl_c_pressed = 0; // Reset the Ctrl-C flag
            printf("\n"); // Print a newline
        }
        int l = parsesemicolon(input, stringsafterparsing);

        for (int i = 0; i < l; i++)
        {
            copystringsafterparsing[i] = strdup(stringsafterparsing[i]);
            int u = strlen(copystringsafterparsing[i]);
            if (copystringsafterparsing[i][u - 1] == '\n')
            {
                copystringsafterparsing[i][u - 1] = '\0';
            }
        }


        for (int i = 0; i < l; i++)
        {
               
            parsespace(stringsafterparsing[i], copystringsafterparsing, i, &count_of_history, history, history_file_path, directory, previous_directory, copystringsafterparsing[i],processids,&countofprocessids);
        }

        prompt(directory);
    }
}
