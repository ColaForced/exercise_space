#ifndef _TCP_SOCKET_HPP
#define _TCP_SOCKET_HPP

#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <string>
#include <iostream>


using std::string;
using std::cout;
using std::endl;

class TcpSocket
{   
    public:
        TcpSocket();
        TcpSocket(int socket);
        ~TcpSocket();
        int connect_to_host(string ip, unsigned short port);
        int send_msg(string msg);
        string reveive_msg();


    private:
        int readn(char *buf, int size);
        int writen(const char*msg, int size);
    
    private:
        int fd;
};


TcpSocket::TcpSocket()
{
    this->fd = socket(AF_INET, SOCK_STREAM, 0);
}


TcpSocket::TcpSocket(int socket)
{
    this->fd = socket;
}


TcpSocket::~TcpSocket()
{
    if(this->fd > 0) close(this->fd);
}


int TcpSocket::connect_to_host(string ip, unsigned short port)
{
    struct sockaddr_in saddr;
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(port);
    inet_pton(AF_INET, ip.data(), &saddr.sin_addr.s_addr);
    int ret = connect(this->fd, (struct sockaddr*)&saddr, sizeof(saddr));
    if (ret == -1)
    {
        perror("connect");
        return -1;
    }
    cout << "success in connection to server..." << endl;
    return ret;
}


int TcpSocket::send_msg(string msg)
{
    char *data = new char[msg.size()+4];
    int bigLen = htonl(msg.size());
    memcpy(data, &bigLen, 4);
    memcpy(data+4, msg.data(), msg.size());
    int ret = writen(data, msg.size()+4);
    delete[] data;
    return ret;
}


string TcpSocket::reveive_msg()
{
    int len = 0;
    readn((char*)&len,4);
    len = ntohl(len);
    cout<<"the size of data :"<<len<<endl;

    char *buf = new char[len + 1];
    int ret = readn(buf, len);
    
    if(ret != len) return string();

    buf[len] = '\0';
    string retStr(buf);
    delete[] buf;
    return retStr;
}


int TcpSocket::readn(char*buf, int size)
{
    int n_read = 0;
    int left = size;
    char *p = buf;

    while(left > 0)
    {
        if(n_read = read(this->fd, p, left) > 0)
        {
            p += n_read;
            left -= n_read;
        }
        else if(n_read == -1)
        {
            return -1;
        }
    }
    return size;
}


int TcpSocket::writen(const char*msg, int size)
{
    int left = size;
    int n_write = 0;
    const char *p = msg;

    while (left>0)
    {
        if((n_write = write(this->fd, msg, left)) > 0)
        {
            p += n_write;
            left -= n_write;
        }
        else if(n_write == -1)
        {
            return -1;
        }
    }
    return size;
}


#endif