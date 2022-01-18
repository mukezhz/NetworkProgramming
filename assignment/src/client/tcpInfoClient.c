#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "assignment.h"

#define BUFFSIZE 1024

typedef struct sockaddr SA;

int main(int argc, char const *argv[])
{
    int sockfd, n;
    char msg[1024];
    struct sockaddr_in serverinfo;
    if ((argc != 7) || (strncmp(argv[1], "-h", 2) != 0) || (strncmp(argv[3], "-p", 2) != 0) || (strncmp(argv[5], "-n", 2) != 0))
    {
        printf("Syntax: %s -h <host address> -p <port> -n <roll no>\n", *argv);
        exit(EXIT_FAILURE);
    }

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("Socket creation error\n");
        exit(EXIT_FAILURE);
    }

    memset(&serverinfo, 0, sizeof(serverinfo));

    serverinfo.sin_family = AF_INET;
    serverinfo.sin_port = ntohs(atoi(argv[4]));
    printf("Host %s\n", argv[2]);
    // serverinfo.sin_addr.s_addr = inet_addr(argv[2]);
    if ((inet_pton(AF_INET, argv[2], &serverinfo.sin_addr)) < 0)
        error_handle("Invalid server info\n");

    if ((connect(sockfd, (SA *)&serverinfo, sizeof(serverinfo))) == -1)
        error_handle("Connection Error\n");

    send(sockfd, argv[6], strlen(argv[6]), 0);
    close(sockfd);
    return 0;
}
