#include "headers.h"
#include "prompt.h"

char *directoryforpath(char *target_directory, char *word)
{

    DIR *directory;
    struct dirent *entry;
    if ((directory = opendir(target_directory)) == NULL)
    {

        printf("No match found");

    }
    int flag = 0;
    while ((entry = readdir(directory)) != NULL)
    {

        if (strcmp(entry->d_name, "..") == 0 || strcmp(entry->d_name, ".") == 0)
        {
          continue;
        }

        char *fullpath=malloc(sizeof(char)*1000);

        strcpy(fullpath, target_directory);

        strcat(fullpath, "/");

        strcat(fullpath, entry->d_name);

        struct stat STAT;
        if (stat(fullpath, &STAT) < 0)
        {
            continue;

        }
        if (S_ISDIR(STAT.st_mode))
        {
            if (strstr(entry->d_name, word) != NULL)
            {

                flag = 1;

                return fullpath;

            }

            directoryforpath(fullpath, word);
        }

    }

    return NULL;
}

void seek_recursion_flag_with_e(char *target_directory, char *word, char *relativepath, int flagd, int flagf, int flage, int *count)
{

    DIR *directory;

    struct dirent *entry;

    if ((directory = opendir(target_directory)) == NULL)
    {
        printf("No match found");
        return;
    }
    // int count = 0;
    while ((entry = readdir(directory)) != NULL)
    {
        if (strcmp(entry->d_name, "..") == 0 || strcmp(entry->d_name, ".") == 0)
        {
            continue;
        }

        char fullpath[10000];
        strcpy(fullpath, target_directory);
        strcat(fullpath, "/");
        strcat(fullpath, entry->d_name);

        char newrelativepath[1000];
        snprintf(newrelativepath, sizeof(newrelativepath), "%s/%s", relativepath, entry->d_name);
        struct stat STAT;
        if (stat(fullpath, &STAT) < 0)
        {

            continue;
        }
        if (S_ISDIR(STAT.st_mode) && flagf == 0)
        {
            if (strstr(entry->d_name, word) != NULL)
            {
                // flag=1;
                (*count)++;
                // printf("%s\n",newrelativepath);
            }
            seek_recursion_flag_with_e(fullpath, word, newrelativepath, flagd, flagf, flage,count);
        }
    }
    if (count == 0)
    {
        printf("No match found");
    }
    return;
}

void seek_recursion_flag(char *target_directory, char *word, char *relativepath, int flagd, int flagf, int flage)
{

    DIR *directory;
    //  int count = 0;
    struct dirent *entry;

    if ((directory = opendir(target_directory)) == NULL)
    {
        printf("No match found");
        return;
    }
    int flag = 0;
    while ((entry = readdir(directory)) != NULL)
    {
        if (strcmp(entry->d_name, "..") == 0 || strcmp(entry->d_name, ".") == 0)
        {
            continue;
        }

        char fullpath[10000];
        strcpy(fullpath, target_directory);
        strcat(fullpath, "/");
        strcat(fullpath, entry->d_name);

        char newrelativepath[1000];
        snprintf(newrelativepath, sizeof(newrelativepath), "%s/%s", relativepath, entry->d_name);
        struct stat STAT;
        if (stat(fullpath, &STAT) < 0)
        {
            continue;
        }
        if (S_ISDIR(STAT.st_mode) && flagf == 0)
        {
            if (strstr(entry->d_name, word) != NULL)
            {
                flag = 1;
                printf("%s\n", newrelativepath);
            }
            seek_recursion_flag(fullpath, word, newrelativepath, flagd, flagf, flage);
        }
        else if (S_ISREG(STAT.st_mode) && flagd == 0)
        {
            if (strstr(entry->d_name, word) != NULL)
            {
                flag = 2;
                printf("%s\n", newrelativepath);
            }
        }
    }
    if (flag == 0)
    {
        printf("No match found");
    }
}

