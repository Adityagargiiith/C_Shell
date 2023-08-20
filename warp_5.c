#include "headers.h"
#include "prompt.h"


void executewarp(char **input2) {
    char new_directory[10000];
    char current_directory[1000];
        getcwd(current_directory,sizeof(current_directory));
        // printf("%s\n",current_directory);
        int count=0;
         while (input2[count] != NULL) {
        count++;
    }
// printf("%d",count);


// if(count==1)
// for(int )
if(count==1){
      char *home_dir = getenv("HOME");
    chdir(home_dir);
    getcwd(new_directory,sizeof(new_directory));
printf("%s\n",new_directory);
return;
}

else if(strcmp(input2[1],"~")==0){
          char *home_dir = getenv("HOME");
    chdir(home_dir);
    getcwd(new_directory,sizeof(new_directory));
printf("%s\n",new_directory);
}

else if(strcmp(input2[1],"..")==0 || strcmp(input2[1],".")==0){
  chdir(input2[1]);
    getcwd(new_directory,sizeof(new_directory));
printf("%s\n",new_directory);

}



else{
  
 char *path = (char *)malloc(sizeof(char)*(strlen(input2[1]+1)));
 strcpy(path,input2[1]);

 char new_directory[10000];
//  char *path="hello";
 char dash[10]="/";
//  char some[6]="truef";
 
    // getcwd(directory,sizeof(directory));
    // printf("%s\n",directory);
//  strcat(current_directory,some);
    strcat(current_directory,dash);
    strcat(current_directory,path);
    //  strcat(current_directory,some);
    
    strcat(current_directory,dash);
    // int l=strlen(current_directory);
    // current_directory[l]='/';
    // strcat(current_directory,dash);
    // current_directory[strlen(current_directory)-1]='/';
    printf("%s\n",current_directory);
    //   char *home_dir = getenv("HOME");
  int l=  chdir(current_directory);
//   int p=chdir('-');
//   printf("%d",l);
// if(l==0){
//   getcwd(new_directory,sizeof(new_directory));
// printf("%s\n",new_directory);
// }
// else{
//     printf("invalid command");
// }
}

    // return;
}

