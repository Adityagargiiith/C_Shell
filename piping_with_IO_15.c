#include "headers.h"
#include "prompt.h"
// void execut_command2(char *outputfile,char*inputfile,char **args,int append){
//     // printf("%s",inputfile);

// }
int containsOnlySpacesOr(const char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] != ' ' && str[i] != '\t') {
            return 1; // Found a character that is not a space or tab
        }
    }
    return 0; // All characters are spaces or tabs
}

void executepipingwithIO(char *input){
    printf("------>\n");

char *commands[MAXARGUMENTS];
char *copyofstringsafterparsing=strdup(input);

for(int i=0;i<MAXARGUMENTS;i++){
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
if(numCommands<2){
    printf("invalid use of pipe\n");
    return;
}
for(int i=0;i<numCommands;i++){
    if(containsOnlySpacesOr(commands[i])==0){
        printf("invalid use of pipe\n");
        return;
    }

}

    int pipes[numCommands-1][2];

    for (int i = 0; i < numCommands - 1; i++) {
        if (pipe(pipes[i]) == -1) {
            perror("Pipe failed");
            return ;
        }
    }

    for (int i = 0; i < numCommands; i++) { 
        pid_t child = fork();

        if (child == -1) {
            perror("Fork failed");
            return ;
        }
if (child == 0) {
    char *inputFile = NULL;
            if (strchr(commands[i], '<') != NULL) {
                char *token = strtok(commands[i], "< ");
                inputFile = strtok(NULL, "< ");
                int fd_in = open(inputFile, O_RDONLY);
                dup2(fd_in, STDIN_FILENO);
                close(fd_in);
            }
                printf("%s",inputFile);

            // Set up output redirection if needed
            char *outputFile = NULL;
            int append = 0;
            if (strchr(commands[i], '>') != NULL) {
                char *token = strtok(commands[i], "> ");
                outputFile = strtok(NULL, "> ");
                if (strchr(token, '>') != NULL) {
                    append = 1;
                }
                int fd_out;
                if (append) {
                    fd_out = open(outputFile, O_WRONLY | O_CREAT | O_APPEND, 0666);
                } else {
                    fd_out = open(outputFile, O_WRONLY | O_CREAT | O_TRUNC, 0666);
                }
                dup2(fd_out, STDOUT_FILENO);
                close(fd_out);
            }

    if (i > 0) {
        dup2(pipes[i - 1][0], STDIN_FILENO);//use to connect input of the previous command to the input descryptor of current command. So now basically it reads the previous input
        close(pipes[i - 1][0]);
    }

    if (i < numCommands - 1) {
        dup2(pipes[i][1], STDOUT_FILENO);//writes in the current pipe
        close(pipes[i][1]);
    }
    // printf("%s\n",commands[i]);
// if(strstr(commands[i],">")!=NULL || strstr(commands[i],">>")!=NULL||strstr(commands[i],"<")!=NULL){
//     input_output(input);
// }
// else{
    
char *command[MAXARGUMENTS];

// char *copyofstringsafterparsing=strdup(input2);
// printf("%s++++\n",commands[i]);

char *copyofstrings=strdup(commands[i]);


for(int i=0;i<MAXARGUMENTS;i++){
    command[i]=strsep(&copyofstrings," \n\t");
    if(command[i]==NULL){
        break;
    }
    if(strlen(command[i])==0){
        i--;
    }
    // count++;

}
    // printf("%s hello",command[0]);
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

    command[count] = NULL; // Nu

    if(strcmp(command[0],"sed")==0 && count>2){
    // printf("hello\n");
         command[1] = "-e"; 
    command[2] = "s/ //g"; 

    // Execute the modified command
    execvp(command[0], command);

    // If execvp fails, report an error
    perror("execvp");
    exit(1);
// char *newcommand={"sed","-e","s/old_text/new_text/g", NULL};
// execvp(command[0], command);
// perror("execvp");
// exit(1);
}

else{
execvp(command[0], command);
    perror("execvp");
    exit(1);

// }
}

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



// printf("%d\n",count);
// for(int i=0;i<count;i++){
//     printf("%s\n",parsedpipeargument[i]);
// }
// if(count < 2){

// return;
// }
// printf("%d",count);
}