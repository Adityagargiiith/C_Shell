#include "headers.h"
#include "prompt.h"
// extern int count_of_history_1;
// count_of_history_1=0;

void parsespace(char *input2,char ** stringsafterpartsing,int v,int *count_of_history,char **history) {
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
// char *history[16];

if(strcmp(parsedpipeargument[0],"warp")==0){
    // printf("hello");
executewarp(parsedpipeargument);
// add_to_history()
// printf("%s",stringsafterpartsing[0]);
add_to_history(stringsafterpartsing,v,count_of_history,history);
save_history(stringsafterpartsing,v,count_of_history,history);

// (*count_of_history)++;
// printf("%d",*count_of_history);
// count_of_history_1++;
// printf("%d",count_of_history_1);
// add_to_history(stringsafterpartsing,v,count_of_history,history);

}

if(strcmp(parsedpipeargument[0],"peek")==0){
    // printf("hello");
executepeek(parsedpipeargument);
add_to_history(stringsafterpartsing,v,count_of_history,history);
save_history(stringsafterpartsing,v,count_of_history,history);


}


if(strcmp(parsedpipeargument[0],"pastevents")==0){
// add_to_history(stringsafterpartsing,v);
print_history(parsedpipeargument,count_of_history,history);
// printf("%s\n",parsedpipeargument[1]);
// for(int i=0;i<count;i++){
//     printf("%s\n",parsedpipeargument[i]);
}

if(strcmp(parsedpipeargument[0],"proclore")==0){
// add_to_history(stringsafterpartsing,v);
proclore(parsedpipeargument);
add_to_history(stringsafterpartsing,v,count_of_history,history);
save_history(stringsafterpartsing,v,count_of_history,history);
// printf("%s\n",parsedpipeargument[1]);
// for(int i=0;i<count;i++){
//     printf("%s\n",parsedpipeargument[i]);
}
// return count;
   
    // return;
}

