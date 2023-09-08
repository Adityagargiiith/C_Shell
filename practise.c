#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>


int main() {
    char input[1024];
    printf("Enter a command (e.g., ls | grep keyword | wc):\n");
    fgets(input, sizeof(input), stdin);

    char *commands[1000];

char *copyofstringsafterparsing=strdup(input);

for(int i=0;i<1000;i++){
    commands[i]=strsep(&copyofstringsafterparsing,"|\n");
    if(commands[i]==NULL){
        break;
    }
    if(strlen(commands[i])==0){
        i--;
    }
    // count++;

}

int numCommands=0;
while (commands[numCommands]!=NULL)
{
    numCommands++;
    /* code */
}


    int pipes[numCommands - 1][2];

    for (int i = 0; i < numCommands - 1; i++) {
        if (pipe(pipes[i]) == -1) {
            perror("Pipe failed");
            return 1;
        }
    }

    for (int i = 0; i < numCommands; i++) {
        pid_t child = fork();

        if (child == -1) {
            perror("Fork failed");
            return 1;
        }
if (child == 0) {
    // Child process
    if (i > 0) {
        // Connect stdin of this command to the read end of the previous pipe
        dup2(pipes[i - 1][0], STDIN_FILENO);
        close(pipes[i - 1][0]);
    }

    if (i < numCommands - 1) {
        // Connect stdout of this command to the write end of the current pipe
        dup2(pipes[i][1], STDOUT_FILENO);
        close(pipes[i][1]);
    }

char *command[1000];

// char *copyofstringsafterparsing=strdup(input2);
// printf("%s++++\n",commands[i]);

char *copyofstrings=strdup(commands[i]);


for(int i=0;i<1000;i++){
    command[i]=strsep(&copyofstrings," \n\t");
    if(command[i]==NULL){
        break;
    }
    if(strlen(command[i])==0){
        i--;
    }
    // count++;

}
int count=0;
while (command[count]!=NULL)
{
    count++;
    /* code */
}
// printf("%d\n",count);
// for(int i=0;i<count;i++){
//     printf("%s-------\n",command[i]);
// }

    command[count] = NULL; // Null-terminate the argument list
    // for(int j=0;j<numArgs;j++){
    //     printf("%s-----\n",commandArgs[j]);
    // }

    // Execute the command with its arguments
    execvp(command[0], command);

    // If execvp fails, report an error
    perror("execvp");
    exit(1);
}

           
        else {
            // Parent process
            wait(NULL);
            if (i > 0) {
                // Close the read end of the previous pipe
                close(pipes[i - 1][0]);
            }
            
            if (i < numCommands - 1) {
                // Close the write end of the current pipe
                close(pipes[i][1]);
            }

            // Wait for the child to finish
        }
    }

    return 0;
}
