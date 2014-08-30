#include "session.h"
#include "common.h"
#include "ftp_nobody.h"
#include "ftp_proto.h"

void session_init(session_t *sess)
{
	memset(sess->command, 0, sizeof (sess->command));
	memset(sess->comm, 0, sizeof (sess->comm));
	memset(sess->args, 0, sizeof (sess->args));
	sess->peerfd = -1;
	sess->nobody_fd = -1;
	sess->proto_fd = -1;

	sess->ascii_mode = 0;
}

void session_begin(session_t *sess)
{
	int fds[2];
	if(socketpair(PF_UNIX, SOCK_STREAM, 0, fds) == -1)
		ERR_EXIT("socketpair");

	pid_t pid;
	if((pid = fork()) == -1)
		ERR_EXIT("fork");
	else if(pid == 0)
	{
		close(fds[0]);
		sess->proto_fd = fds[1];
		handle_proto(sess);
	}
	else
	{
		close(fds[1]);
		sess->nobody_fd = fds[0];
		handle_nobody(sess);
	}

}