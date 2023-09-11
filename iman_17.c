#include "headers.h"

#include "prompt.h"

#define MAX_BUFFER_SIZE 4096

void error(const char *msg) {
    perror(msg);
    exit(EXIT_FAILURE);
}

void stripHTMLTags(char *str) {
    int insideTag = 0;
int j=0;
    for (int i = 0; str[i]; i++) {
        if (str[i] == '<') {
            insideTag = 1;
            continue;
        }
        if (insideTag) {
            if (str[i] == '>') {
                insideTag = 0;
            }
            continue;
        }
        str[j++] = str[i];
    }
    str[j] = '\0';
}

void iman(char **input) {
     //     fprintf(stderr, "Usage: %s <command_name>\n", argv[0]);
    //     exit(EXIT_FAILURE);
    // }

    char *command_name = input[1];

    struct hostent *server = gethostbyname("man.he.net");
    if (server == NULL) {
        error("Error in DNS resolution");
    }

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        error("Error opening socket");
    }

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(80);
    bcopy((char *)server->h_addr, (char *)&server_addr.sin_addr.s_addr, server->h_length);

    if (connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        error("Error connecting to server");
    }

    char request[MAX_BUFFER_SIZE];
    snprintf(request, sizeof(request), "GET http://man.he.net/?topic=%s&section=all HTTP/1.1\r\nHost: man.he.net\r\n\r\n", command_name);
// printf("%s\n",request);
    if (write(sockfd, request, strlen(request)) < 0) {
        // error("Error writing to socket");
        printf("No manpagefound");
        return;
    }


    char buffer[1024];
    char line[1024];
    int n;
    int start=0;

   int lineLength = 0;
   int bytesRead;
   int foundmanpage=0;
    while ((bytesRead = read(sockfd, buffer, sizeof(buffer))) > 0) {
        for (ssize_t i = 0; i < bytesRead; i++) {
            if (buffer[i] == '\n') {
                line[lineLength] = '\0'; 
                    if(strncmp(line,"NAME",4)==0){
                    start=1;
                    }
                    if(start==1){
                        stripHTMLTags(line);
                    printf("%s\n", line);
                    }
                    // if(strncmp(line,"Search Again",12)==0){
                    //     foundmanpage=1;
                    //     break;
                    // }
                lineLength = 0;
            } else if (lineLength < 1000) {
                line[lineLength++] = buffer[i];
            }
        }
    }
    if(start==0){
        printf("No such command\n");
        return;
    }

    if (n < 0) {
        error("Error reading from socket");
    }

    // Step 7: Close the socket
    close(sockfd);

    // return 0;
}
 // if (argc != 2) {
  