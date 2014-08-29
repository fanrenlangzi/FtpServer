#include "ftp_proto.h"
#include "common.h"
#include "sysutil.h"
#include "strutil.h"

//子进程不断的从FTP客户端接收FTP指令，并给与回应
void handle_proto(session_t *sess)
{
	
	writen(sess->peerfd, "220 (FtpServer 1.0)\r\n", strlen("220 (FtpServer 1.0)\r\n"));
	while(1)
	{
		int ret = readline(sess->peerfd, sess->command, MAX_COMMAND);
		if(ret == -1)
		{
			if(errno == EINTR)
				continue;
			ERR_EXIT("readline");
		}
		else if(ret == 0)
		{
			exit(EXIT_SUCCESS);
		}
		str_trim_crlf(sess->command);
		str_split(sess->command, sess->comm, sess->args, ' ');
		printf("COMMD=[%s], ARGS=[%s]\n", sess->comm, sess->args);
	}
}