#include "headers.h"

#include "prompt.h"

#define BUFFER_SIZE 1000
int compareProcesses(const void *a, const void *b) {
    return strcmp(((struct Process *)a)->processname, ((struct Process *)b)->processname);
}


void activities(Process *processids,int *countofprocess){

// char *name[1000];
// char *status[1000];
// printf("%d\n",*countofprocess);
int count=0;     
    qsort(processids, *countofprocess, sizeof(struct Process), compareProcesses);

    for(int i=0;i<*countofprocess;i++){
        char name[1000];
        char status;
        char statusfile[1000];
        char statPath[256];
            snprintf(statPath, sizeof(statPath), "/proc/%d/status", processids[i].pid);

            FILE *statfile = fopen(statPath, "r");
            if (statfile == NULL) {
               
        continue;
            }
            else{
                // printf("%d",);
                char line[1000];
        while (fgets(line, sizeof(line), statfile)) {
            

            if (strncmp(line, "State:", 6) == 0) {
                sscanf(line,"State: %c", &status);
                // printf("%c\n",status);
                if(status=='S'){
                    strcpy(statusfile,"Running");
                }
                else if(status=='T'){ 
                    strcpy(statusfile,"Stopped");
                }
                else{
                    continue;
                }
                // printf("%c\n",status);
    printf("%d : %s - %s\n",processids[i].pid,processids[i].processname,statusfile);
            }
        }
        count++;
        fclose(statfile);
        // sigint
            }
    }

// char *name[1000];
// char *status[1000];
// int count=0;
//     for(int i=0;i<*countofprocess;i++){
// // int pid=processids[i];
// char path[1000];
// snprintf(path,sizeof(path),"/proc/%d/status",processids[i]);

// FILE *file=fopen(path,"r");
// if(file==NULL){
//     printf("nofile");
//     continue;
// }
// // char *name=malloc(sizeof(char)*1000);
// // char *status=malloc(sizeof(char)*1000);
// char *line=malloc(sizeof(char)*1000);
// while(fgets(line,sizeof(line),file)){
//     if(strncmp(line,"Name:",5)==0){
//         sscanf(line+5,"%s",name[count]);
//     }
//     if(strncmp(line,"State:",6)==0){
//         sscanf(line+6,"%s",status[count]);
//     }
// }
// count++;
// fclose(file);
//     }

// for(int i=0;i<count;i++){
// }
}

