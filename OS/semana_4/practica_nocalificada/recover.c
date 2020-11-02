#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <setjmp.h> // for long jump
#include <stdbool.h>  // for long jump

//nivel de kernel

jmp_buf env; // for saving longjmp environment
jmp_buf env2;
int count = 0;

void handler(int sig, siginfo_t *siginfo, void *context)//señal,pid iforma quien mato por ejejmplo,
{
    printf("handler: sig=%d from PID=%d UID=%d count=%d\n",
           sig, siginfo->si_pid, siginfo->si_uid, ++count);

    //printf("\nlong jump? (y|n)");
    //if (getchar() =='y')
        //longjmp(env, 1234);
    switch (sig) {
      case SIGFPE:/* value */
        if (count >= 4) // let it occur up to 4 times
          longjmp(env2, 1234);
        break;
      case SIGSEGV:
        if (count >= 4) // let it occur up to 4 times
          longjmp(env, 1234);
        break;
    }

}
/*void BAD()
{
  fputs("Caught SIGINT: interactive attention signal, probably a ctrl+c.\n", stderr);
}*/

int divide_by_zero() {
  int a = 1;
  int b = 0;
  printf("in divide_by_zero(): try to dereference NULL pointer\n");
  int c = a/b;
  printf("should not see this line\n");
  return c;
}

void BAD()
{
    int *ip = 0;
    printf("in BAD(): try to dereference NULL pointer\n");
    *ip = 123; // dereference a NULL pointer
    printf("should not see this line\n");
}

int main(int argc, char *argv[])
{
    int r;
    struct sigaction act;
    memset(&act, 0, sizeof(act));
    act.sa_sigaction = &handler;
    act.sa_flags = SA_SIGINFO;
    //sigaction(SIGSEGV, &act, NULL); // install SIGSEGV catcher
    sigaction(SIGSEGV, &act, NULL);
    sigaction(SIGFPE, &act, NULL);
    printf("\naquiiii\n");


    //pause();// para hacer que no prosiga el proceso
    if ((r = setjmp(env)) == 0){ // call setjmp(env)
        printf("\ncuantas veces entra\n");
        //divide_by_zero();
        BAD();                        // call BAD()
    }else{
        printf("proc %d survived SEGMENTATION FAULT: r=%d\n", getpid(), r);
        //sigaction(SIGCONT, &act, NULL);
        //return 1;
    }
    printf("proc %d looping\n", getpid());


  //  sigaction(SIGFPE, &act, NULL);
  /*  count = 0;
    printf("\naquiiii\n");
    if ((r = setjmp(env2)) == 0){ // call setjmp(env)
        printf("\ncuantas veces entra\n");
        divide_by_zero();
        //BAD();                        // call BAD()
    }else{
        printf("proc %d survived Floating Pointer Exception: r=%d\n", getpid(), r);
        //sigaction(SIGCONT, &act, NULL);
        //return 1;
    }*/
    while (1)
        ;

    return 0;
}
