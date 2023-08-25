#include "headers.h"
// #include

int main()
{
    // Keep accepting commands
    int count_of_history = 0;
    char *history[16];

    char cwd[1000];
    getcwd(cwd, sizeof(cwd));

    char directory[100];
    getcwd(directory, sizeof(directory));
    char previous_directory[1000];
    strcpy(previous_directory, directory);
    // printf("%s",cwd);
    char history_file_path[1000];

    // snprintf(history_file_path, sizeof(history_file_path), "%s/", cwd);
    strcpy(history_file_path, cwd);
    strcat(history_file_path, "/");
    strcat(history_file_path, HISTORY_FILE);

    load_history(&count_of_history, history, history_file_path);

    while (1)
    {
        // Print appropriate prompt with username, systemname and directory before accepting input
        prompt(directory);
        char input[4096];
        char copy_input[4096];
        fgets(input, 4096, stdin);
        strcpy(copy_input, input);
        char *stringsafterparsing[MAXARGUMENTS];
        char *copystringsafterparsing[MAXARGUMENTS];

        int l = parsesemicolon(input, stringsafterparsing);

        for (int i = 0; i < l; i++)
        {
            copystringsafterparsing[i] = strdup(stringsafterparsing[i]);
            int u = strlen(copystringsafterparsing[i]);
            if (copystringsafterparsing[i][u - 1] == '\n')
            {
                copystringsafterparsing[i][u - 1] = '\0';
            }
        }

        // printf("%d",u);
        for (int i = 0; i < l; i++)
        {
            parsespace(stringsafterparsing[i], copystringsafterparsing, i, &count_of_history, history, history_file_path, directory, previous_directory, copystringsafterparsing[i]);
        }

    }
}
