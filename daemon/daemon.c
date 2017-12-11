/*
*a simple daemon. 
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <syslog.h>

int main(void)
{
	pid_t pid;
	int fd, i;
	char *buf = "Just a daemon.";
	
	if((pid = fork()) < 0)
		printf("fork error.\n");
	else if(pid > 0)
	{
		exit(0);
	}
	setsid();
	chdir("/");
	umask(0);
	for(i=0; i<getdtablesize(); i++)
	{
		close(i);
	}
	
	while(1)
	{
		if((fd = open("/tmp/daemon.log", O_CREAT|O_RDWR|O_APPEND, 0600)) < 0)
		{
			openlog("daemon", LOG_CONS|LOG_PID, LOG_LPR);
			syslog(LOG_ERR, "open error for %s: %m\n", "daemon");
		}
		write(fd, buf, strlen(buf)+1);
		openlog("daemon", LOG_CONS|LOG_PID, LOG_LPR);
		syslog(LOG_USER|LOG_INFO, "%s: %m\n", "that's ok");
		close(fd);
		sleep(10);
	}
	return 0;
}	
