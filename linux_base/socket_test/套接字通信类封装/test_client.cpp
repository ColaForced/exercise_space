#include "tcp_socket.hpp"
#include <string.h>
#include <string>
#include <iostream>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>


using std::string;
using std::cout;
using std::endl;


int main(int argc, char const *argv[])
{
    TcpSocket tcp;
    int ret = tcp.connect_to_host("127.0.0.1", 10000);
    if (ret == -1) {return -1;}
    
    int fd = open("test.txt", O_RDONLY);
    int length = 0;
    char tmp[16];
    memset(tmp, 0, sizeof(tmp));

    while((length = read(fd, tmp, sizeof(tmp))) > 0)
    {
        tcp.send_msg(string(tmp, length));
        cout << "send Msg: " << endl;
        cout << tmp << endl << endl << endl;
        memset(tmp, 0, sizeof(tmp));

        usleep(300);
    }
    sleep(10);
    return 0;
}

