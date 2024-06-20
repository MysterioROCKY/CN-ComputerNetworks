#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int server_fd;
    struct sockaddr_in server_addr, client_addr;
    int addrlen = sizeof(server_addr);
    char buffer[BUFFER_SIZE] = {0};

    // Create UDP socket
    if ((server_fd = socket(AF_INET, SOCK_DGRAM, 0)) == 0) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Initialize server address struct
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    // Bind socket to address and port
    if (bind(server_fd, (const struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d\n", PORT);

    // Receive message from client
    int bytes_received;
    while (1) {
        bytes_received = recvfrom(server_fd, buffer, BUFFER_SIZE, 0, (struct sockaddr *)&client_addr, &addrlen);
        buffer[bytes_received] = '\0'; // Null terminate the received data
        printf("Client: %s\n", buffer);

        // Reply to client
        printf("Server: ");
        fgets(buffer, BUFFER_SIZE, stdin);
        sendto(server_fd, buffer, strlen(buffer), 0, (const struct sockaddr *)&client_addr, addrlen);
    }

    close(server_fd);
    return 0;
}
