Propuesta:
El ejercicio que se realizo esta basado en una separacion de memoria compartida limitada usando una estructura,
que sus miembros son registrados por el procesos de los hijos que se van creando.

Archivo Producer.c
- En este archivo cree un arreglo de structura para poder almacenar varias memorias compartidas de tamaño de la misma structura, por ejemplo:
	struct region* rptr[MAX_LEN];
	posteriormente se hizo la apertura de memoria y el mapeo que es realizado para elemento en el arreglo
-Luego se creo en un bucle infinito el cual se encargaba de crear procesos padres e hijos 
	fork()
-Donde en los procesos hijos se da la orden de registrar su tiempo en que fue creado y almacenarlo en una de las posiciones del arreglo con una memoria compartida disponible
	next_producer.len = getpid();
	strcpy(next_producer.buf,time_ms);
-Asi mismo su PID del hijo
	memcpy(rptr[in], &next_producer, sizeof next_producer);
-En esta parte del codigo se almacena lo que fue produciendo en el rptr[in] disponible
-y de ahi se procede a publicar lo realizado.
	printf("P(%d): Creando Proceso %d [%s]\n",getppid(),getpid(),time_ms);
            

Archivo Consumer.c 
-En estar parte se realizo la diferencia de las horas para verificar cuando sobrevivio los procesos hijos
-al igual que el producer se creo un bucle infinito donde el proceso es el mismo, el cual consumer del asiguiente manera:
	next_consumer = rptr[out];
-Despues se procede a rescatar el PID del hijo enviado en la memoria compartida para luego matarlo de la siguiente manera:
   	kill(next_consumer->len,SIGKILL);
-y finalmente publicarlo:
	printf("[%s] C(%d): Matando Proceso %d (vivió %s)\n",time_ms,getpid(),next_consumer->len,diff);  
        

