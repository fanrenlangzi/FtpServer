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

    uid_t user_uid;

    int ascii_mode;
} session_t;

//初始化session
void session_init(session_t *sess);

//处理会话，这里主要是创建nobody与ftp子进程
void session_begin(session_t *sess);


#endif  /*SESSION_H*/
