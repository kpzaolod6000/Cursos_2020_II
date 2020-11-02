#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

#include <pthread.h>

int sum;/*este dato es compartido por el threads*/

void *runner(void *param)/*threads llama esta funcion*/{
    int i,upper = atoi(param);
    sum = 0;

    for(i = 1; i <= upper; i++)
        sum+=i;
    pthread_exit(0);
}


int main(int argc,char *argv[])
{
	pthread_t tid; /*identificador del threads*/
    pthread_attr_t attr;/*conjunto de atributos de threads (hilo)*/

    /*establecer los atributos predeterminados de los thread*/
	pthread_attr_init(&attr);
    /*crea el thread*/
    pthread_create(&tid,&attr,runner,argv[1]);
    /*espera a que el threads termine*/
	pthread_join(tid, NULL);
    
    printf("suma %d\n",sum);
    
	return 0;
}