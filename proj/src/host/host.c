#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 4321
#define MESSAGE "hello"


/*!
 * @brief Sends a message to the server through the specified socket.
 * 
 * @param socketfd The file descriptor of the socket.
 * @param message The message to be sent.
 * @return int Returns 0 on success, 1 on failure.
 */
int sendSerialMessage(int socketfd, const void* message) {
  if (send(socketfd, message, strlen(message), 0) != strlen(message)) {
    perror("Send failed");
    return 1;
  }

  return 0;
}


int waitSerialMessage() {
  while(1)
    ;
}

/*!
 * @brief The main function that sets up the client, connects to the server, and closes the connection.
 * 
 * @return int Returns 0 on success, exits with failure status on error.
 */
int main() {
  int sockfd;
  struct sockaddr_in server_addr;

  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd == -1) {
    perror("Socket creation failed");
    exit(EXIT_FAILURE);
  }

  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(SERVER_PORT);
  if (inet_pton(AF_INET, SERVER_IP, &server_addr.sin_addr) <= 0) {
    perror("Invalid address/ Address not supported");
    exit(EXIT_FAILURE);
  }

  if (connect(sockfd, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0) {
    perror("Connection failed");
    exit(EXIT_FAILURE);
  }

  close(sockfd);

  return 0;
}