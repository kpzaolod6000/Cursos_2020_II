#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/time.h>
#include <time.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/wait.h>


#define MAX_LEN 10000

struct region{
    int len;
    char buf[MAX_LEN];
};

int main()
{    

	/*creacion de un arreglo de struct que funcionara como el buffer*/
    struct region* rptr[MAX_LEN];
    int fd;
    fd = shm_open("/myregion",O_CREAT| O_RDWR, S_IRUSR | S_IWUSR);


    if(fd == -1){
        printf("shared memory failed\n");
		exit(-1);
    }
    if(ftruncate(fd,sizeof(struct region)) == -1){
        printf("shared memory failed\n");
        exit(-1);
    }
	/*Mapeo de cada struct segun el indice para ser compartida*/
    for(int i = 0; i< MAX_LEN ; i++){
        rptr[i] = mmap(NULL,sizeof(struct region), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    }
    for(int i = 0; i< MAX_LEN ; i++){
        if (rptr[i] == MAP_FAILED) {
            printf("Map failed\n");
            return -1;
        }
    }
    

    int in = 0;
    int out = MAX_LEN-1;
    int status;
            char fmt[16], buf[16];
            struct timeval tv;
            struct tm tm;

            gettimeofday(&tv, NULL);
            tm = *localtime(&tv.tv_sec);
            strftime(fmt, sizeof fmt, "%H:%M:%S.%%03u", &tm);
            snprintf(buf, sizeof buf, fmt, tv.tv_usec);
            printf("[%s] ",buf);
	/*struct auxiliar como el siguiente productor*/
    
    struct region next_producer;
    
    
    while (1)
    {  
        pid_t pid;
	/*creacion del los procesos*/
        pid = fork();
        if (pid < 0) { 
            fprintf(stderr, "Fork Failed");
            return 1;
        }
        else if (pid == 0) {
		/*Tiempo de creacion del hijo*/
            char f[16], time_ms[16];
            struct timeval tvh;
            struct tm tmh;

            gettimeofday(&tvh, NULL);
            tmh = *localtime(&tvh.tv_sec);
            strftime(f, sizeof f, "%H:%M:%S.%%03u", &tmh);
            snprintf(time_ms, sizeof time_ms, f, tvh.tv_usec);

            next_producer.len = getpid();
            strcpy(next_producer.buf,time_ms);
            
            while (((in+1) % MAX_LEN) ==  out)
            {
                ;
            }
		/*copiando la estructura auxiliar en una posicion del buffer disponible*/
            memcpy(rptr[in], &next_producer, sizeof next_producer);
		/*imprimiendo la hora y la creacion del proceso hijo con su PID*/
            printf("P(%d): Creando Proceso %d [%s]\n",getppid(),getpid(),time_ms);
 
            in = (in + 1) % MAX_LEN;
            
            srand(time(NULL));
        
            int numero = 1+rand() % (5+1-1); 
            sleep(numero);
            
            
        }
        else {
		int status;
		/*Tiempo de creacion del padre*/		
		/*
            int status;
            char fmt[16], buf[16];
            struct timeval tv;
            struct tm tm;

            gettimeofday(&tv, NULL);
            tm = *localtime(&tv.tv_sec);
            strftime(fmt, sizeof fmt, "%H:%M:%S.%%03u", &tm);
            snprintf(buf, sizeof buf, fmt, tv.tv_usec);
            printf("[%s] ",buf);
           */
            wait(&status);
       
        }
    }
   
    return 0;
}
