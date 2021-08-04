// #include <stdio.h>
// #include <ctype.h>
// #include <unistd.h>
// #include <stdlib.h>
// #include <sys/types.h>
// #include <sys/stat.h>
// #include <string.h>
// #include <arpa/inet.h>
// #include <sys/socket.h>
// #include <sys/select.h>



// int main(int argc, char const *argv[])
// {
//     int lfd = socket(AF_INET,SOCK_STREAM,0);
//     if(lfd==-1)
//     {
//         perror("socket");
//         exit(0);
//     }

//     struct sockaddr_in addr;
//     addr.sin_family = AF_INET;
//     addr.sin_port = htons(10000);
//     addr.sin_addr.s_addr = INADDR_ANY;
//     int opt = 1;
//     setsockopt(lfd,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt));
//     int ret = bind(lfd, (struct sockaddr*)&addr, sizeof(addr));

//     if(ret == -1)
//     {
//         perror("bind");
//         exit(0);
//     }

//     ret = listen(lfd,128);

//     if(ret == -1)
//     {
//         perror("listen");
//         exit(0);
//     }


//     fd_set reads, tmp;
//     FD_ZERO(&reads);
//     FD_SET(lfd, &reads);

//     int maxfd = lfd;

//     while (1)
//     {
//         tmp = reads;
//         ret = select(maxfd+1, &tmp, NULL,NULL,NULL);
//         if(ret == -1)
//         {
//             perror("select");
//             exit(0);
//         }

//         if(FD_ISSET(lfd,&tmp))
//         {
//             int cfd = accept(lfd,NULL,NULL);
//             FD_SET(cfd,&reads);
//             maxfd = cfd > maxfd ? cfd : maxfd;
//         }

//         for(int i = lfd+1; i< maxfd; ++i)
//         {
//             if(FD_ISSET(i, &tmp))
//             {
//                 char buf[1024];
//                 memset(buf, 0, sizeof(buf));
//                 int len = read(i, buf, sizeof(buf));
//                 if (len>0)
//                 {
//                     printf("client say: %s\n",buf);
//                     write(i,buf,len);
//                 }

//                 else if (len == 0)
//                 {
//                     printf("client closed the connection\n");
//                     FD_CLR(i, &reads);
//                     close(i);
//                     break;
//                 }

//                 else
//                 {
//                     perror("read");
//                     break;
//                 }
//             }
//         }
//     }

//     return 0;
// }


#include <stdio.h>
#include <ctype.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/select.h>

// server
int main(int argc, const char* argv[])
{
    // 创建监听的套接字
    int lfd = socket(AF_INET, SOCK_STREAM, 0);
    if(lfd == -1)
    {
        perror("socket error");
        exit(1);
    }

    // 绑定
    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(9999);
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);  // 本地多有的ＩＰ
    // 127.0.0.1
    // inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr.s_addr);
    
    // 设置端口复用
    int opt = 1;
    setsockopt(lfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    // 绑定端口
    int ret = bind(lfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    if(ret == -1)
    {
        perror("bind error");
        exit(1);
    }

    // 监听
    ret = listen(lfd, 64);
    if(ret == -1)
    {
        perror("listen error");
        exit(1);
    }

    fd_set reads, tmp;
    FD_ZERO(&reads);
    FD_SET(lfd, &reads);

    int maxfd = lfd;

    while(1)
    {
        tmp = reads;
        int ret = select(maxfd+1, &tmp, NULL, NULL, NULL);
        if(ret == -1)
        {
            perror("select");
            exit(0);
        }

        if(FD_ISSET(lfd, &tmp))
        {
            int cfd = accept(lfd, NULL, NULL);
            FD_SET(cfd, &reads);
            maxfd = cfd > maxfd ? cfd : maxfd;
        }
        for(int i=lfd+1; i<=maxfd; ++i)
        {
            if(FD_ISSET(i, &tmp))
            {
                char buf[1024];
                int len = read(i, buf, sizeof(buf));
                if(len > 0)
                {
                    printf("client say: %s\n", buf);
                    write(i, buf, len);
                }
                else if(len == 0)
                {
                    printf("客户端断开了连接\n");
                    FD_CLR(i, &reads);
                    close(i);
                }
                else
                {
                    perror("read");
                    exit(0);
                }
            }
        }
    }

    return 0;
}
