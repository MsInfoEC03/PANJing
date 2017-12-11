#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/select.h>
#include <signal.h>


static void signalio_handler(int signum)
{
	printf("receive a signal from globalfifo,signum:%d.\n", signum);
}

int main(void)
{
	int fd,oflags;
	
	
	fd = open("/dev/globalfifo", O_RDWR, S_IRUSR|S_IWUSR);
	//printf("%d.\n",fd);
		
	if(fd != -1)
	{
		signal(SIGIO, signalio_handler);
		fcntl(fd, F_SETOWN, getpid());
		oflags = fcntl(fd, F_GETFL);
		fcntl(fd, F_SETFL, oflags|FASYNC);
		while(1)
		{
			sleep(100);
		}
	}
	else
		printf("open error\n");
	
	close(fd);
	
    
	return 0;
}
