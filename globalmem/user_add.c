#include <stdio.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>

#define BUFFSIZE 4096
//#define MEM_CLEAR 0x1

int main(void)
{
        int fd,n,m;
        char buf1[BUFFSIZE];
	char buf2[BUFFSIZE];

        if((fd = open("/dev/globalmem", O_RDWR)) == -1) 
                printf("open error\n");
        else
                printf("fd = %d\n",fd);

	
	while((n = read(STDIN_FILENO, buf1, BUFFSIZE)) > 0)
	{   
		if(write(fd, buf1, n) != n)
			printf("write error1\n");
		
		/*while((m = read(fd, buf2, BUFFSIZE)) > 0)
		{   
			if(write(STDOUT_FILENO, buf2, m) != m)
				printf("write error2\n");
		}*/   
	
	}   
	//else
		//printf("read error\n");	
		
       	
	
	//if(ioctl(fd, MEM_CLEAR, NULL) == -1)
		//printf("ioctl error\n");
	
	
        close(fd);

        return 0;
}

