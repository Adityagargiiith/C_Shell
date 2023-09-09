#include "headers.h"

#include "prompt.h"

#define BUFFER_SIZE 1000
int compareProcesses(const void *a, const void *b) {
    return strcmp(((struct Process *)a)->processname, ((struct Process *)b)->processname);
}


void iman(Process *processids,int *countofprocess){
    

}

