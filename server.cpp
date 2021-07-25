#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <fcntl.h>

#define PORT 3000
int main(int argc, char const *argv[])
{
    int server_fd, new_socket; long valread;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    
    // Only this line has been changed. Everything is same.
    char *hello = "/index.html HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 25\n\nHello world!";
    int fd = open("index.html", O_RDONLY);
    char buf[5000000];
    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("In socket");
        exit(EXIT_FAILURE);
    }
    

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( PORT );
    
    memset(address.sin_zero, '\0', sizeof address.sin_zero);
    
    
    if (bind(server_fd, (struct sockaddr *)&address , sizeof(address))<0)
    {
        perror("In bind");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 10) < 0)
    {
        perror("In listen");
        exit(EXIT_FAILURE);
    }
    while(1)
    {
        printf("\n+++++++ Waiting for new connection ++++++++\n\n");
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0)
        {
            perror("In accept");
            exit(EXIT_FAILURE);
        }
        char buffer[30000] = {0};
        valread = read( new_socket , buffer, 30000);
        read(fd, buf, 5000000);
        printf("%s\n",buffer );
        printf("%s\n", buf, 5000000);
        printf("amine haddad\n");
        write(new_socket , buf , 5000000);
        printf("------------------Hello message sent-------------------");
        close(new_socket);
    }
    return 0;
}

// #include <iostream>
// /*
// The header file socket.h includes a number of definitions of structures needed for sockets.
// */
// #include <sys/socket.h>
// /*
//     The header file in.h contains constants and structures needed for internet domain addresses.
// */
// #include <netinet/in.h>
// /*
// This header file contains definitions of a number of data types used in system calls.
// These types are used in the next two include files.
// */
// #include <sys/types.h>
// #include <unistd.h>
// #include <fcntl.h>
// #include <string>

// int main()
// {
//     int sockfd;
//     int newsockfd;
//     // char str[] = "Hello World!";
//     /*
//         these two variable are a file descriptors
//     */
//     int portno;
//     /*
//         stores the port number on which the server accepts connections.
//     */
//     socklen_t clilen;
//     /*
//         stores the size of the address of the client. This is needed for the accept system call
//     */
//     int n;
//     char buffer[265];
//     char str[5000000];
//     int fd = open("index.html", O_RDWR);
//     /*
//         The socket() system call creates a new socket.
//         It takes three arguments.
//         The first is the address domain of the socket.
//     */
//     sockfd = socket(AF_INET, SOCK_STREAM, 0);
//     if (sockfd < 0)
//         std::cout << "ERROR opening socket" << std::endl;
//     /*
//         A sockaddr_in is a structure containing an internet address. This structure is defined in netinet/in.h.
//     */
//     struct sockaddr_in serv_addr, cli_addr;
//     bzero((char *)&serv_addr, sizeof(serv_addr));
//     serv_addr.sin_family = AF_INET;
//     serv_addr.sin_port = htons(3000);
//     serv_addr.sin_addr.s_addr = INADDR_ANY;
//     /*
//     The bind() system call binds a socket to an address, in this case the address of the current host and port number on which the server will run
//     */
//     if (bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
//     {
//         std::cout << "ERROR on binding" << std::endl;
//         exit(1);
//     }
//     /*
//         The listen system call allows the process to listen on the socket for connections
//     */
//     listen(sockfd, 20);
//     while (1)
//     {
//         std::cout << "\n+++++++ Waiting for new connection ++++++++\n\n"
//                   << std::endl;
//         if ((newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen)) < 0)
//             std::cout << "can t accept " << std::endl;
//         char buffer[30000];
//         n = read(newsockfd, buffer, 30000);
//         read(fd, str, 5000000);
//         printf("%s\n", buffer);
//         write(newsockfd ,str, 5000000);
//         // write(newsockfd, str, strlen(str));
//         // printf("------------------Hello message sent-------------------\n");
//         close(newsockfd);
//     }
//     return 0;
// }
