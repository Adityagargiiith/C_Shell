#include "headers.h"
#include "prompt.h"

void executefgbg(char **input){
    int count=0;
    while(input[count]!=NULL){
        count++;
    }
    if(count<2){
        printf("invalid fgbg\n");
        return;
    }
    int pid=atoi(input[1]);

if(strcmp(input[0],"fg")==0){
    if(kill(pid,SIGCONT)==-1){
        printf("No process found\n");
        return;
    }
    int status;
// while(1){
    waitpid(pid,&status,WUNTRACED);
    // waitpid(pid,&status,0);
}
else if(strcmp(input[0],"bg")==0){
    if(kill(pid,SIGCONT)==-1){
        printf("No process found\n");
        return;
    }
}
}
    