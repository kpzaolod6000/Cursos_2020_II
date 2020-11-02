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


#define MAX_LEN 20

struct region{
    int len;
    char buf[MAX_LEN];
};

int main()
{    
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
    for(int i = 0; i< MAX_LEN ; i++){
        rptr[i] = mmap(NULL,sizeof(struct region), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    }
    for(int i = 0; i< MAX_LEN ; i++){
        if (rptr[i] == MAP_FAILED) {
            printf("Map failed\n");
            return -1;
        }
    }
    

    //struct region buffer[MAX_LEN];
    int in = 0;
    int out = MAX_LEN-1;
    struct region next_producer;
    
    
    while (1)
    {   
        
        pid_t pid;
        pid = fork();
        if (pid < 0) { /* error occurred */
            fprintf(stderr, "Fork Failed");
            return 1;
        }
        else if (pid == 0) {

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
                //printf("hola"); 
            }
            memcpy(rptr[in], &next_producer, sizeof next_producer);
            printf("P(%d): Creando Proceso %d [%s]\n",getppid(),getpid(),time_ms);
            //printf("Enviando mensage [%d] ,\n", rptr[in]->len);
            //printf("Enviando mensage [%s] y durmiendo\n", rptr[in]->buf); 
            in = (in + 1) % MAX_LEN;
            
            srand(time(NULL));
        
            int numero = 1+rand() % (5+1-1); 
            sleep(numero);
            
            
        }
        else { /* parent process */
        /* parent will wait for the child to complete */
            //printf("HORA %d",getpid());
            int status;
            char fmt[16], buf[16];
            struct timeval tv;
            struct tm tm;

            gettimeofday(&tv, NULL);
            tm = *localtime(&tv.tv_sec);
            strftime(fmt, sizeof fmt, "%H:%M:%S.%%03u", &tm);
            snprintf(buf, sizeof buf, fmt, tv.tv_usec);
            printf("[%s] ",buf);
            
            //sleep(5);
            wait(&status);
            //printf("Child Complete\n
        }


       /*  next_producer.len = 10;
        strcpy(next_producer.buf,"Pedro");
        while (((in+1) % MAX_LEN) ==  out)
        {
            //printf("hola"); // do nothing
        }
        //rptr[in] = ;
        //buffer[in] = *rptr;
        memcpy(rptr[in], &next_producer, sizeof next_producer);
        
        printf("Enviando mensage [%d] ,\n", rptr[in]->len);
	    printf("Enviando mensage [%s] y durmiendo\n", rptr[in]->buf);
        
        in = (in + 1) % MAX_LEN;
        sleep(5); */
    }
    


/* 
    printf("%lu\n",sizeof(struct region));
    int hora = 10;
    rptr->len = hora;
    strcpy(rptr->buf,"Pedro");
    /* 
    for(int i = 0; i< MAX_LEN ; i++){
        rptr->buf[i] = 'a'; 
    } *//* 
    printf("Enviando mensage [%d] ,\n", rptr->len);
	printf("Enviando mensage [%s] y durmiendo\n", rptr->buf);
    rptr++;
    sleep(5); */
    
	return 0;
}