#include "ftp_proto.h"
#include "common.h"
#include "sysutil.h"
#include "strutil.h"
#include "ftp_codes.h"

void ftp_reply(session_t *sess, int status, const char *text);

void do_user(session_t *sess);

//子进程不断的从FTP客户端接收FTP指令，并给与回应
void handle_proto(session_t *sess)
{
	ftp_reply(sess, FTP_GREET, "(FtpServer 1.0)");
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
		str_upper(sess->comm);
		printf("COMMD=[%s], ARGS=[%s]\n", sess->comm, sess->args);

		if(strcmp("USER", sess->comm) == 0)
			do_user(sess);
	}
}

void ftp_reply(session_t *sess, int status, const char *text)
{
	char tmp[1024] = { 0 };
	snprintf(tmp, sizeof tmp, "%d %s\r\n", status, text);
	writen(sess->peerfd, tmp, strlen(tmp));
}


void do_user(session_t *sess)
{
	struct passwd *pw;
	if((pw = getpwnam(sess->args)) == NULL)
	{
		ftp_reply(sess, FTP_LOGINERR, "Login incorrect.");
		return;
	}

	sess->user_uid = pw->pw_uid;
	ftp_reply(sess, FTP_GIVEPWORD, "Please specify the password.");
}