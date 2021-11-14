#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>

#define FILENAME "ans.txt"

int main(int argc, char const *argv[])
{
    /* Open the file for reading */
    char *line_buf = NULL;
    size_t line_buf_size = 0;
    int line_count = 0;
    ssize_t line_size;
    FILE *fp = fopen(FILENAME, "r");
    if (!fp)
    {
        fprintf(stderr, "Error opening file '%s'\n", FILENAME);
        return 1;
    }
    
    /* Open the socket for writing */
    int sock;
    struct sockaddr_in server;
    char message[256], server_reply[2000];

    sock = socket(AF_INET, SOCK_STREAM, 0);

    if (sock == -1) {
        printf("Could not create socket\n");
        return 1;
    }

    printf("Socket created\n");

    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_family = AF_INET;
    server.sin_port = htons(8080);

    if (connect(sock, (struct sockaddr *)&server, sizeof(server)) < 0) {
        printf("F connect\n");
        return 1;
    }

    printf("Connected\n");

    /* Get the first line of the file. */
    line_size = getline(&line_buf, &line_buf_size, fp);

    /* Loop through until we are done with the file. */
    while (line_size >= 0)
    {
        /* Increment our line count */
        line_count++;

        /* Show the line details */
        printf("line[%06d]: chars=%06zd, buf size=%06zu, contents: %s", line_count,
        line_size, line_buf_size, line_buf);

        if(send(sock, line_buf, line_size, 0) < 0) {
            printf("Send failed\n");
            return 1;
        }

        /* Get the next line */
        line_size = getline(&line_buf, &line_buf_size, fp);
    }

    /* Free the allocated line buffer */
    free(line_buf);
    line_buf = NULL;

    /* Close the file now that we are done with it */
    fclose(fp);

    while(1)
    {
            printf("Enter message: ");
            scanf("%s" , message);
            strcat(message, "\n");

            //Send some data
            if(send(sock, message, strlen(message), 0) < 0)
            {
                    printf("Send failed\n");
                    return 1;
            }

            // //Receive a reply from the server
            // if(recv(sock, server_reply, 2000, 0) < 0)
            // {
            //      printf("recv failed\n");
            //      break;
            // }

            // printf("Server reply: ");
            // printf("%s\n", server_reply);
    }

    close(sock);
    return 0;




    return 0;
}
