#include "headers.h"
#include "prompt.h"

void print_history(char **input2, int(*count_of_history), char **history, char *homedirectory, char *previous_directory,char *copy_of_input)
{

  // (*count_of_history)++;
  int count = 0;
  while (input2[count] != NULL)
  {
    count++;
  }

  if (count > 1)
  {
    if (strcmp(input2[1], "purge") == 0)
    {
      // printf("hello");
      for (int i = 0; i < (*count_of_history); i++)
      {
        history[i][0] = '\0';
        FILE *history_file = fopen("history.txt", "w");
        if (history_file != NULL)
        {
          fclose(history_file);
          // printf("History purged\n");
        }
        else
        {
          perror("Error purging history");
        }
      }
      *count_of_history = 0;
    }
    else if (strcmp(input2[1], "execute") == 0)
    {
      char *variable_input = malloc(sizeof(char) * 1000);
      int num = atoi(input2[2]);

      variable_input = strdup(history[num - 1]);
      // printf("%s\n",variable_input);

      char *parsedpipeargument[MAXARGUMENTS];

      for (int i = 0; i < MAXARGUMENTS; i++)
      {
        parsedpipeargument[i] = strsep(&variable_input, " \n\t");
        if (parsedpipeargument[i] == NULL)
        {
          break;
        }
        if (strlen(parsedpipeargument[i]) == 0)
        {
          i--;
        }
        count++;
      }
      int count = 0;
      while (parsedpipeargument[count] != NULL)
      {
        count++;
      }
      // for(int i=0;i<count;i++){
      //   printf("%s\n",parsedpipeargument[i]);
      // }
// printf("%s",copy_of_input);

      // continue;
      // if(input2)
      if (strcmp(parsedpipeargument[0], "warp") == 0)
      {
        char current_directory[1000];
        getcwd(current_directory, sizeof(current_directory));

        executewarp(parsedpipeargument, homedirectory, previous_directory);

        strcpy(previous_directory, current_directory);
      }

      else if (strcmp(parsedpipeargument[0], "peek") == 0)
      {
        executepeek(parsedpipeargument, homedirectory, previous_directory);
      }

      else if (strcmp(parsedpipeargument[0], "pastevents") == 0)
      {
        print_history(parsedpipeargument, count_of_history, history,homedirectory,previous_directory,copy_of_input);
      }

      else if (strcmp(parsedpipeargument[0], "proclore") == 0)
      {
        proclore(parsedpipeargument);
      }
      else if (strcmp(parsedpipeargument[0], "seek") == 0)
      {

        seek_command(parsedpipeargument,homedirectory,previous_directory);
      }
     

      // return;
    }
  }

else
{
  for (int i = 0; i < (*count_of_history); i++)
  {
    printf("%s\n", history[i]);
  }
}

// return;
}
