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

#define MAXLINE 4096

int main(void)
{
	int fd;
	//int num;
	//char rd_ch[20];
	fd_set rfds, wfds;
	
	fd = open("/dev/globalfifo", O_RDWR|O_NONBLOCK);
	printf("%d.\n",fd);
	if(fd == -1)
	//if((fd1 = open("/dev/globalfifo", O_RDWR)) == -1)
		printf("open error\n");
	else if(fd != -1)
	{
		if(ioctl(fd, 0x1, 0) < 0)
			printf("ioctl command failed\n");
		while(1)
		{
			FD_ZERO(&rfds);
			FD_ZERO(&wfds);
			FD_SET(fd, &rfds);
			FD_SET(fd, &wfds);
			select(fd+1, &rfds, &wfds, NULL, NULL);
			if(FD_ISSET(fd, &rfds))
				printf("Poll monitor:can be read\n");
			if(FD_ISSET(fd, &wfds))
				printf("Poll monitor:can be written\n");
		}
	}
	
	close(fd);
	
    
	return 0;
}
