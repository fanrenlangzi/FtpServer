#include "ftp_proto.h"
#include "common.h"
#include "sysutil.h"

//子进程不断的从FTP客户端接收FTP指令，并给与回应
void handle_proto(session_t *sess)
{
	
	writen(sess->peerfd, "220 (FtpServer 1.0)\r\n", strlen("220 (FtpServer 1.0)\r\n"));
	while(1)
	{
		//int ret = readline(sess->peerfd, )
		for(;;) pause();
	}
}