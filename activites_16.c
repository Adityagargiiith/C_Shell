#include "headers.h"

#include "prompt.h"

#define BUFFER_SIZE 1000
int compareProcesses(const void *a, const void *b) {
    return strcmp(((struct Process *)a)->processname, ((struct Process *)b)->processname);
}


void activities(Process *processids,int *countofprocess){
     

    qsort(processids, *countofprocess, sizeof(struct Process), compareProcesses);

    for(int i=0;i<*countofprocess;i++){
        char statPath[256];
            snprintf(statPath, sizeof(statPath), "/proc/%d/stat", processids[i].pid);

            FILE *statFile = fopen(statPath, "r");
            if (statFile == NULL) {
        printf("%d: %s -Stopped\n",processids[i].pid,processids[i].processname);
        // printf("%s\n",processids[i].processname);

                
            }
            else{
                        printf("%d: %s -Running\n",processids[i].pid,processids[i].processname);

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
//     printf("%d %s %s\n",processids[i],name[i],status[i]);
// }
}

