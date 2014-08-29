.PHONY:clean
CC=gcc
CFLAGS=-Wall -g
BIN=FtpServer
OBJS=main.o sysutil.o session.o strutil.o ftp_nobody.o ftp_proto.o configure.o parse_conf.o
$(BIN):$(OBJS)
	$(CC) $(CFLAGS) $^ -o $@
%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@
clean:
	rm -f *.o $(BIN)
