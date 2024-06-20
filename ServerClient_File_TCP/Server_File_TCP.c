#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#define PORT 8080
#define BUFFER_SIZE 1024
int main() {
int server_fd, new_socket;
struct sockaddr_in address;
int addrlen = sizeof(address);
char buffer[BUFFER_SIZE] = {0};
// Create socket file descriptor
if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
perror("socket failed");
exit(EXIT_FAILURE);
}
// Set socket options
address.sin_family = AF_INET;
address.sin_addr.s_addr = INADDR_ANY;
address.sin_port = htons(PORT);
// Bind the socket to localhost port 8080
if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
perror("bind failed");
exit(EXIT_FAILURE);
}
// Start listening for incoming connections
if (listen(server_fd, 3) < 0) {
perror("listen");
exit(EXIT_FAILURE);
}
printf("Server listening on port %d\n", PORT);
// Accept connection from client
if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
perror("accept");
exit(EXIT_FAILURE);
}
// Receive file name from client
if (recv(new_socket, buffer, BUFFER_SIZE, 0) < 0) {
perror("recv");
exit(EXIT_FAILURE);
}
// Open the file
FILE *file = fopen(buffer, "rb");
if (file == NULL) {
perror("file open failed");
exit(EXIT_FAILURE);
}
// Read data from file and send to client
int bytes_read;
while ((bytes_read = fread(buffer, 1, BUFFER_SIZE, file)) > 0) {
    if (send(new_socket, buffer, bytes_read, 0) != bytes_read) {
    perror("send");
    exit(EXIT_FAILURE);
    }
}
printf("File sent successfully\n");
// Close sockets and file
fclose(file);
close(new_socket);
close(server_fd);
return 0;
}