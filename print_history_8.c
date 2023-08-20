#include "headers.h"
#include "prompt.h"


void print_history(char **input2,int (*count_of_history),char **history){

    // (*count_of_history)++;
     int count = 0;
  while (input2[count] != NULL)
  {
    count++;
  }

  if(count>1){
    if(strcmp(input2[1],"purge")==0){
        // printf("hello");
for(int i=0;i<(*count_of_history);i++){
    history[i][0]='\0';
}
 *count_of_history=0;
    }
    else if(strcmp(input2[1],"execute")==0){

        // continue;
// if(input2)

    }
 
  }
  else{
       for(int i=0;i<(*count_of_history);i++){
            printf("%s\n",history[i]);
        }
  }

    // return;
}

