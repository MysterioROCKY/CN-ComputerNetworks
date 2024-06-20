#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#define PORT 8080
#define BUFFER_SIZE 1024
int main()
{
    int client_fd;
    struct sockaddr_in server_address;
    char buffer[BUFFER_SIZE] = {0};
    // Create socket file descriptor
    if ((client_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
    // Set server address parameters
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);
    // Convert IPv4 and IPv6 addresses from text to binary form
    if (inet_pton(AF_INET, "127.0.0.1", &server_address.sin_addr) <= 0)
    {
        perror("inet_pton failed");
        exit(EXIT_FAILURE);
    }
    // Connect to server
    if (connect(client_fd, (struct sockaddr *)&server_address, sizeof(server_address)) < 0)
    {
        perror("connect failed");
        exit(EXIT_FAILURE);
    }
    // Prompt user for file name
    printf("Enter file name: ");
    fgets(buffer, BUFFER_SIZE, stdin);
    // Remove newline character from file name
    buffer[strcspn(buffer, "\n")] = 0;
    // Send file name to server
    if (send(client_fd, buffer, strlen(buffer), 0) < 0)
    {
        perror("send");
        exit(EXIT_FAILURE);
    }
    // Receive file data from server
    FILE *file = fopen("received_file", "wb");
    if (file == NULL)
    {
        perror("file open failed");
        exit(EXIT_FAILURE);
    }
    int bytes_received;
    while ((bytes_received = recv(client_fd, buffer, BUFFER_SIZE, 0)) > 0)
    {
        fwrite(buffer, 1, bytes_received, file);
    }
    if (bytes_received < 0)
    {
        perror("recv");
        exit(EXIT_FAILURE);
    }
    printf("File received successfully\n");
    // Close socket and file
    fclose(file);
    close(client_fd);
    return 0;
}