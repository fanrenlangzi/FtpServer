#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <dirent.h>
#include <sys/types.h>


#define ERR_EXIT(m) \
    do { \
        perror(m);\
        exit(EXIT_FAILURE);\
    }while(0)


int main(int argc, const char *argv[])
{
    DIR *dir = opendir(".");
    if(dir == NULL)
        ERR_EXIT("opendir");

    struct dirent *dr;
    while((dr = readdir(dir)))
    {
    	if(dr->d_name[0] == '.')
    		continue;
    	printf("%s\n", dr->d_name);
    }

    closedir(dir);
    return 0;
}
