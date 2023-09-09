#include "headers.h"

    char directory[100];
   int foregroundprocessid =0;
void sigint_handler(int sig)
{
    printf("\n");
}

void sigtstp_handler(int sig)
{
    // if(sig==SIGTSTP){

    printf("%d\n",foregroundprocessid);

      if (foregroundprocessid != 0)
    {
        kill(foregroundprocessid, SIGSTOP);
        printf("\nProcess %d suspended.\n", foregroundprocessid);
        foregroundprocessid = 0;
    }
    else{
        // printf("hello");
         printf("\nCtrl-Z pressed, but not suspending the shell.\n");
    }
    // }

}

int main()
{
    // shellpid=getpid();
    int count_of_history = 0;
    char *history[16];
    Process processids[1000];

    int countofprocessids = 0;

    char cwd[1000];
    getcwd(cwd, sizeof(cwd));

    getcwd(directory, sizeof(directory));
    char previous_directory[1000];
    strcpy(previous_directory, directory);
    char history_file_path[1000];

    strcpy(history_file_path, cwd);
    strcat(history_file_path, "/");
    strcat(history_file_path, HISTORY_FILE);
    load_history(&count_of_history, history, history_file_path);

//   setpgid(0, 0);
    signal(SIGINT, sigint_handler);
    signal(SIGTSTP, sigtstp_handler);
    while (1)
    {
        prompt(directory);

        char input[4096];
        char copy_input[4096];
        if (fgets(input, 4096, stdin) == NULL)
        {

            // Ctrl+D (EOF) was detected. Exit the shell gracefully.
            // printf("Logging out of the shell...\n");
            break;
        }

        // fgets(input, 4096, stdin);
        strcpy(copy_input, input);
        char *stringsafterparsing[MAXARGUMENTS];
        char *copystringsafterparsing[MAXARGUMENTS];
        if (strcmp(input, "exit\n") == 0)
        {
            break;
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

            parsespace(stringsafterparsing[i], copystringsafterparsing, i, &count_of_history, history, history_file_path, directory, previous_directory, copystringsafterparsing[i], processids, &countofprocessids);
        }
    }
}
