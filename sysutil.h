#ifndef SYS_UTIL_H
#define SYS_UTIL_H 

#include "common.h"

//创建监听fd
int tcp_server(const char *host, unsigned short port);

int getlocalip(char *ip);

//设置fd为阻塞或者非阻塞
void activate_nonblock(int fd);
void deactivate_nonblock(int fd);

//超时IO函数
int read_timeout(int fd, unsigned int wait_seconds);
int write_timeout(int fd, unsigned int wait_seconds);
int accept_timeout(int fd, struct sockaddr_in *addr, unsigned int wait_seconds);
int connect_timeout(int fd, struct sockaddr_in *addr, unsigned int wait_seconds);

//处理TCP粘包问题
ssize_t readn(int fd, void *buf, size_t count);
ssize_t writen(int fd, const void *buf, size_t count);
ssize_t recv_peek(int sockfd, void *buf, size_t len);
ssize_t readline(int sockfd, void *buf, size_t maxline);

//发送与接收文件描述符
void send_fd(int sock_fd, int fd);
int recv_fd(const int sock_fd);


#endif  /*SYS_UTIL_H*/
