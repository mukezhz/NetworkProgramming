#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "assignment.h"
#include "clientinfo.h"

#define LISTENQ 10
#define BUFFSIZE 1024

typedef struct sockaddr SA;
struct node *head;

int main(int argc, char const *argv[])
{
    head = init();
    int sockfd, connfd, n = 0;
    char msg[BUFFSIZE];
    socklen_t clientsize;
    struct sockaddr_in serverinfo, clientinfo;
    struct node *ll = NULL;
    struct Message m;

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
        memset(&m, 0, sizeof(m));
        memset(&msg, 0, sizeof(msg));
        clientsize = sizeof(clientinfo);
        if ((connfd = accept(sockfd, (SA *)&clientinfo, &clientsize)) < 0)
            error_handle("New Socket Formation Error\n");
        // recv read are non blocking
        while ((n = read(connfd, msg, sizeof(msg))) > 0)
        {
            msg[n] = 0;
            long roll = atoi(msg);
            printf("CLIENT MSG: %s\n\n", msg);
            if (strncmp(msg, "again", 5) == 0)
            {
                char *temp = substr(msg, 6, strlen(msg) - 5);
                temp[strlen(msg) - 5] = 0;
                roll = atoi(temp);
                ll = search(head, roll);
                if (ll == NULL)
                {
                    m.status = -1;
                    printf("Not found: %p\n", ll);
                }
                else
                {
                    int len = sprintf(msg, "Welcome %s your unique identification key is %ld\n", ll->data.name, ll->data.registration_no);
                    strcpy(m.msg, msg);
                    m.msg[len] = 0;
                    m.status = 0;
                    ll->data.msj_sent_count++;
                }
            }
            else if (strncmp(msg, "Thank you!!!", strlen("Thank you!!!")) == 0)
            {
                int len = sprintf(m.msg, "Welcome !!!\n");
                m.msg[len] = 0;
                m.status = 1;
            }
            else if (strncmp(msg, "quit", 4) == 0)
            {
                printf("Closing connection of client\n");
                break;
            }
            else
            {
                if (roll == 0 && strlen(msg) > 2)
                {
                    char msg[] = "Please input valid roll number";
                    strcpy(m.msg, msg);
                    m.msg[strlen(msg)] = 0;
                    m.status = 1;
                    // send(connfd, msg, strlen(msg), 0);
                }
                else
                {
                    ll = search(head, roll);
                    if (ll == NULL)
                    {
                        int len = sprintf(msg, "Unable to find information\n");
                        strcpy(m.msg, msg);
                        m.msg[len] = 0;
                        m.status = -1;
                    }
                    else
                    {
                        int len = sprintf(msg, "Welcome %s your unique identification key is %ld\n", ll->data.name, ll->data.registration_no);
                        strcpy(m.msg, msg);
                        m.msg[len] = 0;
                        m.status = 0;
                        ll->data.msj_sent_count++;
                    }
                    // send(connfd, msg, strlen(msg), 0);
                    // printf("Server:\n%s\n", msg);
                }
            }
            strcat(m.msg, "\n\nDo you want to see your information again?('again' or 'quit')");
            send(connfd, &m, sizeof(m), 0);
        }
        close(connfd);
    }
    close(sockfd);
    return 0;
}
