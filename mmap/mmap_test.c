#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <string.h>
#include <stdio.h>

int main(void)
{
	int fd,i;
	char buf[]="hello world.\n";
	char *start;
	
	fd = open("/dev/globalmem", O_RDWR); 
	
	start = mmap(NULL, 4096, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
	if(start == MAP_FAILED) /* 判断是否映射成功 */
		printf("mmap error!!!\n");
	//printf("%s", start);
	//strcat(start, buf);
	for(i=0;i<4096;i++)
		printf("%c", start[i]);
	
	munmap(start, 4096); /* 解除映射 */
	close(fd);
    
	return 0;
}