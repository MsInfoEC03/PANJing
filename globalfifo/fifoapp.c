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
	int fd1,fd2;
	int m = 0,n = 0;
	pid_t pid;
	//char buf[12] = "hello world!";
	char buf[MAXLINE];

	if((pid = fork()) < 0)
                printf("fork error\n");
	
	else if(pid > 0)
	{
		if((fd1 = open("/dev/globalfifo", O_RDWR|O_NONBLOCK)) == -1)
		//if((fd1 = open("/dev/globalfifo", O_RDWR)) == -1)
			printf("open1 error\n");
		while(1)
		{
			n = read(STDIN_FILENO, buf, MAXLINE);
			write(fd1, buf, n);
		}
		close(fd1);
	}
	else
	{
		
		if((fd2 = open("/dev/globalfifo", O_RDWR)) == -1)
			printf("open2 error\n");
		
			m = read(fd2, buf, MAXLINE);
			if(m > 0)
			{
				write(STDOUT_FILENO, buf, m);
			}
		
		close(fd2);
	}
    
	return 0;
}
