#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define BUFFSIZE 1024

typedef struct sockaddr SA;

int main(int argc, char** argv) {
	int sockfd;
	struct sockaddr_in address;
  char buff[BUFFSIZE];
  char msg[BUFFSIZE];
  memset(buff, 0, sizeof(buff));
  memset(msg, 0, sizeof(buff));
  
  if (argc!=5 || strcmp(argv[1],"-h")!=0 || strcmp(argv[3], "-p")!=0) {
    printf("Invalid syntax\n");
    printf("Syntax: ./client -h <Ip address> -p <Port no>\n");
    exit(EXIT_FAILURE);
  }

	// creating socket
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0) {
		printf("error creating socket\n");
		exit(EXIT_FAILURE);
	}
	// assigning address port
	address.sin_port = htons(atoi(argv[4]));
	address.sin_family = AF_INET;
	inet_pton(AF_INET, argv[2], &address.sin_addr);
	if ( connect(sockfd, (SA*) &address, sizeof(address)) < 0 ) {
    printf("Connection error\n");
    exit(EXIT_FAILURE);
  }
  while(1) {
    printf("Client msg: ");
    fgets(msg, BUFFSIZE, stdin);
    if ( (strcmp(msg, "exit") == 0) || (strcmp(msg, "EXIT")) == 0) {
      printf("Connection is being closed\n");
      close(sockfd);
      exit(EXIT_SUCCESS);
    }
    send(sockfd, msg, strlen(msg), 0);
    memset(msg, 0, sizeof(msg));
    recv(sockfd, &buff, sizeof(buff), 0);
    printf("Server send: %s", buff);
  }
  return 0;
}

