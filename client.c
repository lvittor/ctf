#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>

#define FILENAME "ans.txt"
#define INET_ADDR "127.0.0.1"

int main(int argc, char const *argv[])
{
	char *line_buf = NULL;
	size_t line_buf_size = 0;
	int line_count = 0;
	ssize_t line_size;
	FILE *fp = fopen(FILENAME, "r");
	if (!fp) {
		fprintf(stderr, "Error opening file '%s'\n", FILENAME);
		return 1;
	}

	struct sockaddr_in server;
	char message[256];

	int sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == -1) {
		printf("Could not create socket\n");
		return 1;
	}

	printf("Socket created\n");

	server.sin_addr.s_addr = inet_addr(INET_ADDR);
	server.sin_family = AF_INET;
	server.sin_port = htons(8080);

	if (connect(sock, (struct sockaddr *)&server, sizeof(server)) < 0) {
		printf("F connect\n");
		return 1;
	}

	printf("Connected\n");
	line_size = getline(&line_buf, &line_buf_size, fp);
	while (line_size >= 0) {
		line_count++;
		printf("line[%06d]: chars=%06zd, buf size=%06zu, contents: %s",
		       line_count, line_size, line_buf_size, line_buf);

		if (send(sock, line_buf, line_size, 0) < 0) {
			printf("Send failed\n");
			return 1;
		}

		line_size = getline(&line_buf, &line_buf_size, fp);
	}

	free(line_buf);
	line_buf = NULL;

	fclose(fp);

	while (1) {
		printf("Enter message: ");
		scanf("%s", message);
		strcat(message, "\n");

		if (send(sock, message, strlen(message), 0) < 0) {
			printf("Send failed\n");
			return 1;
		}
	}

	close(sock);
	return 0;
}
