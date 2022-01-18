#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "assignment.h"

#define LISTENQ 10
#define BUFFSIZE 1024

typedef struct sockaddr SA;

int main(int argc, char const *argv[])
{
    int sockfd, newsockfd, n = 0;
    char msg[1024];
    socklen_t clientsize;
    struct sockaddr_in serverinfo, clientinfo;
    if ((argc != 3) || (strncmp(argv[1], "-p", 2) != 0))
    {
        printf("Syntax: %s -p <port>\n", *argv);
        exit(EXIT_FAILURE);
    }

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        error_handle("Socket Creation Error\n");

    memset(&serverinfo, 0, sizeof(serverinfo));

    serverinfo.sin_addr.s_addr = INADDR_ANY;
    serverinfo.sin_family = AF_INET;
    serverinfo.sin_port = ntohs(atoi(argv[2]));

    if (bind(sockfd, (SA *)&serverinfo, sizeof(serverinfo)) == -1)
        error_handle("Binding Error\n");
    printf("Binding Successful to port: %s\n", argv[2]);

    if (listen(sockfd, LISTENQ) == -1)
        error_handle("Listening Error\n");

    while (1)
    {
        memset(&clientinfo, 0, sizeof(clientinfo));
        memset(&msg, 0, sizeof(msg));
        clientsize = sizeof(clientinfo);
        if ((newsockfd = accept(sockfd, (SA *)&clientinfo, &clientsize)) < 0)
            error_handle("New Socket Formation Error\n");
        // recv read are non blocking
        while ((n = read(newsockfd, msg, sizeof(msg))) > 0)
        {
            msg[n] = 0;
            printf("Client msg: %s\n", msg);
        }
        close(newsockfd);
    }
    close(sockfd);
    return 0;
}
