#include "headers.h"
#include "prompt.h"
void process_single_command(char * input2,int flag){

 
char *parsedpipeargument[MAXARGUMENTS];
int count=0;

for(int i=0;i<MAXARGUMENTS;i++){
    parsedpipeargument[i]=strsep(&input2," \n\t");
    if(parsedpipeargument[i]==NULL){
        break;
    }
    if(strlen(parsedpipeargument[i])==0){
        i--;
    }
    // count++;
}


while (parsedpipeargument[count]!=NULL){
    count++;
}
pid_t pid;
int status;

  pid = fork();
    if (pid == 0) {
        // Child process
        execvp(parsedpipeargument[0], parsedpipeargument);
        perror("Error");
        exit(1);
    } else if (pid > 0) {
        // Parent process
        if(flag==1){
         printf("[%d]\n", pid);
        // waitpid(pid, &status, 0);
        }
        else{
              waitpid(pid, &status, 0);
        if (WIFEXITED(status)) {
            printf("%s exited normally\n", parsedpipeargument[0]);
        } else {
            printf("%s exited abnormally\n", parsedpipeargument[0]);
        }

        }
    
    } else {
        perror("Fork error");
    }


}

void executeprocess(char *input2)
{

    int count = 0;
    char parsedpipeargument[MAXARGUMENTS][MAXARGUMENTS];
    
    int l=strlen(input2);
   for (int i = 0; i < l; i++) {
    int flag=0;
        if (input2[i] == '&') {
            // parsedpipeargument[count] = malloc(i + 1); 
            strncpy(parsedpipeargument[count], input2, i); 
            parsedpipeargument[count][i] = '\0'; 
            flag=1;
            char copy[1000];
            strcpy(copy,parsedpipeargument[count]);
            process_single_command(copy,flag); 
            // free(parsedpipeargument[count]); 
            
            input2 += i + 1; // Move the input pointer after the '&'
             l-= i + 1; // Adjust the remaining input length
            i = -1; // Reset the loop index
            count++;
        }

    }
    if(l>0){
        char copy[1000];
        strcpy(parsedpipeargument[count],input2);
        strcpy(copy,parsedpipeargument[count]);
        process_single_command(copy,0);

    }
    // printf("%d",count);


}


