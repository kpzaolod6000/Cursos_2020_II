#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <setjmp.h> // for long jump
#include <stdbool.h> // true, false
#define EVER ;;

//nivel de kernel

jmp_buf env;
int count = 0;
int cont = 0;
void handler(int sig, siginfo_t *siginfo, void *context){
    printf("handler: sig=%d from PID=%d UID=%d count=%d\n",sig, siginfo->si_pid, siginfo->si_uid, ++count);
    cont++;
    switch(sig) {
    case SIGFPE:
      fputs("Caught SIGFPE: arithmetic exception, such as division by zero.\n..\n", stderr);
      cont = 0;
    break;
    case SIGSEGV:
      fputs("Caught SIGSEGV: segfault.\n..\n", stderr);
      cont = 0;
      break;
    case SIGTERM:
      fputs("Caught SIGTERM: Muerte suave.\n..\n", stderr);
      cont = 0;
      break;
    case SIGCHLD:
      fputs("Caught SIGCHLD:Ignora la señal del hijo que termino.\n..\n", stderr);
      cont = 0;
      break;
    case SIGINT:
      fputs("Caught SIGINT: interactive attention signal, probably a ctrl+c.\n..\n", stderr);
      if (cont == 1){
          cont = 0;
          /*Regresando al punto de recuperacion*/
          longjmp(env, 1234);
      }
      cont = 0;
      break;
    case SIGUSR1:
      puts("Hello!");
      break;
    }
}

int main(int argc, char *argv[])
{
    int r;
    struct sigaction act;
    memset(&act, '\0', sizeof(act));
    act.sa_sigaction = &handler;
    act.sa_flags = SA_SIGINFO;

    sigaction(SIGFPE, &act, NULL);
    sigaction(SIGSEGV, &act, NULL);
    sigaction(SIGTERM, &act, NULL);
    sigaction(SIGCHLD, &act, NULL);
    sigaction(SIGINT, &act, NULL);
    /*Estableciendo el punto de recuperacion con el setjmp*/
    if ((r = setjmp(env)) == 0){
        printf("Se ha detectado señales de interrupcion\n ");
    }else{
        printf("proc %d he sobrevivido a la señal de iteraccion ctrl^c r=%d\n...\n", getpid(), r);

        return 0;
    }
    for(EVER){;}

    return 0;
}
