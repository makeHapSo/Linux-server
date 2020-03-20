#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <ctype.h>
#include <unistd.h>
#include <fcntl.h>

#include "warp.h"

#define MAXLINE 4096
#define SERV_PORT 8000

struct clie_pre{
    struct sockaddr_in cliaddr;
    int cfd
};

void *pthe_work(void *arge)
{
    int n,i;
    struct clie_pre *ptr = (struct clie_pre*)arge;
    char buf[MAXLINE];
    char str[INET_ADDRSTRLEN]; //#define INET_ADDRSTRLEN 16  可用"[+d"查看

    while(1){
        n = Read(ptr->cfd, buf, MAXLINE); //读客户端
        if(n == 0){
            printf("客户端 %d 关闭\n", ptr->cfd);
            break;  //跳出循环,关闭cfd
        }
        printf("接收到 %s 从端口 %d\n",
                inet_ntop(AF_INET, &(*ptr).cliaddr.sin_addr, str, sizeof(str)),
                ntohs((*ptr).cliaddr.sin_port));   //打印客户端信息(IP/PORT)

        for (i = 0; i < n; i++) 
            buf[i] = toupper(buf[i]);                   //小写-->大写

        Write(STDOUT_FILENO, buf, n);                //写出至屏幕
        Write(ptr->cfd, buf, n);
    }
    Close(ptr->cfd);
    return (void *)0;
}

int main()
{
    struct sockaddr_in servaddr, cliaddr;
    socklen_t cliaddr_len;
    int cfd, lfd;
    int i = 0;
    pthread_t tid;
    struct clie_pre clie_pre[256]; //根据最大线程数创建结构体数组.

    lfd = Socket(AF_INET, SOCK_STREAM, 0);

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(SERV_PORT);

    Bind(lfd, (struct serveaddr*)&servaddr, sizeof(servaddr));

    Listen(lfd, 128);

    while(1){
        cliaddr_len = sizeof(cliaddr);
        cfd = Accept(lfd, (struct serveraddr*)&cliaddr, &cliaddr_len);
        clie_pre[i].cliaddr = cliaddr;
        clie_pre[i].cfd = cfd;
        pthread_create(&tid, NULL, pthe_work, (void *)&clie_pre[i]);
        pthread_detach(tid);
        i++;
    }
    return 0;
}
