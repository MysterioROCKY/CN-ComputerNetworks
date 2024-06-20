#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define SERVER_IP "127.0.0.1"
#define BUFFER_SIZE 1024
#define END_MSG "END_OF_FILE"

int main() {
    int client_fd, bytes_received;
    struct sockaddr_in server_addr;
    socklen_t addrlen = sizeof(server_addr);
    char buffer[BUFFER_SIZE] = {0};
    char filename[BUFFER_SIZE];

    if ((client_fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    if (inet_pton(AF_INET, SERVER_IP, &server_addr.sin_addr) <= 0) {
        perror("inet_pton failed");
        exit(EXIT_FAILURE);
    }

    printf("Enter file name: ");
    fgets(filename, BUFFER_SIZE, stdin);
    filename[strcspn(filename, "\n")] = '\0';

    sendto(client_fd, filename, strlen(filename), 0, (struct sockaddr *)&server_addr, addrlen);

    FILE *file = fopen("received_file", "wb");
    if (!file) {
        perror("file open failed");
        exit(EXIT_FAILURE);
    }

    do {
        bytes_received = recvfrom(client_fd, buffer, BUFFER_SIZE, 0, (struct sockaddr *)&server_addr, &addrlen);
        if (bytes_received > 0) {
            if (strncmp(buffer, END_MSG, bytes_received) == 0) {
                break;
            }
            fwrite(buffer, 1, bytes_received, file);
        }
    } while (bytes_received > 0);

    if (bytes_received < 0) {
        perror("recvfrom");
        exit(EXIT_FAILURE);
    }

    printf("File received successfully\n");
    fclose(file);
    close(client_fd);
    return 0;
}
