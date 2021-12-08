// upper case
// socket file descriptor
// no of byte read

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>


#define PORT 8000
#define LISTENQ 10
#define BUFFSIZE 1024

typedef struct sockaddr SA;

void upperCase(char* msg) {
	int i;
	for(i=0; msg[i]!='\0'; i++) {
		msg[i] = toupper(msg[i]);
	}
	msg[i] = '\0';
}

int main(int argc, char** argv) {
	int sockfd, new_sockfd;
	int n;
	struct sockaddr_in address, clientaddress;
	socklen_t len;
	struct {
		char msg[BUFFSIZE];
		int bytes_read;
		int socketfd;
		
	} buff;
	memset(&buff, 0, sizeof(buff));

	// creating socket
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0) {
		printf("error creating socket\n");
		exit(EXIT_FAILURE);
	}
	bzero(&address, sizeof(address));
	// assigning address
	address.sin_addr.s_addr = htonl(INADDR_ANY);
	address.sin_port = htons(PORT);
	address.sin_family = AF_INET;

	// binding 
	if (bind(sockfd, (SA*)&address, sizeof(address)) == -1) {
		printf("error while binding\n");
		exit(EXIT_FAILURE);
	}

	// listen 
	listen(sockfd, LISTENQ);
	printf("listeing on port: %d\n", PORT);

	// loop accept
	while(1) {
		memset(&buff, 0, sizeof(buff));
		len = sizeof(clientaddress);
		new_sockfd = accept(sockfd, (SA*)&clientaddress, &len);
		printf("new sock %d\n", new_sockfd);
		if (new_sockfd < 0) {
			printf("cannot accept\n");
			exit(EXIT_FAILURE);		
		}
		// recv is non blocking
		while((n = read(new_sockfd, buff.msg, sizeof(buff.msg))) > 0) {
			buff.msg[n] = 0;
			printf("Client send: %s\n", buff.msg);
			upperCase(buff.msg);
			printf("Client send(uppercase): %s\n", buff.msg);
			buff.bytes_read = n;
			buff.socketfd = new_sockfd;
			send(new_sockfd, &buff, sizeof(buff), 0);
			memset(&buff, 0, sizeof(buff));
		}
		// close(new_sockfd);
	}
  close(sockfd);
  return 0;
}

