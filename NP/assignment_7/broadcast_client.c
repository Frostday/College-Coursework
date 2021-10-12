#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

int main()
{
  int sockfd;
  int n;
  char buffer[1024];
  struct sockaddr_in address;
  sockfd = socket(AF_INET, SOCK_DGRAM, 0);
  printf("socket created with id : %d\n", sockfd);
  memset(&address, 0, sizeof(address));
  address.sin_family = AF_INET;
  address.sin_port = htons(8080);
  address.sin_addr.s_addr = inet_addr("10.0.2.15");
  bind(sockfd, (struct sockaddr *)&address, sizeof(address));
  for (;;)
  {
    n = recvfrom(sockfd, (char *)buffer, 1024, 0, (struct sockaddr *)&address, sizeof(address));
    buffer[n] = '\0';
    printf("broadcast message : %s\n", buffer);
  }
  close(sockfd);
  return 0;
}
