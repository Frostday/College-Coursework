#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int sockfd;
    int opt = 1;
    struct sockaddr_in address;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    printf("socket created with id %d\n", sockfd);

    memset(&address, 0, sizeof(address));

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr("10.0.2.15"); //broadcast address found via
    address.sin_port = htons(8080);

    bind(sockfd, (struct sockaddr *)&address, sizeof(address));
    printf("socked binded\n");

    setsockopt(sockfd, SOL_SOCKET, SO_BROADCAST, &opt, sizeof(opt));
    printf("socket option set to broadcast\n");
    
    char *message = "broadcast message from sender";
    while (1)
    {
        sendto(sockfd, (char *)message, strlen(message), 0, (struct sockaddr *)&address, sizeof(address));
        printf("broadcast message sent\n");
        sleep(3);
    }
    return 0;
}
