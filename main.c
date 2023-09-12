#include "headers.h"

    char directory[100];
   int foregroundprocessid =0;
void sigint_handler(int sig)
{
    kill(foregroundprocessid,SIGINT);
    printf("\n");
}
void sigtstp_handler(int sig)
{  
    // printf("%d\n",foregroundprocessid);
    // if()
    kill(foregroundprocessid,SIGSTOP);
        kill(foregroundprocessid,SIGTSTP);
        printf("\n");
}
// void si

int main()
{
    // shellpid=getpid();
    int count_of_history = 0;
    char *history[16];
    Process processids[1000];

    int countofprocessids = 0;
// printf("%d-->terminal\n",getpid());
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
    // trap 'sigint_handler' SIGINT
    signal(SIGINT, sigint_handler);
    signal(SIGTSTP, sigtstp_handler);
    while (1)
    {
        prompt(directory);


        char input[4096];
        char copy_input[4096];
        if (fgets(input, 4096, stdin) == NULL)
        {
            // for(int i=0;i<countofprocessids;i++){
                kill(0,SIGTERM);
            
printf("\n");
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
