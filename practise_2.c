#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <libxml/HTMLparser.h>

#define MAX_BUFFER_SIZE 4096

void error(const char *msg) {
    perror(msg);
    exit(EXIT_FAILURE);
}


void parseAndPrintText(const char *html) {
    htmlDocPtr doc = htmlReadMemory(html, strlen(html), NULL, NULL, HTML_PARSE_RECOVER | HTML_PARSE_NOERROR | HTML_PARSE_NOWARNING);
    if (doc == NULL) {
        fprintf(stderr, "Error parsing HTML\n");
        return;
    }

    htmlNodePtr cur = xmlDocGetRootElement(doc);
    while (cur != NULL) {
        if (cur->type == XML_TEXT_NODE) {
            printf("%s", cur->content);
        }
        cur = cur->next;
    }

    xmlFreeDoc(doc);
    xmlCleanupParser();
}



int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <command_name>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    char *command_name = argv[1];

    // Step 1: DNS resolution for man.he.net
    struct hostent *server = gethostbyname("man.he.net");
    if (server == NULL) {
        error("Error in DNS resolution");
    }

    // Step 2: Open a TCP socket to the IP address
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        error("Error opening socket");
    }

    // Step 3: Specify server details
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(80);
    bcopy((char *)server->h_addr, (char *)&server_addr.sin_addr.s_addr, server->h_length);

    // Step 4: Connect to the server
    if (connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        error("Error connecting to server");
    }

    // Step 5: Send a GET request
    char request[MAX_BUFFER_SIZE];
    snprintf(request, sizeof(request), "GET http://man.he.net/?topic=%s&section=all HTTP/1.1\r\nHost: man.he.net\r\n\r\n", command_name);
    if (write(sockfd, request, strlen(request)) < 0) {
        error("Error writing to socket");
    }

    // Step 6: Read and print the body of the website
    char response[MAX_BUFFER_SIZE];
    ssize_t n;
    int body_started = 0;

    while ((n = read(sockfd, response, sizeof(response))) > 0) {
         if (!body_started) {
            char *body_start = strstr(response, "<PRE>");
            if (body_start != NULL) {
                body_started = 1;
                parseAndPrintHTML(body_start);
            }
        } else {
            parseAndPrintHTML(response);
        }
    }

    if (n < 0) {
        error("Error reading from socket");
    }

    // Step 7: Close the socket
    close(sockfd);

    return 0;
}
