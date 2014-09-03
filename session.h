#ifndef SESSION_H
#define SESSION_H 

#include "common.h"
#define MAX_COMMAND 1024

typedef struct{

	char command[MAX_COMMAND]; //client发来FTP指令
	char comm[MAX_COMMAND];	//FTP指令
	char args[MAX_COMMAND];	//FTP指令的参数

    int peerfd; //客户连接的fd

    int nobody_fd; //nobody所使用的fd
    int proto_fd;  //proto进程使用的fd

    uid_t user_uid;	//用户的uid
    int ascii_mode;	//是否为ascii传输模式

    struct sockaddr_in *p_addr; //port模式下对方的ip和port
    int data_fd; //数据传输fd
    int listen_fd; //监听fd，用于PASV模式

    long long restart_pos;  //文件传输断点
    char *rnfr_name;    //文件重命名 RNTR RNTO
} session_t;

//初始化session
void session_init(session_t *sess);

//将三个字符数组置位
void session_reset_command(session_t *sess);

//处理会话，这里主要是创建nobody与ftp子进程
void session_begin(session_t *sess);


#endif  /*SESSION_H*/
