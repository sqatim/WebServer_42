#include <iostream>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>

void error(char *str)
{
    std::cout << str << std::endl;
    exit(1);
}
int main()
{
    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    char buffer[256];
    char str[5000000];
     int fd = open("index.html", O_RDWR);
    // int s = read(./index.html, )
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        std::cout << "ERROR opening socket" << std::endl;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(8080);
    if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
        std::cout << "ERROR opening socket" << std::endl;
    send(sockfd, str, strlen(str), 0);
    std::cout << "hello msg sent " << std::endl;
    n = read(sockfd, buffer, 256);
    read(fd, str, 5000000);
    printf("%s\n", buffer);
    // write, str, 5000000);
    return 0;
}

