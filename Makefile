.PHONY:clean
CC=gcc
CFLAGS=-Wall -g
BIN=FtpServer
OBJS=main.o sysutil.o session.o strutil.o ftp_nobody.o ftp_proto.o configure.o parse_conf.o command_map.o
LIB=-lcrypt
$(BIN):$(OBJS)
	$(CC) $(CFLAGS) $^ -o $@ $(LIB)
%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@
clean:
	rm -f *.o $(BIN)
