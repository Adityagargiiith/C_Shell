#include "headers.h"
#include "prompt.h"

int compare_strings(const void *a, const void *b)
{
  return strcmp(*(const char **)a, *(const char **)b);
}

void print_permissions(mode_t mode) {
    char perms[] = "rwxrwxrwx"; // All permission characters
    char type;

    if (S_ISDIR(mode)) {
        type = 'd';
    } else {
        type = '-';
    }

    for (int i = 0; i < 9; i++) {
        if (!(mode & (1 << (8 - i)))) {
            perms[i] = '-';
        }
    }

    printf("%c%s ", type, perms);
}

void executepeek(char **input2)
{
  char *entries[1000];

  char directory[100];
  char new_directory[100];
  getcwd(directory, sizeof(directory));
  // char *path = "hello";
  //  char dash[10]="/";
  DIR *dir;
  struct dirent *entry;
  dir = opendir(input2[2]);
    if (dir == NULL)
    {
      printf("invalid");
      return ;
    }

  if (strcmp(input2[1], "-a") == 0)
  {
    
    int i = 0;
    while ((entry = readdir(dir)) != NULL)
    {
      entries[i] = strdup(entry->d_name);
      strcpy(entries[i], entry->d_name);
      i++;
      // printf("%s\n",entry->d_name);
    }

    qsort(entries, i, sizeof(char *), compare_strings);

    // for(int =0;i<n;i++)
    for (int count = 0; count < i; count++)
    {
      printf("%s\n", entries[count]);
    }
  }

  else if(strcmp(input2[1], "-l") == 0){
    
      int i = 0;
    while ((entry = readdir(dir)) != NULL)
    {
      if (entry->d_name[0] == '.') {
            continue; 
        }
         char full_path[10000];
        snprintf(full_path, sizeof(full_path), "%s/%s", input2[2], entry->d_name);

          struct stat file_stat;
        if (stat(full_path, &file_stat) == -1) {
            perror("stat");
            continue;
        }
print_permissions(file_stat.st_mode);
   printf("%2ld ", file_stat.st_nlink); 

        struct passwd *pw = getpwuid(file_stat.st_uid);
        struct group *gr = getgrgid(file_stat.st_gid);
        printf("%s ", pw ? pw->pw_name : "unknown");
        printf("%s ", gr ? gr->gr_name : "unknown");
        printf("%ld ", (long)file_stat.st_size);
        // printf("Type: %s ", S_ISDIR(file_stat.st_mode) ? "Directory" : "File");
    struct tm *timeinfo = localtime(&file_stat.st_mtime);
        char time_str[80];
        strftime(time_str, sizeof(time_str), "%b %d %H:%M", timeinfo);

        printf("%-12s ", time_str);

        // printf("Last Modified: %s\n", time_str);
        printf("%s ", entry->d_name);
        

        // printf("Permissions: %o\n", file_stat.st_mode & 0777);
        // if (stat(full_path, &file_stat) == -1) {
        //     perror("stat");
        //     continue;
        // }
      // entries[i] = strdup(entry->d_name);
      // strcpy(entries[i], entry->d_name);
      // i++;
      // printf("%s\n",entry->d_name);
      printf("\n");
    }

    // qsort(entries, i, sizeof(char *), compare_strings);

    // for(int =0;i<n;i++)
    // for (int count = 0; count < i; count++)
    // {
    //   printf("%s\n", entries[count]);
    // }

  }

  return;
}

  // return;
  // }
