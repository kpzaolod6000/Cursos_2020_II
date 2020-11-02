
#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() 
{
int pid ;
	
	pid = fork() ;
	if(pid == -1) /* erro */
	{
		exit(-1) ;
	}
	else if(pid == 0) /* filho */
	{
		sleep(10);
        //for(;;){}
        printf("hijo");
		exit(0);
	}
	else /* pai */
	{
        //for(;;){}
        sleep(20);
        printf("padre");
	}
}

