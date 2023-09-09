#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>

#define MAX_BUFFER_SIZE 4096

void error(const char *msg) {
    perror(msg);
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <command_name>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    char *command_name = argv[1];

    // Resolve DNS for man.he.net
    struct hostent *server = gethostbyname("man.he.net");
    if (server == NULL) {
        error("Error in DNS resolution");
    }

    // Create a socket
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        error("Error opening socket");
    }

    // Specify server details
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(80);
    bcopy((char *)server->h_addr, (char *)&server_addr.sin_addr.s_addr, server->h_length);

    // Connect to the server
    if (connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        error("Error connecting to server");
    }

    // Send a GET request
    char request[MAX_BUFFER_SIZE];
    snprintf(request, sizeof(request), "GET /man1/%s.1.php HTTP/1.1\r\nHost: man.he.net\r\n\r\n", command_name);
    if (write(sockfd, request, strlen(request)) < 0) {
        error("Error writing to socket");
    }

    // Read and print the response
    char response[MAX_BUFFER_SIZE];
    ssize_t n;
    while ((n = read(sockfd, response, sizeof(response))) > 0) {
        fwrite(response, 1, n, stdout);
    }

    if (n < 0) {
        error("Error reading from socket");
    }

    // Close the socket
    close(sockfd);

    return 0;
}
