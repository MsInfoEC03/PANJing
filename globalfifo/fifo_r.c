#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define MAXLINE 4096
int main(void)
{
	int fd;
	int n = 0;
	
	char buf[MAXLINE];
		
	if((fd = open("/dev/globalfifo", O_RDWR|O_NONBLOCK)) == -1)
		//if((fd1 = open("/dev/globalfifo", O_RDWR)) == -1)
			printf("open1 error\n");
	while(1)
	{
		n = read(STDIN_FILENO, buf, MAXLINE);
		write(fd, buf, n);
	}
	close(fd);

    
	return 0;
}
