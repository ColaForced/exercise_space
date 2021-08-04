#ifndef _TCP_SERVER_HPP
#define _TCP_SERVER_HPP


#include "tcp_socket.hpp"
#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <string>
#include <iostream>

class TcpServer
{
    public:
        TcpServer();
        ~TcpServer();
        int set_listen(unsigned short port);
        TcpSocket *accept_connection(struct sockaddr_in *addr = nullptr);

    private:
        int fd;
};


TcpServer::TcpServer()
{
    fd = socket(AF_INET, SOCK_STREAM, 0);
}


TcpServer::~TcpServer()
{
    close(fd);
}


int TcpServer::set_listen(unsigned short port)
{
    struct sockaddr_in saddr;
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(port);
    saddr.sin_addr.s_addr = INADDR_ANY;  // 0 = 0.0.0.0
    int ret = bind(this->fd, (struct sockaddr*)&saddr, sizeof(saddr));
    if (ret == -1)
    {
        perror("bind");
        return -1;
    }
    cout << "success in binding, ip: "
        << inet_ntoa(saddr.sin_addr)
        << ", port: " << port << endl;

    ret = listen(this->fd, 128);
    if (ret == -1)
    {
        perror("listen");
        return -1;
    }
    cout << "success in listening..." << endl;

    return ret;
}


TcpSocket* TcpServer::accept_connection(struct sockaddr_in *addr)
{
    if (addr == NULL)
    {
        return nullptr;
    }

    socklen_t addrlen = sizeof(struct sockaddr_in);
    int cfd = accept(this->fd, (struct sockaddr*)addr, &addrlen);
    if (cfd == -1)
    {
        perror("accept");
        return nullptr;
    }
    printf("success in establish the connection with client...\n");
    return new TcpSocket(cfd);

}

#endif