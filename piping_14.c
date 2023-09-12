#include "headers.h"
#include "prompt.h"

int containsOnlySpacesOrTabs(const char *str)
{
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (str[i] != ' ' && str[i] != '\t')
        {
            return 1; 
        }
    }
    return 0; 
}

void executepiping(char *input,char *homedirectory,char *previousdirectory)
{

    char *commands[MAXARGUMENTS];
    char *copyofstringsafterparsing = strdup(input);

    for (int i = 0; i < MAXARGUMENTS; i++)
    {
        commands[i] = strsep(&copyofstringsafterparsing, "|\n");
        if (commands[i] == NULL)
        {
            break;
        }
        if (strlen(commands[i]) == 0)
        {
            i--;
        }
        // count++;
    }

    int numCommands = 0;
    while (commands[numCommands] != NULL)
    {
        numCommands++;
        /* code */
    }
    if (numCommands < 2)
    {
        printf("invalid use of pipe\n");
        return;
    }
    for (int i = 0; i < numCommands; i++)
    {
        if (containsOnlySpacesOrTabs(commands[i]) == 0)
        {
            printf("invalid use of pipe\n");
            return;
        }
    }

    int pipes[numCommands - 1][2];

    for (int i = 0; i < numCommands - 1; i++)
    {
        if (pipe(pipes[i]) == -1)
        {
            perror("Pipe failed");
            return;
        }
    }

    for (int i = 0; i < numCommands; i++)
    {
        pid_t child = fork();

            // printf("hello\n");
        if (child == -1)
        {
            perror("Fork failed");
            return;
        }
        
        if (child == 0)
        {
            if (i > 0)
            {
                dup2(pipes[i - 1][0], STDIN_FILENO); // use to connect input of the previous command to the input descryptor of current command. So now basically it reads the previous input
                close(pipes[i - 1][0]);
            }

            if (i < numCommands - 1)
            {
                dup2(pipes[i][1], STDOUT_FILENO); // writes in the current pipe
                close(pipes[i][1]);
            }

            char *command[MAXARGUMENTS];

            char *copyofstrings = strdup(commands[i]);

            for (int i = 0; i < MAXARGUMENTS; i++)
            {
                command[i] = strsep(&copyofstrings, " \n\t");
                if (command[i] == NULL)
                {
                    break;
                }
                if (strlen(command[i]) == 0)
                {
                    i--;
                }
                // count++;
            }
            // printf("%s hello",command[0]);
            int count = 0;
            while (command[count] != NULL)
            {
                count++;
                /* code */
            }


            command[count] = NULL; // Nu
            // fflush(stdout);

            if (strcmp(command[0], "sed") == 0 && count > 2)
            {
                // printf("hello\n");
                command[1] = "-e";
                command[2] = "s/ //g";
                execvp(command[0], command);
                perror("execvp");
                exit(1);
            }
            else if(strcmp(command[0],"warp")==0){
                executewarp(command,homedirectory,previousdirectory);
                fflush(stdout);
                return;
            }
            else if(strcmp(command[0],"peek")==0){
                printf("hello\n");
                // stdout.flus
                            // fflush(stdout);

                executepeek(command,homedirectory,previousdirectory);
                // fflush(stdout);
                return;
            }
            else if(strcmp(command[0],"seek")==0){
                seek_command(command,homedirectory,previousdirectory);
                return;
            }
            else if(strcmp(command[0],"proclore")==0){
                proclore(command,homedirectory);
                return;
            }
            else
            {
                execvp(command[0], command);
                perror("execvp");
                exit(1);
            }
        }

        else
        {
            // Parent process
            wait(NULL);
            if (i > 0)
            {
                close(pipes[i - 1][0]);
            }

            if (i < numCommands - 1)
            {
                close(pipes[i][1]);
            }

        }
    }

    // printf("%d\n",count);
    // for(int i=0;i<count;i++){
    //     printf("%s\n",parsedpipeargument[i]);
    // }
    // if(count < 2){

    // }
    // printf("%d",count);
}