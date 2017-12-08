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
	int m = 0;
	pid_t pid;
	//char buf[12] = "hello world!";
	char buf[MAXLINE];
		
	if((fd = open("/dev/globalfifo", O_RDWR|O_NONBLOCK)) == -1)
		printf("open2 error\n");
	//while(1)
	//{
		m = read(fd, buf, MAXLINE);
		if(m > 0)
		{
			write(STDOUT_FILENO, buf, m);
		}
	//}
	close(fd);

    
	return 0;
}
