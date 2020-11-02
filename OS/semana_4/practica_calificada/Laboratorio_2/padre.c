
#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
int main()
{
  pid_t pid ;
  int wstatus;
	printf("Soy el padre, PID =  %d,voy a crear un hijo\n",getpid()) ;
	pid = fork() ;

	if(pid == 0) /* hijo */
	{
		printf("Mi hijo es, PID = %d\n",getpid());
    printf("[CHILD]: Cargare un comando ejecutador hijo.c.\n");
    printf("...\n");
    sleep(5);
    /*Reemplaza el Proceso hijo por el archivo ejecutable hijo.c*/
    execlp("./hijo","hijo",(char*) NULL);
    printf("[CHILD]: Si ves esto, no se pudo ejecutar el programa!\n");
  }
	else if(pid > 0)/* padre */
	{
    int rest;
    printf("[PARENT]: Esperando el proceso hijo.\n");

    /*El proceso padre espera al proceso hijo con el comando waitpid*/
    rest = waitpid(pid,&wstatus,WUNTRACED | WCONTINUED);
    if (rest == -1) {
         perror("waitpid");
         exit(EXIT_FAILURE);
     }

     if (WIFEXITED(wstatus)) {
         printf("exited, status=%d\n", WEXITSTATUS(wstatus));
     } else if (WIFSIGNALED(wstatus)) {
         printf("killed by signal %d\n", WTERMSIG(wstatus));
     } else if (WIFSTOPPED(wstatus)) {
         printf("stopped by signal %d\n", WSTOPSIG(wstatus));
     } else if (WIFCONTINUED(wstatus)) {
         printf("continued\n");
     }
    printf("[PARENT]: Mi hijo con su PID %d termino.\n",rest);
	}
  else{
    perror("E impossivel criar um filho") ;
		exit(-1) ;
  }
  return 0;
}
