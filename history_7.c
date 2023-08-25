#include "headers.h"
#include "prompt.h"


void add_to_history(char **input2,int count,int *count_of_history,char **history) {
    // printf("%d",*count_of_history);
    if((*count_of_history)<15){
        
        if((*count_of_history)==0 || strcmp(history[*count_of_history - 1], input2[count]) != 0){
        history[(*count_of_history)]=strdup(input2[count]);
            (*count_of_history)++;

        // printf("%s\n",history[(*count_of_history)-1]);

        }

    }
        else{
            // printf("%d",*count_of_history);

            if(strcmp(history[14],input2[count])!=0){
            for(int i=0;i<14;i++){
          strcpy(history[i],history[i+1]);
            }
  strcpy(history[14],input2[count]);
            } 
        }
    }

    

    // return;

