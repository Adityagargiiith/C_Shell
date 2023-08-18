#ifndef __PROMPT_H
#define __PROMPT_H

void prompt();
int parsesemicolon(char *input2,char **arguments);
void parsespace(char *input2);
void executewarp(char **input2);
void executepeek(char **input2);
// void warp();

#endif