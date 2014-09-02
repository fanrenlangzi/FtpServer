#include "priv_command.h"
#include "common.h"
#include "sysutil.h"
#include "priv_sock.h"
#include "configure.h"

//获取数据套接字
void privop_pasv_get_data_sock(session_t *sess)
{
	char ip[16] = {0};
	priv_sock_recv_str(sess->nobody_fd, ip, sizeof ip);
	uint16_t port = priv_sock_recv_int(sess->nobody_fd);
	//创建fd
	int data_fd = tcp_client(20);

	struct sockaddr_in addr;
	memset(&addr, 0, sizeof addr);
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr(ip);
	addr.sin_port = htons(port);
	int ret = connect_timeout(data_fd, &addr, tunable_connect_timeout);
	if(ret == -1)
		ERR_EXIT("connect_timeout");
	priv_sock_send_result(sess->nobody_fd, PRIV_SOCK_RESULT_OK);
	priv_sock_send_fd(sess->nobody_fd, data_fd);
	close(data_fd);
}

void privop_pasv_active(session_t *sess)
{

}

void privop_pasv_listen(session_t *sess)
{

}

void privop_pasv_accept(session_t *sess)
{

}
