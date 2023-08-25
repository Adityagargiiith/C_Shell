#include "headers.h"
#include "prompt.h"
// extern int count_of_history_1;
// count_of_history_1=0;

void parsespace(char *input2,char ** stringsafterpartsing,int v,int *count_of_history,char **history,char *history_file_path,char *homedirectory,char *previous_directory,char *copy_of_input) {


int count=0;
char *parsedpipeargument[MAXARGUMENTS];


for(int i=0;i<MAXARGUMENTS;i++){
    parsedpipeargument[i]=strsep(&input2," \n\t");
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
    char current_directory[1000];
    getcwd(current_directory,sizeof(current_directory));
    
executewarp(parsedpipeargument,homedirectory,previous_directory);

add_to_history(stringsafterpartsing,v,count_of_history,history);

save_history(stringsafterpartsing,v,count_of_history,history,history_file_path);
strcpy(previous_directory,current_directory);


}

else if(strcmp(parsedpipeargument[0],"peek")==0){
    // printf("hello");
executepeek(parsedpipeargument,homedirectory,previous_directory);
add_to_history(stringsafterpartsing,v,count_of_history,history);
save_history(stringsafterpartsing,v,count_of_history,history,history_file_path);


}


else if(strcmp(parsedpipeargument[0],"pastevents")==0){
// add_to_history(stringsafterpartsing,v);
print_history(parsedpipeargument,count_of_history,history,homedirectory,previous_directory,copy_of_input);

}

else if(strcmp(parsedpipeargument[0],"proclore")==0){
// add_to_history(stringsafterpartsing,v);
proclore(parsedpipeargument);
add_to_history(stringsafterpartsing,v,count_of_history,history);
save_history(stringsafterpartsing,v,count_of_history,history,history_file_path);

}
else if(strcmp(parsedpipeargument[0],"seek")==0){

seek_command(parsedpipeargument);
add_to_history(stringsafterpartsing,v,count_of_history,history);
save_history(stringsafterpartsing,v,count_of_history,history,history_file_path);

}
else{
    executeprocess(copy_of_input);
    add_to_history(stringsafterpartsing,v,count_of_history,history);
save_history(stringsafterpartsing,v,count_of_history,history,history_file_path);

}
   
    // return;
}

