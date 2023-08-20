#include "headers.h"
#include "prompt.h"



void save_history(char **input2,int count,int *count_of_history,char **history) {
    // printf("%d",*count_of_history);
    FILE *file=fopen(HISTORY_FILE,"w");
    
    for(int i=0;i<(*count_of_history);i++){
    fprintf(file,"%s\n",history[i]);    

    }

    fclose(file);

     }

    

    // return;