void seek_recursion(char *target_directory, char *word, char *relativepath)
{
    // printf("%d",*count_of_history);

    // chdir()
    DIR *directory;
    //  int count = 0;
    struct dirent *entry;

    if ((directory = opendir(target_directory)) == NULL)
    {
        printf("No match found");
        return;
    }
    int flag = 0;
    while ((entry = readdir(directory)) != NULL)
    {
        if (strcmp(entry->d_name, "..") == 0 || strcmp(entry->d_name, ".") == 0)
        {
            continue;
        }

        char fullpath[10000];
        strcpy(fullpath, target_directory);
        strcat(fullpath, "/");
        strcat(fullpath, entry->d_name);

        char newrelativepath[1000];
        snprintf(newrelativepath, sizeof(newrelativepath), "%s/%s", relativepath, entry->d_name);
        struct stat STAT;
        if (stat(fullpath, &STAT) < 0)
        {
            continue;
        }
        if (S_ISDIR(STAT.st_mode))
        {
            if (strstr(entry->d_name, word) != NULL)
            {
                flag = 1;
                printf("%s\n", newrelativepath);
            }
            seek_recursion(fullpath, word, newrelativepath);
        }
        else if (S_ISREG(STAT.st_mode))
        {
            if (strstr(entry->d_name, word) != NULL)
            {
                flag = 2;
                printf("%s\n", newrelativepath);
            }
        }
    }
    if (flag == 0)
    {
        printf("No match found");
    }
}

void seek_command(char **input2)
{

    int count = 0;
    while (input2[count] != NULL)
    {
        count++;
    }

    char *relativepath = ".";

    if (count == 3)
    {
        if (strcmp(input2[1], "-d") != 0 && strcmp(input2[1], "-f") != 0 && strcmp(input2[1], "-e") != 0)
            seek_recursion(input2[2], input2[1], relativepath);

        else
        {
            if (strcmp(input2[1], "-d") == 0)
                seek_recursion_flag(relativepath, input2[2], relativepath, 1, 0, 0);
            if (strcmp(input2[1], "-f") == 0)
                seek_recursion_flag(relativepath, input2[2], relativepath, 0, 1, 0);
            if (strcmp(input2[1], "-e") == 0)
                printf("invalid flag");
            // seek_recursion_flag(relativepath,input2[2],relativepath,0,0,1);
        }
    }
    else if (count == 2)
    {
        char *target_directory = ".";
        seek_recursion(target_directory, input2[1], relativepath);
    }

    else if (count == 4)
    {
        if (strcmp(input2[1], "-d") == 0 && strcmp(input2[2],"-f")!=0 && strcmp(input2[2],"-e")!=0 )
        {
            seek_recursion_flag(input2[3], input2[2], relativepath, 1, 0, 0);
        }

        else if (strcmp(input2[1], "-f") == 0 && strcmp(input2[2],"-d")!=0 && strcmp(input2[2],"-e")!=0 )
        {
            seek_recursion_flag(input2[3], input2[2], relativepath, 0, 1, 0);
        }
        else if((strcmp(input2[1],"-d")==0 && strcmp(input2[2],"-e")==0) || (strcmp(input2[2],"-d")==0 && strcmp(input2[1],"-e")==0))
        {


 int count = 0;
//  printf("hello");
char *newrelativepath=".";

            seek_recursion_flag_with_e(newrelativepath, input2[3] , relativepath, 1, 0, 0, &count);

            if (count == 1)
            {
                char *newdirectory = directoryforpath(newrelativepath, input2[3]);
                printf("%s\n",newdirectory);
                // printf("he;;");
                chdir(newdirectory);

            }

        }
    else if((strcmp(input2[1],"-f")==0 && strcmp(input2[2],"-e")==0) || (strcmp(input2[1],"-e")==0 && strcmp(input2[2],"-f")==0))
        {

            seek_recursion_flag( ".",input2[3] , relativepath, 0, 1, 0);

    }

    else{

        printf("invalid flags");

    }

 }


    else if (count == 5)
    {

        if ((strcmp(input2[1], "-d") == 0 && strcmp(input2[2], "-e") == 0) || (strcmp(input2[1], "-e") == 0 && strcmp(input2[2], "-d") == 0))
        {
            int count = 0;
            seek_recursion_flag_with_e(input2[4], input2[3], relativepath, 1, 0, 0, &count);
                        // printf("%d",count);

            if (count == 1)
            {
                char *newdirectory = directoryforpath(input2[4], input2[3]);
                printf("%s\n",newdirectory);
                // printf("he;;");
                chdir(newdirectory);

            }
        }

      else if ((strcmp(input2[1], "-f") == 0 && strcmp(input2[2], "-e") == 0) || (strcmp(input2[1], "-e") == 0 && strcmp(input2[2], "-f") == 0))

        {

            seek_recursion_flag(input2[4], input2[3], relativepath, 0, 1, 0);

        }
        else
        {
            printf("invalid flags");
        }
    }
}
