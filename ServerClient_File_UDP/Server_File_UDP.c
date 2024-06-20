#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024
#define END_MSG "END_OF_FILE"

int main() {
    int server_fd, bytes_read;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addrlen = sizeof(client_addr);
    char buffer[BUFFER_SIZE] = {0};

    if ((server_fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d\n", PORT);

    while (1) {
        if (recvfrom(server_fd, buffer, BUFFER_SIZE, 0, (struct sockaddr *)&client_addr, &addrlen) < 0) {
            perror("recvfrom");
            exit(EXIT_FAILURE);
        }

        FILE *file = fopen(buffer, "rb");
        if (!file) {
            perror("file open failed");
            exit(EXIT_FAILURE);
        }

        while ((bytes_read = fread(buffer, 1, BUFFER_SIZE, file)) > 0) {
            sendto(server_fd, buffer, bytes_read, 0, (struct sockaddr *)&client_addr, addrlen);
        }

        sendto(server_fd, END_MSG, strlen(END_MSG), 0, (struct sockaddr *)&client_addr, addrlen);
        printf("File sent successfully\n");
        fclose(file);
    }

    close(server_fd);
    return 0;
}
