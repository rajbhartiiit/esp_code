#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "FreeRTOS.h"
#include "task.h"

#include "lwip/err.h"
#include "lwip/sockets.h"
#include "lwip/sys.h"
#include "lwip/netdb.h"

#include "udp_server.h"
// #define PORT 4096
#define PORT 8080
#define MAXLINE 1024

void udp_server_task()
{
    // add your udp server files here
    // also add while (1) here with vTaskdelay

    // Server side implementation of UDP client-server model

    // Driver code

    int sockfd;
    char buffer[MAXLINE];
    char *hello = "Hello from server";
    struct sockaddr_in servaddr, cliaddr;

    while (1)
    {
        // Creating socket file descriptor
        if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
        {
            perror("socket creation failed");
            exit(EXIT_FAILURE);
        }

        memset(&servaddr, 0, sizeof(servaddr));
        memset(&cliaddr, 0, sizeof(cliaddr));

        // Filling server information
        servaddr.sin_family = AF_INET; // IPv4
        servaddr.sin_addr.s_addr = INADDR_ANY;
        servaddr.sin_port = htons(PORT);

        // Bind the socket with the server address
        if (bind(sockfd, (const struct sockaddr *)&servaddr,
                 sizeof(servaddr)) < 0)
        {
            perror("bind failed");
            exit(EXIT_FAILURE);
        }

        int len, n;
        sizeof(cliaddr);
        while (1)
        {
            n = recvfrom(sockfd, (char *)buffer, MAXLINE,
                         0, (struct sockaddr *)&cliaddr,
                         &len);
            buffer[n] = '\0';
            printf("Client : %s\n", buffer);

            printf("len : %d\n", len);

            printf("sizeof sockaddr : %d\n", sizeof(struct sockaddr));

            // int err = sendto(sockfd, (const char *)hello, strlen(hello),
            //                  0, (const struct sockaddr *)&cliaddr,
            //                  len);
            int err = sendto(sockfd, hello, strlen(hello),
                             0, (const struct sockaddr *)&cliaddr,
                             16);

            printf("err %d\n", err);
            if (err < 0)
            {
                printf("err occured %d\n", err);
            }
            printf("Hello message sent.\n");
        }
    }
}

void udp_server_init(void)
{
    xTaskCreate(&udp_server_task, "udp_server_task", 512, NULL, 3, NULL);
}