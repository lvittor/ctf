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

void func(int sockfd)
{
	char buff[MAX];
	while (1) {
		memset(buff, 0, MAX);
		read(sockfd, buff, sizeof(buff));
		printf("From client: %s\n", buff);
		memset(buff, 0, MAX);
	}
}

int main()
{
	int sockfd, connfd, len;
	struct sockaddr_in servaddr, cli;

	sockfd = socket(PF_INET, SOCK_STREAM, IPPROTO_IP);
	if (sockfd == -1) {
		printf("socket creation failed...\n");
		return ERROR;
	} else
		printf("Socket successfully created...\n");

	int reuseport = 1;
	if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &reuseport,
		       sizeof(reuseport))) {
		perror("setsockopt");
		return ERROR;
	}

	memset(&servaddr, 0, sizeof(servaddr));

	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(PORT);

	if (bind(sockfd, (SA *)&servaddr, sizeof(servaddr))) {
		perror(NULL);
		printf("socket bind failed...\n");
		return ERROR;
	} else
		printf("Socket successfully binded...\n");

	if (listen(sockfd, 5)) {
		printf("Listen failed...\n");
		return ERROR;
	} else
		printf("Server listening...\n");
	len = sizeof(cli);

	connfd = accept(sockfd, (SA *)&cli, &len);
	if (connfd < 0) {
		printf("server accept failed...\n");
		return ERROR;
	} else
		printf("server accept the client...\n");

	FILE *server_file = fdopen(connfd, "r");
	if (server_file == NULL) {
		printf("error openning the server_file...\n");
		return ERROR;
	}

	run_challenges(server_file);
	close(sockfd);

	return SUCCESS;
}