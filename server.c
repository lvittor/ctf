#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include "server.h"
#include "challenges.h"

// Function designed for chat between client and server.
void func(int sockfd)
{
	char buff[MAX];
	// infinite loop for chat
	for (;;) {
		memset(buff, 0, MAX);

		// read the message from client and copy it in buffer
		read(sockfd, buff, sizeof(buff));
		// print buffer which contains the client contents
		printf("From client: %s\n", buff);
		memset(buff, 0, MAX);
	}
}

// Driver function
int main()
{
	int sockfd, connfd, len;
	struct sockaddr_in servaddr, cli;

	// socket create and verification
	sockfd = socket(PF_INET, SOCK_STREAM, IPPROTO_IP);
	if (sockfd == -1) {
		printf("socket creation failed...\n");
		exit(ERROR);
	} else
		printf("Socket successfully created..\n");

	int reuseport = 1;
	if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &reuseport,
		       sizeof(reuseport))) {
		perror("setsockopt");
		exit(ERROR);
	}

	memset(&servaddr, 0, sizeof(servaddr));

	// assign IP, PORT
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(PORT);

	// Binding newly created socket to given IP and verification
	if (bind(sockfd, (SA *)&servaddr, sizeof(servaddr))) {
		perror(NULL);
		printf("socket bind failed...\n");
		exit(ERROR);
	} else
		printf("Socket successfully binded..\n");

	// Now server is ready to listen and verification
	if (listen(sockfd, 5)) {
		printf("Listen failed...\n");
		exit(ERROR);
	} else
		printf("Server listening..\n");
	len = sizeof(cli);

	// Accept the data packet from client and verification
	connfd = accept(sockfd, (SA *)&cli, &len);
	if (connfd < 0) {
		printf("server accept failed...\n");
		exit(ERROR);
	} else
		printf("server accept the client...\n");

	FILE *server_file = fdopen(connfd, "r");
	if (server_file == NULL) {
		printf(":(");
		exit(ERROR);
	}

	run_challenges(server_file);

	// After chatting close the socket
	close(sockfd);
}