#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define SERVER_ADDR "127.0.0.1"
#define SERVER_PORT 8989

int main(int argc, char *argv[]) {
    int sock = 0, bytes_read = 0;
    struct sockaddr_in server;
    char buffer[1024] = {0};

    // Create socket
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\nSocket creation error\n");
        return -1;
    }

    memset(&server, '0', sizeof(server));

    server.sin_family = AF_INET;
    server.sin_port = htons(SERVER_PORT);

    // Convert IPv4 and IPv6 addresses from text to binary form
    if (inet_pton(AF_INET, SERVER_ADDR, &server.sin_addr) <= 0) {
        printf("\nInvalid address/ Address not supported\n");
        return -1;
    }

    // Connect to server
    if (connect(sock, (struct sockaddr *)&server, sizeof(server)) < 0) {
        printf("\nConnection Failed\n");
        return -1;
    }

    // Send message to server
    char message[100];
    sprintf(message, "%s.%s\n", argv[1], argv[2]);
    if (send(sock, message, strlen(message), 0) < 0) {
        printf("\nSend failed\n");
        return -1;
    }

    // Receive data from server
    while ((bytes_read = read(sock, buffer, 1024)) > 0) {
        printf("%s", buffer);
    }

    printf("\n");
    close(sock);
    return 0;
}
