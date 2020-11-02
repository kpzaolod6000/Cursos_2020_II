
#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
int main(){
  pid_t childpid ;
  pid_t grandchildpid ;

  int wstatus;
  printf("\nHola de nuevo soy el hijo PID =  %d,voy a crear un hijo \n",getpid());
  childpid = fork();

  if(childpid == 0)/*nieto*/
  {
    grandchildpid = fork();
    if( grandchildpid == 0){
      sleep(5);
      printf("\nProceso de envio de Señales\n");
      sleep(5);
      kill(getppid(),SIGFPE);
      sleep(5);
      kill(getppid(),SIGSEGV);
      sleep(5);
      kill(getppid(),SIGTERM);
      sleep(5);
      kill(getppid(),SIGCHLD);
      sleep(5);
      kill(getppid(),SIGINT);
      exit(0);
    }else if (grandchildpid > 1){
      printf("Mi hijo es , PID = %d \n",getpid()) ;
      printf("[GRANDCHILD]: Cargare un comando ejecutador nieto.c.\n");

      printf("...\n");
      sleep(5);
      /*Reemplaza el Proceso nieto por el archivo ejecutable nieto.c*/
      execlp("./nieto","nieto",(char*) NULL);
      printf("[CHILD]: Si ves esto, no se pudo ejecutar el programa!\n");
    }
    else{/*error pid == -1*/
      perror("E impossivel criar um filho") ;
      exit(-1) ;
    }

  }
  else if(childpid > 0)
  {
    int rest;
    printf("[CHILD]: Esperando el proceso hijo.\n");

    /*El proceso hijo espera al proceso nieto con el comando waitpid*/
    rest = waitpid(childpid,&wstatus,WUNTRACED | WCONTINUED);
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
    printf("[CHILD]: Mi hijo con su PID %d termino.\n",rest);
  }
  else{
    perror("E impossivel criar um filho") ;
    exit(-1) ;
  }


  sleep(5);
  return 0;
}
