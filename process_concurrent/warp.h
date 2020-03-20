#ifndef ERRO_H
#define ERRO_H

void perr_exit(const char *s); //错误处理
int Accept(int fd, struct sockaddr *sa, socklen_t *salenptr); //接收错误处理
int Bind(int fd, const struct sockaddr *sa, socklen_t salen); //绑定
int Connect(int fd, const struct sockaddr *sa, socklen_t salen); //链接
int Listen(int fd, int backlog); //设置最大链接个数
int Socket(int family, int type, int protocol); //套接字
ssize_t Read(int fd, void *ptr, size_t nbytes); //read  
ssize_t Write(int fd, const void *ptr, size_t nbytes); //write
int Close(int fd); //关闭套接字
ssize_t Readn(int fd, void *vptr, size_t n); //规定读多少
ssize_t Writen(int fd, const void *vptr, size_t n); //规定写多少
ssize_t my_read(int fd, char *ptr); //每次读一个字符
ssize_t Readline(int fd, void *vptr, size_t maxlen); //读一行

#endif