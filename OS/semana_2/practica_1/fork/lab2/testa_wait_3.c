/* arquivo test_wait0.c */

#include <errno.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{

	pid_t childpid;
	int retornoWaitpid;

	if ((childpid=fork()) == 0) {
		printf("\tOi, eu sou o Filho1, PID = %d, PPID = %d.\n",getpid(),getppid()) ;
		printf("\tVou ficar num loop infinito.\n") ;
		for(;;) ;
	}else {
		printf("\tSou o pai... vou ficar esperando meu filho morrer\n") ;//Yo soy el padre ... estaré esperando que mi hijo muera
		while (1){
			retornoWaitpid = waitpid(-1, NULL, WNOHANG);
			//retornoWaitpid = wait(NULL);
			printf("INT %i\n",retornoWaitpid);
   			if ((retornoWaitpid == -1) && (errno != EINTR)){
				printf("\t mi hijo murio :(\n");
				break;}
			else {
				printf("\tMeu filho ainda nao morreu ... vou FAZER OUTRA COISA... depois checo novamente se ele já morreu...!\n") ;
				//Mi hijo aún no ha muerto ... HARÉ CUALQUIER COSA ... luego volveré a comprobar si ya ha muerto ...
				sleep(5);
			}
		}
	}

	exit(0);
}
