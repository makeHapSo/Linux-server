#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "warp.h"

#define MAXLINE 4096
#define SERV_PORT 8000

int main()
{
    int cfd, n;
    char buf[MAXLINE];
    struct sockaddr_in serveraddr;

    cfd = Socket(AF_INET, SOCK_STREAM, 0);
    bzero(&serveraddr, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    inet_pton(AF_INET, "127.0.0.1", &serveraddr.sin_addr);
    serveraddr.sin_port = htons(SERV_PORT);

    Connect(cfd, (struct sockaddr*)&serveraddr, sizeof(serveraddr));

    while(fgets(buf, MAXLINE, stdin) != NULL){ //从标准输入读MAXLINE长度
        Write(cfd, buf, strlen(buf));
        n = Read(cfd, buf, MAXLINE);
        if (n == 0) {
            printf("另一边已经关闭了.\n");
            break;
        }
        else
            Write(STDOUT_FILENO, buf, n);
    }
    Close(cfd);
    return 0;
}