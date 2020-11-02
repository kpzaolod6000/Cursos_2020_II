# Sistemas Operativos
# Laboratorio 2 Señales
## INTEGRANTES
* PUCHO ZEVALLOS KELVIN PAUL
* PEREZ RODRIGUEZ ANGELO ALDO

## Archivo padre.c
El archivo padre.c se encarga de crear un hijo con la funcion fork(), el cual va a ser modificado ya que no copiara el mismo código del padre sino que gracias a la función execlp()reemplaza todo el código que el hijo va a tomar de padre por un código independiente el cual lo tomara de hijo.c.
El proceso padre espera al proceso hijo con el comando waitpid() recuperando el PID del hijo y su estado de salida

## Archivo hijo.c
El archivo hijo.c se encarga de crear un hijo llamado nieto con la función fork(), el cual como el caso del padre.c y el hijo.c , el hijo de hijo.c al crear un fork() gracias a la función execlp() va a reemplazar el código de hijo.c por nieto.c .

Dentro de la condicional que reconoce al hijo del archivo hijo.c que viene a ser el nieto, se creara un nieto de hijo.c y ese nieto vendría a ser en el programa general un bisnieto de padre.c. 
El cual el bisnieto se encarga de mandar señales con el PID de su padre quien es el nieto de hijo.c , la función del nieto se encarga de ejecutar el comando execlp() para que se pueda reemplazar el proceso nieto por el archivo ejecutable nieto.c , sin esperar al bisnieto.

El proceso hijo al igual que el padre espera al proceso nieto con el comando waitpid() recuperando el PID del nieto y su estado de salida

## Archivo nieto.c
Se implementa la estructura signaction con la funcion handdler,se recupera señales de esta manera sigaction(SIGFPE, &act, NULL para luego tratarlas en la función handdler y luego imprimir su identificador el PID del proceso de quien mando la señal y el UID que viene a ser el usuario y  un contador, cada identificador o señal es tratado por un switch() quien se encarga de verificar que función cumple cada señal imprimiendo un reporteen la terminal dentro de ese switch hay una excepción que es la señal SIGINT el cual contiene el longjmp ()y volveremos al estado de recuperación ignorando la señal SIGINT

## Errores inesperados en el tiempo de ejecución:
Las señales que no se utilizaron nos presentaron errores en el momento de enviarlos por lo cual se prefirió no usarlos porque a veces hacia que la PC quedo suspendida en algunas muchas pruebas 
