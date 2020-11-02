#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/time.h>
#include <time.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <string.h>
#include <signal.h>
#include <sys/wait.h>

#define MAX_LEN 10000

struct region{
    int len;
    char buf[MAX_LEN];
};
/*funcion time_partition para separar la hora actual*/
int time_partition(int ini,int fnl1,int fnl2,char HourC[],char HourP[]){
    char timeC[20];
    char timePh[20];
    int indc = 0;
    int indph = 0;
    
    for(int h = ini ;h < fnl1 ; h++){
        timeC[indc++] = HourC[h];
        
    }
    for(int h = ini ;h < fnl2 ; h++){
        timePh[indph++] = HourP[h];
    }
    int tmC = atoi(timeC);
    int tmP = atoi(timePh);
    return abs(tmC-tmP);
}
/*funcion time_diff para separar restar las horas de creacion y las horas de eliminacion del hijo*/
void time_diff(char diff[],char horal[] ,char horaf[] ,int tam1,int tam2){
    strcpy(diff,"");
    for (int j = 0 ,i = 0; i < 4; i++,j+=3)
    {
        if(i == 3){
            char transs[10];
            sprintf(transs,"%d",time_partition(j,tam1,tam2,horal,horaf) );
            strcat(diff,".");
            strcat(diff,transs);
        }
        else
        {
            if(time_partition(j,j+2,j+2,horal,horaf) != 0){
                if(strlen(diff) != 0){
                    char trans[10];
                    sprintf(trans,"%d",time_partition(j,j+2,j+2,horal,horaf) );
                    strcat(diff,":");
                    strcat(diff,trans);
                }else
                {
                    char trans[10];
                    sprintf(trans,"%d",time_partition(j,j+2,j+2,horal,horaf) );
                    strcat(diff,trans);
                }
                
            }
        }
    }
}

int main()
{    
	/*creacion de un arreglo de struct que funcionara como el buffer*/
    struct region* rptr[MAX_LEN];
    int fd;
    fd = shm_open("/myregion",O_RDONLY, 0666);


    if(fd == -1){
        printf("shared memory failed\n");
		exit(-1);
    }
	/*Mapeo de cada struct segun el indice para ser compartida*/
    for(int i = 0; i< MAX_LEN ; i++){
        rptr[i] = mmap(NULL,sizeof(struct region), PROT_READ ,MAP_SHARED, fd, 0);
    }
    
    for(int i = 0; i< MAX_LEN ; i++){
        if (rptr[i] == MAP_FAILED) {
            printf("Map failed\n");
            exit(-1);
        }
    }

	/*struct auxiliar como el siguiente productor*/
    struct region* next_consumer;
    int in = MAX_LEN;
    int out = 0;

    while (1){
	/*tiempo de creacion del proceso actual*/
        char f[16], time_ms[16];
        struct timeval tvh;
        struct tm tmh;
	
        gettimeofday(&tvh, NULL);
        tmh = *localtime(&tvh.tv_sec);
        strftime(f, sizeof f, "%H:%M:%S.%%03u", &tmh);
        snprintf(time_ms, sizeof time_ms, f, tvh.tv_usec);

        while (in == out)
        {
            ;
        }
  
        next_consumer = rptr[out];
    
        out = (out + 1) % MAX_LEN;
	/*KILL al proceso hijo mediante señales con su PID consumido gracias a la memoria compartida*/
        kill(next_consumer->len,SIGKILL);
        int tam1 = strlen(time_ms);
        int tam2 = strlen(next_consumer->buf);
        char diff[20];
	/*operacion de sacar la diferencia entre horas*/
        time_diff(diff,next_consumer->buf,time_ms,tam2,tam1);
	/*imprimiendo la hora y la ELIMINACION del proceso hijo con su PID*/
        printf("[%s] C(%d): Matando Proceso %d (vivió %s)\n",time_ms,getpid(),next_consumer->len,diff);  
        

        srand(time(NULL));
    
        int numero = 1+rand() % (5+1-1); 
        sleep(numero);
    }

    if (shm_unlink("/myregion") == -1) {
		printf("Error removing %s\n","/myregion");
		exit(-1);
	} 

	return 0;
}
