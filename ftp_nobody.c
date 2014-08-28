#include "ftp_nobody.h"
#include "common.h"
#include "sysutil.h"


void set_nobody();

//nobody时刻准备从子进程接收命令
void handle_nobody(session_t *sess)
{
	//设置为nobody进程
	set_nobody();

	char cmd;
	while(1)
	{
		int ret = readn(sess->nobody_fd, &cmd, sizeof cmd);
		if(ret == -1)
		{
			if(errno == EINTR)
				continue;
			ERR_EXIT("readn");
		}
		for(;;)
			pause();
	}
}

void set_nobody()
{
	//基本思路
	//1.首先获取nobody的uid、gid
	//2.然后逐项进行设置
	struct passwd *pw;
	if((pw = getpwnam("nobody")) == NULL)
		ERR_EXIT("getpwnam");

	if(setegid(pw->pw_gid) == -1)
		ERR_EXIT("setegid");
	
	if(seteuid(pw->pw_uid) == -1)
		ERR_EXIT("seteuid");
	
}