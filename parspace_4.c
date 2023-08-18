#include "headers.h"
#include "prompt.h"


void parsespace(char *input2) {
// printf("%s",input200);

// char *arguments[1000];
int count=0;
char *parsedpipeargument[MAXARGUMENTS];

for(int i=0;i<MAXARGUMENTS;i++){
    parsedpipeargument[i]=strsep(&input2," \n");
    if(parsedpipeargument[i]==NULL){
        break;
    }
    if(strlen(parsedpipeargument[i])==0){
        i--;
    }
    count++;
    
}
// printf("%s",parsedpipeargument[0]);

if(strcmp(parsedpipeargument[0],"warp")==0){
    // printf("hello");
executewarp(parsedpipeargument);
}

if(strcmp(parsedpipeargument[0],"peek")==0){
    // printf("hello");
executepeek(parsedpipeargument);
}


// printf("%s\n",parsedpipeargument[1]);
// for(int i=0;i<count;i++){
//     printf("%s\n",parsedpipeargument[i]);
// }
// return count;
   
    // return;
}

