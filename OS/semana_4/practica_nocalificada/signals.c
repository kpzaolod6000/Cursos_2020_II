#include <stdio.h>   // puts(), printf()
#include <signal.h>  // SIGFPE, SIGSEGV, SIGINT
#include <stdlib.h>  // exit(), EXIT_SUCCESS, EXIT_FAIURE
#include <unistd.h>  // getpid(), pause()
#include <setjmp.h>
#include <stdbool.h> // true, false
#include <string.h>

bool done = false;
jmp_buf env; // for saving longjmp environment
int count = 0;

int divide_by_zero() {
  int a = 1;
  int b = 0;
  return a / b;
}

void segfault() {
  int *ptr = NULL;
  *ptr = 42;
}
void sigintss()
{
  fputs("Caught SIGINT: Señal iteractiva,probablemente sea un  ctrl+c.\n", stderr);
}

//void signal_handler(int s) {
void signal_handler(int sig, siginfo_t *siginfo, void *context) {
  printf("handler: sig=%d from PID=%d UID=%d count=%d\n",
         sig, siginfo->si_pid, siginfo->si_uid, ++count);


  switch(sig) {
    case SIGFPE:
      fputs("Caught SIGFPE: arithmetic exception, such as division by zero.\n", stderr);
      printf("long jump? (y|n) ");
      if (getchar() =='y')
          longjmp(env, 111);
      exit(EXIT_FAILURE);
    case SIGSEGV:
      fputs("Caught SIGSEGV: segfault.\n", stderr);
      printf("long jump? (y|n) ");
      if (getchar() =='y')
          longjmp(env, 111);
      exit(EXIT_FAILURE);
      break;
    case SIGINT:
      fputs("Caught SIGINT: interactive attention signal, probably a ctrl+c.\n", stderr);
      printf("long jump? (y|n) ");
      if (getchar() =='y')
          longjmp(env, 111);
      break;
    case SIGUSR1:
      puts("Hello!");
      printf("long jump? (y|n) ");
      if (getchar() =='y')
          longjmp(env, 111);
      break;
  }

}

int main(void) {

  printf("My PID = %ld\n", (long) getpid());


  // signal(SIGFPE,  signal_handler);

  // divide_by_zero();
  // segfault();


  int r;
  struct sigaction act;

	memset (&act, '\0', sizeof(act));

	/* Use the sa_sigaction field because the handles has two additional parameters */
	//act.sa_sigaction = &hdl;
  act.sa_sigaction = &signal_handler;

	/* The SA_SIGINFO flag tells sigaction() to use the sa_sigaction field, not sa_handler. */
	act.sa_flags = SA_SIGINFO;

	/*if (sigaction(SIGINT, &act, NULL) < 0 ) {
		perror ("sigaction");
		return 1;
	}*/
  sigaction(SIGFPE, &act, NULL);
  r = setjmp(env);
  if (r == 0){ // call setjmp(env)
      divide_by_zero();
  }
  else{
      printf("\nproc %d survived Floating Pointing Exception: r=%d\n", getpid(), r);
  }
  sigaction(SIGSEGV, &act, NULL);
  r = setjmp(env);
  if (r == 0){ // call setjmp(env)
      //printf("%d\n" , setjmp(env));
      segfault();
  }
  else{
      printf("\nproc %d survived SEGMENTATION FAULT: r=%d\n", getpid(), r);
      //sigaction(SIGCONT, &act, NULL);
      //return 1;
  }
  sigaction(SIGINT, &act, NULL);
  if ((r = setjmp(env)) == 0){
      sigintss();
      while(1){;}
  }
  else{
      printf("\nproc %d survived al ctrl^c: r=%d\n", getpid(), r);
  }
/*           FALTA          ERROR EN JMP*/


  puts("I'm done!");

  exit(EXIT_SUCCESS);
}
