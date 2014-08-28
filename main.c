#include "common.h"
#include "sysutil.h"
#include "session.h"

int main(int argc, char const *argv[])
{
	if(getuid())
	{
		fprintf(stderr, "FtpServer must be started by root\n");
		exit(EXIT_FAILURE);
	}

	//创建一个监听fd
	int listenfd = tcp_server(NULL, 9981);

	pid_t pid;
	session_t sess;
	session_init(&sess);
	while(1)
	{
		int peerfd = accept_timeout(listenfd, NULL, 10);
		if(peerfd  == -1 && errno == ETIMEDOUT)
			continue;
		else if(peerfd == -1)
			ERR_EXIT("accept_timeout");

		if((pid = fork()) == -1)
			ERR_EXIT("fork");
		else if(pid == 0)
		{
			close(listenfd);
			//
			sess.peerfd = peerfd;
			session_begin(&sess);
		}
		else
		{
			close(peerfd);
		}
	}

	return 0;
}