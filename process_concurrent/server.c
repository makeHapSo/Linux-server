#include <stdio.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>
#include <sys/wait.h>
#include <ctype.h>
#include <unistd.h>

#include "warp.h"

#define MAXLINE 4096
#define SERV_PORT 8000

void sigchild(int tempnum)
{
    while(waitpid(0, NULL, WNOHANG) > 0){

    }
    return;
}

int main()
{
    pid_t pid;
    int lfd, cfd;
    int i, n;
    char buf[MAXLINE];
    char str[INET_ADDRSTRLEN];
    struct sockaddr_in servaddr, cliaddr;
    socklen_t cliaddr_len;
    struct sigaction newact;

    newact.sa_handler = sigchild;
    sigemptyset(&newact.sa_mask);
    newact.sa_flags = 0;
    sigaction(SIGCHLD, &newact, NULL); //sigaction函数的功能是检查或修改与指定信号相关联的处理动作（可同时两种操作）

    lfd = Socket(AF_INET, SOCK_STREAM, 0);
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(SERV_PORT);
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    Bind(lfd, (struct sockteaddr*)&servaddr, sizeof(servaddr));

    Listen(lfd,10);

    while (1) {
        cliaddr_len = sizeof(cliaddr);
        cfd = Accept(lfd, (struct sockaddr *)&cliaddr, &cliaddr_len);
        pid = fork();
        if (pid == 0) {
            Close(lfd);
            while (1) {
                n = Read(cfd, buf, MAXLINE);
                if (n == 0) {
                    printf("另一边已经关闭了.\n");
                    break;
                }
                printf("接收到从 %s 端口 %d\n",
                        inet_ntop(AF_INET, &cliaddr.sin_addr, str, sizeof(str)), //ip
                        ntohs(cliaddr.sin_port)); //端口

                for (i = 0; i < n; i++)
                    buf[i] = toupper(buf[i]);

                Write(STDOUT_FILENO, buf, n);
                Write(cfd, buf, n);
            }
            Close(cfd);
            return 0;
        } else if (pid > 0) {
            Close(cfd);
        }  else
            perr_exit("fork");
    }
    return 0;
}
