#ifndef __PROMPT_H
#define __PROMPT_H


void prompt();
int parsesemicolon(char *input2,char **arguments);
void parsespace(char *input2,char ** stringsafterpartsing,int v,int *count_of_history,char **history);
void executewarp(char **input2);
void executepeek(char **input2);
// void executepastevents(char **input2);
void storehistory(char **input2);
void add_to_history(char **input2,int count,int *count_of_history,char **history);
void proclore(char **input2);

void print_history(char **input2,int *count_of_history,char **history);
void proclore(char **input2);
void save_history(char **input2,int count,int *count_of_history,char **history);

#define ANSI_COLOR_GREEN   "\x1b[32m"  
#define ANSI_COLOR_WHITE   "\x1b[0m"  
#define ANSI_COLOR_BLUE    "\x1b[34m"  
#define ANSI_COLOR_RESET   "\x1b[0m"

// void warp();

#endif