#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>


#define PORT 8000
#define BUFFSIZE 1024

typedef struct sockaddr SA;

int main(int argc, char** argv) {
	int sockfd;
	struct sockaddr_in address;
	struct {
		char msg[BUFFSIZE];
		int bytes_read;
		int socketfd;
		
	} buff;

	// creating socket
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0) {
		printf("error creating socket\n");
		exit(EXIT_FAILURE);
	}
	// assigning address port
	address.sin_port = htons(PORT);
	address.sin_family = AF_INET;
	inet_pton(AF_INET, "127.0.0.1", &address.sin_addr);
	connect(sockfd, (SA*) &address, sizeof(address));
	printf("Enter the message: ");
	fgets(buff.msg, BUFFSIZE, stdin);
	printf("Sending msg: %s", buff.msg);
	send(sockfd, buff.msg, strlen(buff.msg), 0);
	printf("sending success: %s", buff.msg);
	printf("***********receiving**********\n");
	recv(sockfd, &buff, sizeof(buff), 0);
	printf("Server send(msg): %s", buff.msg);
	printf("Server send(bytes_read): %d\n", buff.bytes_read);
	printf("Server send(socketfd): %d\n", buff.socketfd);

  	close(sockfd);
  	return 0;
}

