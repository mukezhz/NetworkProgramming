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
    int sockfd, n = 0;
    char buff[1024];
    char msg[15] = "Thank you!!!";
    struct sockaddr_in serverinfo;
    struct Message m;

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
    n = recv(sockfd, &m, sizeof(m), 0);
    printf("Server Msg: %s\tStatus: %d\n", m.msg, m.status);
    if (n > 10)
        send(sockfd, msg, strlen(msg), 0);
    char *roll = argv[6];
    while (1)
    {
        memset(&msg, 0, sizeof(msg));
        memset(&m, 0, sizeof(m));
        n = read(sockfd, &m, sizeof(m));
        m.msg[strlen(m.msg)] = 0;
        printf("SERVER MSG: %s\n", m.msg);
        printf("Enter message: ");
        scanf("%s", msg);
        if (atoi(msg) != 0)
            strcpy(roll, msg);
        if (strncmp(msg, "again", 5) == 0)
        {
            strcat(msg, " ");
            strcat(msg, roll);
        }
        else if (strncmp(msg, "quit", 4) == 0)
        {
            send(sockfd, msg, strlen(msg), 0);
            break;
        }
        send(sockfd, msg, strlen(msg), 0);
    }
    close(sockfd);
    return 0;
}
