#include "headers.h"
// #include 

int main()
{
    // Keep accepting commands
    while (1)
    {
        // Print appropriate prompt with username, systemname and directory before accepting input
        prompt();
        char input[4096];
        char copy_input[4096];
        fgets(input, 4096, stdin);
        strcpy(copy_input,input);
char *stringsafterparsing[MAXARGUMENTS];

int l=parsesemicolon(input,stringsafterparsing);

for(int i=0;i<l;i++){
    parsespace(stringsafterparsing[i]);
//    printf("%s\n",stringsafterparsing[i]) ;
    
}


// for(int i=0;i<3;i++){
//     printf("%s\n",stringsafterparsing[i]);
// }
    
// printf("%d",l);
  

}
}


    

