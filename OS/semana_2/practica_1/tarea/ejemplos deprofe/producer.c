/**
 * Simple program demonstrating shared memory in POSIX systems.
 *
 * This is the producer process that writes to the shared memory region.
 *
 * Figure 3.16
 * 
 * To compile, enter
 * 	gcc shm-posix-producer.c -lrt
 *
 * @author Silberschatz, Galvin, and Gagne
 * Operating System Concepts  - Tenth Edition
 * Copyright John Wiley & Sons - 2018
 */


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/types.h>

int main()
{
	const int SIZE = 4096;// enbytes
	const char *name = "OS";
	const char *message0= "Studying ";
	const char *message1= "Operating Systems ";
	const char *message2= "Is Fun!";

	int shm_fd;
	void *ptr;// apunta a la memoria compartirda

	/* create the shared memory segment */
	shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);//RDWR, lectura y exritura name nombre especifico de la comparticion de la memoria

	/* configure the size of the shared memory segment */
	ftruncate(shm_fd,SIZE);

	/* now map the shared memory segment in the address space of the process */
	ptr = mmap(0,SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);//se mapee la memoria compartida
	if (ptr == MAP_FAILED) {
		printf("Map failed\n");
		return -1;
	}

	/**
	 * Now write to the shared memory region.
 	 *
	 * Note we must increment the value of ptr after each write.
	 */
	printf("%p ",ptr);
	sprintf(ptr,"%s",message0);// escribir un string en un puntero
	ptr += strlen(message0);//[01010] despues de esto
	printf(" %p\n",ptr);
	printf("Enviando mensage [%s] y durmiendo\n", message0);
	sleep(5);//5 segudnos se duerme


	sprintf(ptr,"%s",message1);
	ptr += strlen(message1);
	printf(" %p\n",ptr);
	printf("Enviando mensage [%s] y durmiendo\n", message1);
	sleep(5);

	sprintf(ptr,"%s",message2);
	ptr += strlen(message2);
	printf(" %p\n",ptr);
	printf("Enviando mensage [%s] y durmiendo\n", message2);
	sleep(5);

	const int a = 10;
    sprintf(ptr,"%d",a);
	ptr += 2;
	printf(" %p\n",ptr);
	printf("Enviando mensage [%d] y durmiendo\n", a);
	sleep(5);

	sprintf(ptr,"%s",message2);
	ptr += strlen(message2);
	printf(" %p\n",ptr);
	printf("Enviando mensage [%s] y durmiendo\n", message2);
	sleep(5);


	return 0;
}