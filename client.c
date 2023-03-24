#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>

#define PORT 1337

int main(int argc, char *argv[])
{
    int sockfd;
    struct sockaddr_in server_addr;
    struct hostent *server;
    char buffer[1024];

    // Check command-line arguments
    if (argc < 2) {
        printf("Usage: %s hostname\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // Look up the server address
    server = gethostbyname(argv[1]);
    if (server == NULL) {
        perror("gethostbyname failed");
        exit(EXIT_FAILURE);
    }

    // Create the socket
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
}