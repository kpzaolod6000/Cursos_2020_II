#include <stdio.h>   // puts(), printf()
#include <signal.h>  // SIGFPE, SIGSEGV, SIGINT
#include <stdlib.h>  // exit(), EXIT_SUCCESS, EXIT_FAIURE
#include <unistd.h>  // getpid(), pause()
#include <stdbool.h> // true, false

bool done = false;

int divide_by_zero() {
  int a = 1;
  int b = 0;
  return a / b;
}

void segfault() {
  int *ptr = NULL;
  *ptr = 42;
}

void signal_handler(int s){
  switch(s) {
    case SIGFPE:
      fputs("Caught SIGFPE: arithmetic exception, such as division by zero.\n", stderr);
      exit(EXIT_FAILURE);//CON ESTE COMANDO TERMINA EL proceso SI LO QUITO SE QUEDA CARGANDO
      break;
    case SIGSEGV:
      fputs("Caught SIGSEGV: segfault.\n", stderr);
      exit(EXIT_FAILURE);
      break;
    case SIGINT:
      fputs("Caught SIGINT: interactive attention signal, probably a ctrl+c.\n", stderr);
      //exit(EXIT_FAILURE);
      break;
    case SIGUSR1:
      puts("Hello!");
      break;
  }
}

int main(void) {

  printf("My PID = %ld\n", (long) getpid());

  // Install signal handlers.
  signal(SIGFPE, signal_handler);//float points insertion //8
  signal(SIGSEGV, signal_handler);//11
  signal(SIGINT, signal_handler);//2
  //suposicion:cuando invoca estas señalaes programadas empieza a trabajar con ellas y no con el del sistema
  //cuando se kilea en el terminal con kill -s [8 o 11 o 2 o ...] pid y se recupera la señal activand estas 3
  //empieza a trabajr con la funcion signal_handler y si el case tiene exit(EXIT_FAILURE); acaba el programada
  //mientras tanto cuando se kilea sin activar estas señales y kileando con kill ... lo hace normalmente
  //y si se desea ver que paso con el programa solo se coloca bg y aparece un mensaje por parte del program segun que señal mandaste

  //divide_by_zero();
  //segfault();

 // Wait until a signal is delivered.

  while (true){}//si no llamo a la funcion signal(SIGINT, signal_handler) puedo matarlo pero si lo llamo no :C
  //con ctrl+z lo envio a background y bg lo recupero  y sale ./sig &
  //despues veo si s ESTA EN R con ps -l de ahi lo mato con kill -s 9 pid
  //de ahi vuelvo a ver   ps -l y des pues pongo bg y me indica que la operacion en background fue killed

  //kill por medio del termianl llama a la funcion signals por ejemplo sis se ejecuta y se envia
  //al background y luego se kill -s 8 pid que es SIGFPE entoces imprime el mensaje y lo mata
  //porque lo mata ? porque tiene el exit en la funcion signals y si lo quito el programa sigue corriendo verificar con ps -l y bg
  //ojo el kill -s 9 pid es el un comando que si o si le saca su mrda al proceso, pero no se puede registrar su llamado solo mata


  pause();//pausa el programa

  puts("I'm done!");

  exit(EXIT_SUCCESS);
}
