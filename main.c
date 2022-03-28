#include <stdio.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main()
{

    int sock = socket(AF_INET, SOCK_STREAM, 0); // creating a socket

    if (sock < 0) // aborting the program it fails to create socket
        return -1;

    struct sockaddr_in api; // defining required struct

    // initializing the struct
    api.sin_port = htons(80);
    api.sin_family = AF_INET;
    api.sin_addr.s_addr = inet_addr("104.20.138.65");

    if (connect(sock, (struct sockaddr *)&api, sizeof(api)) < 0) // connecting to server if it fails to do so then we will abort the program
        return -1;

    // taking a url as input
    char url[256];
    printf("Enter url : ");
    scanf("%s", url);

    // constructing the request string
    char pre_request[309] = "GET /api-create.php?url=";
    char *post_request = " HTTP/1.1\r\nHost:tinyurl.com\r\n\r\n";
    strcat(pre_request, url);
    strcat(pre_request, post_request);

    send(sock, pre_request, strlen(pre_request), 0); // sending request to server

    char res[500]; // defining a buffer for response

    recv(sock, res, 500, 0); // receiving the response from server

    // finding out the index from which the shortned url start
    int i;
    for (size_t count = 0; count < 14; i++)
    {
        if (res[i] == '\n')
            count++;
    }

    // printing out the shortned url
    printf("\nShortned url : ");
    for (size_t j = i; j < strlen(res); j++)
        printf("%c", res[j]);
    printf("\n\n");

    close(sock); // closing the socket
    return 0;
}
